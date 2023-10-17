#include <iostream>
#include "types.hpp"
#include "constants.hpp"
#include "board.hpp"
#include "utils.hpp"

Board::Board(std::string_view fen) {
    init(fen);
}

void Board::init(std::string_view fen) {
    init_bitboards();
    process_fen(fen);
};

void Board::init_bitboards() {
    // set all piece bitboards to 0
    for(int color = 0; color < N_COLORS; ++color) {
        for(int ptype = 0; ptype < N_PIECES; ++ptype) {
            pieces_[color][ptype] = uint64_t{0};
        }
    }
    // set each square to a null piece
    for(int square = 0; square < N_SQUARES; ++square) {
        squares_[square] = { NONE, NULL_COLOR };
    }

    // set each color occupancy bitboard to 0
    colors_[WHITE] = uint64_t{0};
    colors_[BLACK] = uint64_t{0};

}

void Board::clear() {
    init_bitboards();

    state_ = BoardState{
        .castling_rights = CASTLE_BLACK_KING | CASTLE_BLACK_QUEEN | CASTLE_WHITE_KING | CASTLE_WHITE_QUEEN, /*all rights set to true by default*/
        .croissant = NULL_SQUARE,
        .half_moves = 0,
        .zobrist_key = uint64_t{0}
    };

    full_moves_ = 0;
    next_move_ = WHITE;
    pov_ = WHITE;
}

void Board::process_fen(std::string_view fen) {
    // Example starting FEN: rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 0

    Color next_move;
    int full_moves;
    BoardState state;
    
    std::vector<std::string> fields = utils::tokenize(fen.data());
    // corresponding fields for each section of the FEN string
    enum Fields {
        _squares = 0,
        _next_move = 1,
        _castling_rights = 2,
        _croissant = 3,
        _half_moves = 4,
        _full_moves = 5
    };

    // squares
    std::string_view p = fields[Fields::_squares];
    int squareIndex = 0;
    // If the character is a letter, set the according piece bitboard's
    // and color occupany bitboard's bit to 1 and add that piece to the
    // square position array. If the character is a digit, skip that many bits.
    for(std::size_t i = 0; i < p.length(); ++i) {
        if(('a' <= p[i] && p[i] <= 'z') || ('A' <= p[i] && p[i] <= 'Z')) {
            Piece piece = utils::char_to_piece(p[i]);
            squares_[squareIndex] = piece;
            // set bitboard bit
            pieces_[piece.color][piece.type] |= (1ULL << squareIndex);
            colors_[piece.color] |= (1ULL << squareIndex); 
            squareIndex++;
        } else if('0' <= p[i] && p[i] <= '9') {
            squareIndex += p[i] - '0';
        } else if(p[i] == '/') {
            continue;
        }
    }

    // nextMove
    switch(fields[Fields::_next_move].front()) {
        case 'w': next_move = WHITE; break;
        case 'b': next_move = BLACK; break;
        default: std::cout << "invalid FEN string"; exit(1);
    }

    // castlingRights;
    for(auto c: fields[Fields::_castling_rights]) {
        switch(c) {
            case 'k': state.castling_rights |= CASTLE_BLACK_KING;  break;
            case 'q': state.castling_rights |= CASTLE_BLACK_QUEEN; break;
            case 'K': state.castling_rights |= CASTLE_WHITE_KING;  break;
            case 'Q': state.castling_rights |= CASTLE_WHITE_QUEEN; break;
            case '-': break;
            default: std::cout << "invalid FEN string"; exit(1);
        }
    }

    // croissant
    state.croissant = fields[Fields::_croissant].front() == '-' ? NULL_SQUARE :
        Square((std::distance(SQUARE_NAMES.begin(), std::find(SQUARE_NAMES.begin(), SQUARE_NAMES.end(), fields[Fields::_croissant].data()))));

    // halfMoves
    state.half_moves = std::stoi(fields[Fields::_half_moves].data());

    // fullMoves
    full_moves = std::stoi(fields[Fields::_full_moves].data());

    state_ = state;
    next_move = next_move;
    full_moves_ = full_moves;
}


