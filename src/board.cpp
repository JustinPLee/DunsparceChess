#include <iostream>
#include "types.hpp"
#include "constants.hpp"
#include "board.hpp"
#include "utils.hpp"

namespace dunsparce {

Board::Board(std::string_view fen) {
    init(fen);
}

void Board::init(std::string_view fen) {
    processFen(fen);
};


void Board::clear() {
    squares_.fill(Piece{}); 

    for(int i = 0; i < N_PIECES; ++i) {
        for(int c = 0; c < N_COLORS; ++c) {
            pieces_[i][c] = uint64_t{0};
        } 
    }

    occupancies_[WHITE] = Bitboard{0};
    occupancies_[BLACK] = Bitboard{0};

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

void Board::updatePieceAndColorBitboards(Piece piece, Square square) {
    pieces_[piece.color][piece.type].set(square);
    occupancies_[piece.color].set(square); 
}

void Board::processFen(std::string_view fen) {
    // Example starting FEN: rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 0
    
    std::vector<std::string> fields{ utils::tokenize(fen.data()) };
    // corresponding fields for each section of the FEN string
    enum Fields {
        i_squares = 0,
        i_next_move = 1,
        i_castling_rights = 2,
        i_croissant = 3,
        i_half_moves = 4,
        i_full_moves = 5
    };

    const auto get_squares = [&]() {
        std::string_view p = fields[Fields::i_squares];
        std::array<Piece, 64> new_squares{};
        int squareIndex { 0 };
        // If the character is a letter, set the according piece bitboard's
        // and color occupany bitboard's bit to 1 and add that piece to the
        // square position array. If the character is a digit, skip that many bits.
        for(std::size_t i = 0; i < p.length(); ++i) {
            if(('a' <= p[i] && p[i] <= 'z') || ('A' <= p[i] && p[i] <= 'Z')) {
                Piece piece = utils::charToPiece(p[i]);
                new_squares[squareIndex] = piece;
                updatePieceAndColorBitboards(piece, Square(squareIndex));
                squareIndex++;
            } else if('0' <= p[i] && p[i] <= '9') {
                squareIndex += p[i] - '0';
            } else if(p[i] == '/') {
                continue;
            }
        }
        return new_squares;
    };

    const auto get_next_move = [&]() {
        switch(fields[Fields::i_next_move].front()) {
            case 'w': return WHITE;
            case 'b': return BLACK;
            default: std::cout << "invalid FEN string"; exit(1);
        }
    };

    const auto get_castling_rights = [&]() {
        uint8_t castling_rights{};
        for(auto c: fields[Fields::i_castling_rights]) {
            switch(c) {
                case 'k': castling_rights |= CASTLE_BLACK_KING;
                case 'q': castling_rights |= CASTLE_BLACK_QUEEN;
                case 'K': castling_rights |= CASTLE_WHITE_KING;
                case 'Q': castling_rights |= CASTLE_WHITE_QUEEN;
                case '-': break;
                default: std::cout << "invalid FEN string"; exit(1);
            }
        }
        return castling_rights;
    };

    const auto get_croissant = [&]() {
        return fields[Fields::i_croissant].front() == '-' ? NULL_SQUARE :
            Square((std::distance(SQUARE_NAMES.begin(), std::find(SQUARE_NAMES.begin(), SQUARE_NAMES.end(), fields[Fields::i_croissant].data()))));
    };

    const auto get_half_moves = [&]() {
        return std::stoi(fields[Fields::i_half_moves].data());
    };

    const auto get_full_moves = [&]() {
        return std::stoi(fields[Fields::i_full_moves].data());
    };

    state_ = { get_castling_rights(), get_croissant(), get_half_moves(), generateZobristKey() };
    next_move_ = get_next_move();
    full_moves_ = get_full_moves();
    squares_ = get_squares();
}

// TODO: 
uint64_t Board::generateZobristKey() { return 0; };

// TODO: FIX exporting repeated pieces
std::string Board::exportFen() {
    // squares
    std::string squares = "";
    for(int rank = RANK1; rank <= RANK8; ++rank) {
        for(int file = FILEA; file <= FILEH; ++file) {
            squares += utils::pieceToChar(squares_[(file-1)+(rank-1)*8]);
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
                std::cout << " " << utils::pieceToUnicode(squares_[file+rank*8]) << " |";
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
                std::cout << " " << utils::pieceToUnicode(squares_[file+rank*8]) << " |";
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

int Board::getPieceMaterial() {
    return 200;
}

void Board::reversePov() {
    pov_ = !pov_;
}

}