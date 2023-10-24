
#include <vector>
#include <array>
#include <string>
#include <sstream>
#include <bit>
#include <iostream>
#include "assert.h"

#include "utils.hpp"

#include "types.hpp"
#include "constants.hpp"

namespace dunsparce::utils {

char pieceToChar(Piece piece) {
    static const std::array<char, NPieces+2> names{"PNBRQKpnbrqk?"};
    return names[int(piece)];
}

Piece charToPiece(char c) {
    switch(c) {
        case 'P': return WPawn;
        case 'N': return WKnight;
        case 'B': return WBishop;
        case 'R': return WRook;
        case 'Q': return WQueen;
        case 'K': return WKing;
        case 'p': return BPawn;
        case 'n': return BKnight;
        case 'b': return BBishop;
        case 'r': return BRook;
        case 'q': return BQueen;
        case 'k': return BKing;
        case '-': return NullPiece;
        default: std::cout << "invalid char"; exit(1);
    }
}

std::string pieceToUnicode(Piece piece) {
    static const std::array<std::string, NPieces+2> unicode_chars{"♙","♘","♗","♖","♕","♔","♟︎","♞","♝","♜","♛","♚", "?"};
    return unicode_chars[int(piece)];
}

std::string_view squareToCoordinates(Square square) {
    constexpr static std::array<std::string_view, NSquares+1> square_names {
        "a8", "b8", "c8", "d8", "e8", "f8", "g8", "h8",
        "a7", "b7", "c7", "d7", "e7", "f7", "g7", "h7",
        "a6", "b6", "c6", "d6", "e6", "f6", "g6", "h6",
        "a5", "b5", "c5", "d5", "e5", "f5", "g5", "h5",
        "a4", "b4", "c4", "d4", "e4", "f4", "g4", "h4",
        "a3", "b3", "c3", "d3", "e3", "f3", "g3", "h3",
        "a2", "b2", "c2", "d2", "e2", "f2", "g2", "h2",
        "a1", "b1", "c1", "d1", "e1", "f1", "g1", "h1",
        "-"
    };
    return square_names[square];
}

std::vector<std::string> tokenize(const std::string& str) {
    std::vector<std::string> tokens;
    std::istringstream ss(str);
    std::string value;
    while(ss >> value) {
        tokens.push_back(value);
    }
    return tokens;
}

void printBits(Bitboard bb) {
    if(bb == 0) {
        std::cout << 0;
        return;
    }
    std::string bit_s{};
    for(int i = 0; i < 64; ++i) {
        bit_s = std::to_string(bb & 1) + bit_s;
        bb >>= 1;
    }
    std::cout << bit_s;
}

int popcount(Bitboard bb) {
    int count = 0;
    while(bb) {
        ++count;
        bb &= bb - 1;
    }
    return count;
}

// lsb (from topleft)
Square getFirstSquare(const Bitboard& bb) {
    if (bb) {
        return Square(popcount((bb & -bb) - 1));
    } else {
        return NullSquare;
    }
}

void popSquare(Bitboard& bb, int square) {
    bb &= ~(One << square);
}

void printBB(const Bitboard& bb) {
    std::cout << '\n';
    for(int rank = 0; rank < 8; ++rank) {
        for(int file = 0; file < 8; ++file) {
            if(file == 0) std::cout << "  " << 8-rank;
            std::cout << (bb & (One << (rank*8+file)) ? " x" : " .");
        }
        std::cout << '\n';
    }
    // print files
    std::cout << "    a b c d e f g h\n\n"; 

    std::cout << " Integer representation: " << bb << "\n\n";
}

Color oppSide(Color color) {
    if(color == White) {
        return Black;
    } else {
        return White;
    }
}

Piece createPiece(Color color, BasePiece base_piece) {
    return Piece(base_piece + 6 * static_cast<int>(color));
}

bool isSquareEmpty(const Bitboard& bb, Square square) {
    return !(bb & (One << square));
}

} // namespace dunsparce::utils