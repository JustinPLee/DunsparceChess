#include <iostream>
#include "types.hpp"
#include "constants.hpp"
#include "board.hpp"
#include "utils.hpp"
#include "engine/movegen/attacks.hpp"

namespace dunsparce {

Board::Board(std::string_view fen) {
    init(fen);
}

void Board::init(std::string_view fen) {
    //processFen(fen)
};

void Board::clear() {
    // state variables
    pieces_.fill(Zero);
    occupancies_.fill(Zero);
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
                utils::setSquare(pieces_[int(piece)], Square(square_idx));
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
            croissant_ = utils::convertToSquare(8 - (croissant[1] - '0'), croissant[0] - 'a');
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
    for(int i = 6; i <= NPieces; ++i) {
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
                    if(utils::getSquare(pieces_[piece], utils::convertToSquare(rank, file))) {
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
                    if(utils::getSquare(pieces_[piece], utils::convertToSquare(7-rank, 7-file))) {
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

int Board::getPieceMaterial() {
    return 200;
}

void Board::reversePov() {
    pov_ = (pov_ == White ? Black : White);
}

} // namespace dunsparce