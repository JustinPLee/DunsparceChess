#pragma once

#include "types.hpp"

namespace Dunsparce {

    enum class BasePiece : uint8_t { // 7
        Pawn = 0,
        Knight,
        Bishop,
        Rook,
        Queen,
        King,
        None
    };

    enum class Piece { // 12
		BlackPawn = 0,
		WhitePawn,
		BlackKnight,
		WhiteKnight,
		BlackBishop,
		WhiteBishop,
		BlackRook,
		WhiteRook,
		BlackQueen,
		WhiteQueen,
		BlackKing,
		WhiteKing,
		None
    };

    enum class Color {
        Black = 0,
        White,
        None
    };
}