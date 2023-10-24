#include <iostream>
#include <vector>

#include "types.hpp"
#include "constants.hpp"
#include "board.hpp"
#include "utils.hpp"
#include "engine/movegen/attacks.hpp"
#include "engine/movegen/movegen.hpp"

namespace dunsparce {

Board::Board(const std::string& fen) {
    clear();
    parseFen(fen);
}

void Board::clear() {
    // state variables
    pieces_.fill(Zero);
    occupancies_.fill(Zero);
    move_list_.reserve(constants::max_moves);
    croissant_ = NullSquare;
    side_ = White;
    pov_ = White;
    castling_ = uint8_t{ 0 };
}

void Board::parseFen(const std::string& fen) {
    clear();

    std::vector<std::string> fields{ utils::tokenize(fen) };

    auto init_pieces = [&]() {
        std::string piece_str{ fields[0] };
        int square_idx{ 0 };
        for(size_t idx = 0; idx < piece_str.length(); ++idx) {
            if(std::isalpha(piece_str[idx])) {
                Piece piece{ utils::charToPiece(piece_str[idx]) };
                pieces_[int(piece)] |= (One << square_idx);
                ++square_idx;
            } else if(std::isdigit(piece_str[idx])) {
                square_idx += piece_str[idx]-'0';
            }
        }
    };

    auto init_side = [&]() {
        side_ = (fields[1] == "w" ? White : Black);
    };

    auto init_castling = [&]() {
        std::string castling{ fields[2] };
        std::for_each(castling.begin(), castling.end(), [&](char c) {
            switch(c) {
                case 'K': castling_ |= constants::castle_wk; break;
                case 'Q': castling_ |= constants::castle_wq; break;
                case 'k': castling_ |= constants::castle_bk; break;
                case 'q': castling_ |= constants::castle_bq; break;
                case '-': return;
            }
        });
    };

    auto init_croissant = [&]() {
        std::string croissant{ fields[3] };
        if(croissant != "-") {
            croissant_ = get_square(8 - (croissant[1] - '0'), croissant[0] - 'a');
        } else {
            croissant = NullSquare;
        }
    };

    init_pieces();
    init_side();
    init_castling();
    init_croissant();
    if(fields.size() > 4) {
        // init_half_moves();
        // init_full_moves();
    }

    for(int i = 0; i <= 5; ++i) {
        occupancies_[Black] |= pieces_[i];
    }
    for(int i = 6; i < NPieces; ++i) {
        occupancies_[White] |= pieces_[i];
    }
    occupancies_[Both] = occupancies_[Black] | occupancies_[White];
}

// TODO: 
uint64_t Board::generateZobristKey() { return 0; };

// TODO: FIX exporting repeated pieces
std::string Board::exportFen() {
    // squares
    std::string squares = "";
    for(int rank = 0; rank < 8; ++rank) {
        for(int file = 0; file < 8; ++file) {
            //squares += utils::pieceToChar(squares_[(file-1)+(rank-1)*8]);
        }
        squares += '/';
    }

    // nextMove
    std::string next_move = (side_ == White ? "w" : "b");

    // castlingRights
    std::string castling = "";
    if(castling_ & constants::castle_wk) {
        castling += 'K';
    }
    if(castling_ & constants::castle_wq) {
        castling += 'Q';
    }
    if(castling_ & constants::castle_bk) {
        castling += 'k';
    }
    if(castling_ & constants::castle_bq) {
        castling += 'q';
    }

    // croissant
    std::string croissant = (croissant_ == NullSquare ? "-" : utils::squareToCoordinates(croissant_).data());

    // halfMoves
    std::string half_moves = "0";

    // fullMoves
    std::string full_moves = "0";

    return squares + " " + next_move + " " + castling + " " + croissant + " " + half_moves + " " + full_moves;
}

void Board::print() {
    // White orientation
    if(pov_ == White) {
        for(int rank = 0; rank < 8; ++rank) {
            for(int file = 0; file < 8; ++file) {
                if(file == 0) std::cout << "  " << 8-rank;
                std::string piece_repr = ".";
                for(int piece = 0; piece < NPieces; ++piece) {
                    if(pieces_[piece] & (One << get_square(rank, file))) {
                        piece_repr = utils::pieceToUnicode(Piece(piece));
                        break;
                    }
                }
                std::cout << " " << piece_repr;
            }
            std::cout << '\n';
        }
        std::cout << "    a b c d e f g h\n\n";
    } else if(pov_ == Black) {
        for(int rank = 0; rank < 8; ++rank) {
            for(int file = 0; file < 8; ++file) {
                if(file == 0) std::cout << "  " << rank+1;
                std::string piece_repr = ".";
                for(int piece = 0; piece < NPieces; ++piece) {
                    if(pieces_[piece] & (One << get_square(7-rank, 7-file))) {
                        piece_repr = utils::pieceToUnicode(Piece(piece));
                        break;
                    }
                }
                std::cout << " " << piece_repr;
            }
            std::cout << '\n';
        }
        std::cout << "    h g f e d c b a\n\n";
    }

    std::cout << " Side to move: " << ((side_ == White) ? "White" : "Black") << '\n';
    std::cout << " Croissant square: " << ((croissant_ != NullSquare) ? utils::squareToCoordinates(croissant_) : "Null") << '\n';
    std::cout << " Castling: "   << ((castling_ & constants::castle_wk)  ? 'K' : '-')
                                 << ((castling_ & constants::castle_wq)  ? 'Q' : '-')
                                 << ((castling_ & constants::castle_bk)  ? 'k' : '-')
                                 << ((castling_ & constants::castle_bq)  ? 'q' : '-');
    std::cout << "\n\n";
}

int Board::get_material() {
    return 200;
}

void Board::reversePov() {
    pov_ = (pov_ == White ? Black : White);
}

int Board::addMove(const move::Move& move) {
    move_list_.push_back(move);
    return move_list_.size()-1;
}

int Board::addMove(Square from_square, Square to_square, Piece piece, Piece promoted_piece, bool capture_flag, bool double_push_flag, bool croissant_flag, bool castling_flag) {
    move_list_.emplace_back(from_square, to_square, piece, promoted_piece, capture_flag, double_push_flag, croissant_flag, castling_flag);
    return move_list_.size()-1;
}

void Board::printMove(int index) const {
    std::cout << "Move #" << index+1 << " " << move_list_[index] << '\n';
}

void Board::printMoves() const {
    for(size_t i = 0; i < move_list_.size(); ++i) {
        printMove(i);
    }
}


Bitboard Board::get_piece_bb(Color color, BasePiece base_piece) const {
    return pieces_[utils::createPiece(color, base_piece)];
}

Bitboard Board::get_piece_bb(Piece piece) const {
    return pieces_[piece];
}

Square Board::get_croissant_square() const {
    return croissant_;
}
uint8_t Board::get_castling() const {
    return castling_;
}

Bitboard Board::get_occupancy_bb(Color color) const {
    return occupancies_[color];
}

std::vector<move::Move> Board::get_moves() const {
    return move_list_;
}

} // namespace dunsparce