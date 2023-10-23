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

constexpr uint64_t One{ 1ULL };
constexpr uint64_t Zero{ 0ULL };

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
    NSquares = 64, NullSquare = 65
};


/**
 * Type for abs Direction
*/
enum Direction {
    North = 8,
    South = 8,
    West = 1,
    East = 1,
    NorthWest = North - West,
    NorthEast = North + East,
    SouthWest = South - West,
    SouthEast = South + East,
};


/**
 * Types for each piece
*/
enum Piece {
    BPawn,
    BKnight,
    BBishop,
    BRook,
    BQueen,
    BKing,
    WPawn,
    WKnight,
    WBishop,
    WRook,
    WQueen,
    WKing,
    NullPiece = 13,
    NPieces = 12,
};

// special type for sliding attacks
enum BishopOrRook {
    Bishop,
    Rook
};

/**
 * Type of color, including a type for no color
*/
enum Color {
    Black = 0,
    White = 1,
    Both = 2,
    NColors = 3
};

} // namespace dunsparce