// TODO: FIX exporting repeated pieces
std::string Board::export_fen() {
    // squares
    std::string squares = "";
    for(int rank = RANK1; rank <= RANK8; ++rank) {
        for(int file = FILEA; file <= FILEH; ++file) {
            squares += utils::piece_to_char(squares_[(file-1)+(rank-1)*8]);
        }
        squares += '/';
    }

    // nextMove
    std::string next_move = (next_move_ == WHITE ? "w" : "b");

    // castlingRights
    std::string castling = "";
    if(state_.castling_rights & CASTLE_WHITE_KING) {
        castling += 'K';
    }
    if(state_.castling_rights & CASTLE_WHITE_QUEEN) {
        castling += 'Q';
    }
    if(state_.castling_rights & CASTLE_BLACK_KING) {
        castling += 'k';
    }
    if(state_.castling_rights & CASTLE_BLACK_QUEEN) {
        castling += 'q';
    }

    // croissant
    std::string croissant = (state_.croissant == NULL_SQUARE ? "-" : SQUARE_NAMES[state_.croissant].data());

    // halfMoves
    std::string half_moves = "0";

    // fullMoves
    std::string full_moves = "0";

    return squares + " " + next_move + " " + castling + " " + croissant + " " + half_moves + " " + full_moves;
}

void Board::print() {
    //    +-------------------------------+
    //  8 | ♜ | ♞ | ♝ | ♚ | ♛ | ♝ | ♞ | ♜ |
    //    |---+---+---+---+---+---+---+---|   
    //  7 | ♟︎ | ♟︎ | ♟︎ | ♟︎ | ♟︎ | ♟︎ | ♟︎ | ♟︎ |
    //    |---+---+---+---+---+---+---+---| 
    //  6 |   |   |   |   |   |   |   |   |
    //    |---+---+---+---+---+---+---+---|     
    //  5 |   |   |   |   |   |   |   |   |
    //    |---+---+---+---+---+---+---+---|        
    //  4 |   |   |   |   |   |   |   |   |
    //    |---+---+---+---+---+---+---+---|    
    //  3 |   |   |   |   |   |   |   |   |
    //    |---+---+---+---+---+---+---+---|   
    //  2 | ♙ | ♙ | ♙ | ♙ | ♙ | ♙ | ♙ | ♙ |
    //    |---+---+---+---+---+---+---+---|  
    //  1 | ♖ | ♘ | ♗ | ♕ | ♔ | ♗ | ♘ | ♖ |  
    //    +-------------------------------+
    //      a   b   c   d   e   f   g   h   

    // White orientation
    if(pov_ == WHITE) {
        std::cout << "\n\t  +-------------------------------+\n";
        for(int rank = RANK8; rank >= RANK1; --rank) {
            std::cout << "\t" << rank+1 << " |";
            for(int file = FILEA; file <= FILEH; ++file) {
                std::cout << " " << utils::piece_to_unicode(squares_[file+rank*8]) << " |";
            }
            if(rank < RANK8) {
                std::cout << "\n\t  |---+---+---+---+---+---+---+---|\n";
            } else {
                std::cout << "\n\t  +-------------------------------+\n";
            }
        }
        std::cout << "\t    a   b   c   d   e   f   g   h \n\n";
    } else {
    // Black orientation
        std::cout << "\n\t  +-------------------------------+\n";
        for(int rank = RANK1; rank <= RANK8; ++rank) {
            std::cout << "\t" << rank+1 << " |";
            for(int file = FILEH; file >= FILEA; --file) {
                std::cout << " " << utils::piece_to_unicode(squares_[file+rank*8]) << " |";
            }
            if(rank < RANK1) {
                std::cout << "\n\t  |---+---+---+---+---+---+---+---|\n";
            } else {
                std::cout << "\n\t  +-------------------------------+\n";
            }
        }
        std::cout << "\t    h   g   f   e   d   c   b   a \n\n";
    }
}

int Board::get_piece_material() {
    return 200;
}

void Board::reverse_pov() {
    pov_ = !pov_;
}

Piece Board::piece_at(Square square) {
    return squares_[square];
}