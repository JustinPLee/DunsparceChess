#include <iostream>
#include "types.hpp"
#include "constants.hpp"
#include "board.hpp"
#include "utils.hpp"

Board::Board(std::string_view fen) {
    init(fen);
}

void Board::init(std::string_view fen) {
    clear();
    processFen(fen);
};

void Board::clear() {
    for(int color = 0; color < N_COLORS; color++) {
        for(int ptype = 0; ptype < N_PIECES; ptype++) {
            pieces_[color][ptype] = 0ULL;
        }
    }
    for(int square = 0; square < N_SQUARES; square++) {
        squares_[square] = { NONE, NULL_COLOR };
    }

    colors_[WHITE] = 0ULL;
    colors_[BLACK] = 0ULL;

    state_ = {
        .castlingRights = 15,
        .croissant = NULL_SQUARE,
        .halfMoves = 0,
        .zobrist_key = 0ULL
    };
    fullMoves_ = 0;
    nextMove_ = WHITE;
    pov_ = WHITE;

}

void Board::processFen(std::string_view fen) {
    // rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 0
    // lowercase is black, uppercase is white

    Color nextMove;
    int fullMoves;
    BoardState state;

    enum Fields {
        _squares = 0,
        _nextMove = 1,
        _castlingRights = 2,
        _croissant = 3,
        _halfMoves = 4,
        _fullMoves = 5
    };

    std::vector<std::string> fields = utils::tokenize(fen.data());

    // squares
    std::string_view p = fields[Fields::_squares];
    int squareIndex = 0;
    for(std::size_t i = 0; i < p.length(); i++) {
        if(('a' <= p[i] && p[i] <= 'z') || ('A' <= p[i] && p[i] <= 'Z')) {
            Piece piece = utils::charToPiece(p[i]);
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
    switch(fields[Fields::_nextMove].front()) {
        case 'w': nextMove = WHITE; break;
        case 'b': nextMove = BLACK; break;
        default: std::cout << "should never be here"; exit(1);
    }
    // castlingRights;
    for(auto c: fields[Fields::_castlingRights]) {
        switch(c) {
            case 'k': state.castlingRights |= CASTLE_BLACK_KING;  break;
            case 'q': state.castlingRights |= CASTLE_BLACK_QUEEN; break;
            case 'K': state.castlingRights |= CASTLE_WHITE_KING;  break;
            case 'Q': state.castlingRights |= CASTLE_WHITE_QUEEN; break;
            case '-': break;
            default: std::cout << "should never be here"; exit(1);
        }
    }
    // croissant
    // get index of piece string
    state.croissant = fields[Fields::_croissant].front() == '-' ? NULL_SQUARE :
        (Square)(std::distance(SQUARE_NAMES.begin(), std::find(SQUARE_NAMES.begin(), SQUARE_NAMES.end(), fields[Fields::_croissant].data())));
    // halfMoves
    state.halfMoves = std::stoi(fields[Fields::_halfMoves].data());

    // fullMoves
    fullMoves = std::stoi(fields[Fields::_fullMoves].data());

    state_ = state;
    nextMove = nextMove;
    fullMoves_ = fullMoves;
}


// TODO: FIX exporting repeated pieces
std::string Board::exportFen() {
    // squares
    std::string squares = "";
    for(int rank = 1; rank <= 8; rank++) {
        for(int file = 1; file <= 8; file++) {
            squares += utils::pieceToChar(squares_[(file-1)+(rank-1)*8]);
        }
        squares += '/';
    }
    // nextMove
    std::string nextMove = (nextMove_ == WHITE ? "w" : "b");
    // castlingRights
    std::string castlingRights = "";
    if(state_.castlingRights & CASTLE_WHITE_KING) {
        castlingRights += 'K';
    }
    if(state_.castlingRights & CASTLE_WHITE_QUEEN) {
        castlingRights += 'Q';
    }
    if(state_.castlingRights& CASTLE_BLACK_KING) {
        castlingRights += 'k';
    }
    if(state_.castlingRights & CASTLE_BLACK_QUEEN) {
        castlingRights += 'q';
    }
    // croissant
    std::string croissant = (state_.croissant == NULL_SQUARE ? "-" : SQUARE_NAMES[state_.croissant].data());

    // halfMoves
    std::string halfMoves = "0";

    // fullMoves
    std::string fullMoves = "0";

    return squares + " " + nextMove + " " + castlingRights + " " + croissant + " " + halfMoves + " " + fullMoves;
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
    if(pov_ == WHITE) {
        std::cout << "\n\t  +-------------------------------+\n";
        for(int rank = RANK8; rank >= RANK1; rank--) {
            std::cout << "\t" << rank+1 << " |";
            for(int file = FILEA; file <= FILEH; file++) {
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
        std::cout << "\n\t  +-------------------------------+\n";
        for(int rank = RANK1; rank <= RANK8; rank++) {
            std::cout << "\t" << rank+1 << " |";
            for(int file = FILEH; file >= FILEA; file--) {
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

int Board::evalPieceMaterial() {
    return 200;
}

void Board::reversePov() {
    pov_ = !pov_;
}