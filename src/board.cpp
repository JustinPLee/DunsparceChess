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
    parseFen(fen);
}

void Board::clear() {
    pieces_.reserve(NPieces);
    for(int i = 0; i < NPieces; ++i) pieces_[i] = Zero;
    occupancies_.reserve(NColors);
    for(int i = 0; i < NColors; ++i) occupancies_[i] = Zero;
    croissant_ = NullSquare;
    side_ = White;
    castling_ = uint8_t{ 0 };
    pov_ = White;
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
            croissant_ = NullSquare;
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
    std::string squares = "";
    for(int rank = 0; rank < 8; ++rank) {
        for(int file = 0; file < 8; ++file) {
            //squares += utils::pieceToChar(squares_[(file-1)+(rank-1)*8]);
        }
        squares += '/';
    }
    std::string next_move = (side_ == White ? "w" : "b");
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
    std::string croissant = (croissant_ == NullSquare ? "-" : utils::squareToCoordinates(croissant_).data());
    std::string half_moves = "0";
    std::string full_moves = "0";

    return squares + " " + next_move + " " + castling + " " + croissant + " " + half_moves + " " + full_moves;
}

void Board::print() {
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

void Board::set_piece_bb(Piece piece, Square square) {
    pieces_[piece] |= (One << square);
}

void Board::pop_piece_bb(Piece piece, Square square) {
    utils::popSquare(pieces_[piece], square);
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

Board::BoardState Board::copyBoardState() const {
    Board::BoardState copy;
    copy.pieces = pieces_;
    copy.occupancies = occupancies_;
    copy.side = side_;
    copy.croissant = croissant_;
    copy.castling = castling_;
    return copy;
}

void Board::restoreBoardState(Board::BoardState&& board_state) {
    pieces_ = board_state.pieces;
    occupancies_ = board_state.occupancies;
    side_ = board_state.side;
    croissant_ = board_state.croissant;
    castling_ = board_state.castling;
}

bool Board::makeMove(const move::Move& move, move::Type move_type, BoardState& copy) {
    copy = copyBoardState();

    const Square from_square{ move.get_from_square() };
    const Square to_square{ move.get_to_square() };
    const Piece piece{ move.get_piece() };
    const Piece promotion_piece{ move.get_promotion_piece() };
    const bool capture{ move.get_capture_flag() };
    const bool double_push{ move.get_double_push_flag() };
    const bool croissant{ move.get_croissant_flag() };
    const bool castling{ move.get_castling_flag() };

    pop_piece_bb(piece, from_square);
    set_piece_bb(piece, to_square);

    if(capture) {
        const Piece captured_piece_range_start{ (side_ == Black) ? WPawn : BPawn };
        for(int p = captured_piece_range_start; p < captured_piece_range_start + NPieces/2; ++p) {
            if(utils::isSquareSet(pieces_[p], to_square)) {
                pop_piece_bb(Piece(p), to_square);
                break;
            }
        }
    }

    if(move_type == move::Type::Capture) {}

    if(promotion_piece != NullPiece) {
        // piece is already at to_square
        pop_piece_bb((side_ == White) ? WPawn : BPawn, to_square);
        set_piece_bb(promotion_piece, to_square);
    }

    if(croissant) {
        if(side_ == White) {
            pop_piece_bb(BPawn, Square(to_square + 8)); // south
        } else {
            pop_piece_bb(WPawn, Square(to_square - 8)); // north
        }
    }
    
    croissant_ = NullSquare;

    if(double_push) {
        if(side_ == White) {
            croissant_ = Square(to_square + 8);
        } else {
            croissant_ = Square(to_square - 8);
        }
    }

    if(castling) {
        switch(int(to_square)) {
            // white king side
            case G1:
                pop_piece_bb(WRook, H1);
                set_piece_bb(WRook, F1);
                break;
            // white queen side
            case C1:
                pop_piece_bb(WRook, A1);
                set_piece_bb(WRook, D1);
                break;
            // black king side
            case G8:
                pop_piece_bb(BRook, H8);
                set_piece_bb(BRook, F8);
                break;
            // black queen side;
            case C8:
                pop_piece_bb(BRook, A8);
                set_piece_bb(BRook, D8);
                break;
        }
    }
    // accounts for rook/king moving
    castling_ &= constants::castling_rights[from_square];
    // accounts for rooks being captured
    castling_ &= constants::castling_rights[to_square];

    occupancies_[White] = Zero;
    occupancies_[Black] = Zero;
    occupancies_[Both] = Zero;

    for(int piece = BPawn; piece <= BKing; ++piece) {
        occupancies_[White] |= pieces_[piece];
    }
    for(int piece = WPawn; piece <= WKing; ++piece) {
        occupancies_[Black] |= pieces_[piece];
    }
    occupancies_[Both] = occupancies_[White] | occupancies_[Black];

    side_ = Color(side_^1);
    // king is available to take by an oposing piece. illegal move
    if(attacks::isAttacked((side_ == White) ? utils::findLSB(get_piece_bb(BKing)) : utils::findLSB(get_piece_bb(WKing)), side_, *this)) {
        restoreBoardState(std::move(copy));
        return false;
    }

    return true;
}

move::Move Board::get_move(int index) const {
    return move_list_[index];
}

void Board::clearMoves() {
    move_list_.clear();
}


} // namespace dunsparce