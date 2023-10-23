#pragma once

#include <cstdint> // uint types
#include <iostream>

namespace dunsparce {

/**
 * Global types
*/

using Bitboard = uint64_t;
using Rank = int;
using File = int;


/**
 * Type for identifying a Square. 
*/
enum Square {
    A8, B8, C8, D8, E8, F8, G8, H8,
    A7, B7, C7, D7, E7, F7, G7, H7,
    A6, B6, C6, D6, E6, F6, G6, H6,
    A5, B5, C5, D5, E5, F5, G5, H5,
    A4, B4, C4, D4, E4, F4, G4, H4,
    A3, B3, C3, D3, E3, F3, G3, H3,
    A2, B2, C2, D2, E2, F2, G2, H2,
    A1, B1, C1, D1, E1, F1, G1, H1,
    N_SQUARES = 64, NULL_SQUARE = 65
};


/**
 * Type for abs Direction
*/
enum Direction {
    NORTH = 8,
    SOUTH = 8,
    WEST = 1,
    EAST = 1,
    NORTH_WEST = NORTH - WEST,
    NORTH_EAST = NORTH + EAST,
    SOUTH_WEST = SOUTH - WEST,
    SOUTH_EAST = SOUTH + EAST,
    N_DIRECTIONS = 8
};


/**
 * Types for each piece, including a type for no piece
*/
enum PieceType {
    PAWN,
    KNIGHT,
    BISHOP,
    ROOK,
    QUEEN,
    KING,
    NONE = 6,
    N_PIECES = 6,
};

/**
 * Type of color, including a type for no color
*/
enum Color {
    BLACK = 0,
    WHITE = 1,
    NULL_COLOR = 0, // review
    N_COLORS = 2,
};

/**
 * Piece class is composed of a PieceType and a Color
*/
struct Piece {
    PieceType type;
    Color color;
    Piece() : type{ PieceType::NONE }, color{ Color::NULL_COLOR } {}
    Piece(PieceType type, Color color) : type{type}, color{color} {}
};
inline std::ostream& operator<<(std::ostream& out, const Piece& piece) { std::cout << piece.color << "," << piece.type; return out; }
inline bool operator==(const Piece& lhs, const Piece& rhs) { return lhs.type == rhs.type && lhs.color == rhs.color; }
inline bool operator!=(const Piece& lhs, const Piece& rhs) { return !(lhs == rhs); }

/**
 * Type definition for a MoveType. Stored as a 32-bit int.
*/
struct MoveType {
    Square from;
    Square to;
    Piece piece;
    Piece captured;
    Piece promoted;
    bool isDoublePush;
    bool isCroissant;
    bool isCastle;
};
inline std::ostream& operator<<(std::ostream& out, const MoveType& move_type) {
    std::cout << "From: " << move_type.from
              << ", To: " << move_type.to
              << ", Piece: " << move_type.piece
              << ", Capture: " << move_type.captured
              << ", Promoted: " << move_type.promoted
              << ", IsDoublePush: " << move_type.isDoublePush
              << ", IsCroissant: " << move_type.isCroissant
              << ", IsCastle: " << move_type.isCastle
              << '\n';
    return out;
}

} // dunsparce::types