#pragma once

#include <cstdint> // uint types

/**
 * Global types
*/

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
    NULL_COLOR = 0,
    N_COLORS = 2,
};

/**
 * Piece class is composed of a PieceType and a Color
*/
struct Piece {
    PieceType type;
    Color color;
};
inline bool operator==(const Piece& lhs, const Piece& rhs) { return lhs.type == rhs.type && lhs.color == rhs.color; }
inline bool operator!=(const Piece& lhs, const Piece& rhs) { return !(lhs == rhs); }

/**
 * Type for identifying a Square. 
*/
enum Square {
    A1, B1, C1, D1, E1, F1, G1, H1,
    A2, B2, C2, D2, E2, F2, G2, H2,
    A3, B3, C3, D3, E3, F3, G3, H3,
    A4, B4, C4, D4, E4, F4, G4, H4,
    A5, B5, C5, D5, E5, F5, G5, H5,
    A6, B6, C6, D6, E6, F6, G6, H6,
    A7, B7, C7, D7, E7, F7, G7, H7,
    A8, B8, C8, D8, E8, F8, G8, H8,
    N_SQUARES = 64, NULL_SQUARE = 65
};

/**
 * Type for a Direction. Relative to black pov by default.
*/
enum Direction {
    NORTH = 8,
    SOUTH = -8,
    WEST = -1,
    EAST = 1,
    NORTH_WEST = 7,
    NORTH_EAST = 9,
    SOUTH_WEST = -9,
    SOUTH_EAST = -7,
    N_DIRECTIONS = 8
};

/**
 * Type for a Rank.
*/
enum Rank {
    RANK1 = 0,
    RANK2,
    RANK3,
    RANK4,
    RANK5,
    RANK6,
    RANK7,
    RANK8,
    N_RANKS = 8
};

/**
 * Type for a File.
*/
enum File {
    FILEA = 0,
    FILEB,
    FILEC,
    FILED,
    FILEE,
    FILEF,
    FILEG,
    FILEH,
    N_FILES = 8
};

/**
 * Type definition for a MoveType. Stored as a 32-bit int.
*/
struct MoveType {
    Square from;
    Square to;
    Piece piece;
    Piece captured;
    Piece promoted;
    bool is_double_push;
    bool is_croissant;
    bool is_castle;
};