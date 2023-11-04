#pragma once

#include <iostream>

#include "types.hpp"

namespace dunsparce {
    struct Move {
        Square source_square;
        Square target_square;
        Piece actor;
        Piece promoted_piece;

        bool capture_flag;
        bool double_push_flag;
        bool croissant_flag;
        bool castling_flag;
    };
    constexpr Move NullMove{ NullSquare, NullSquare, NullPiece, NullPiece, false, false, false, false };

    enum class MoveType {
        AllMoves,
        Capture
    };

    uint32_t encodeMove(const Move& move);
    Move decodeMove(uint32_t data);

    std::ostream& operator<<(std::ostream& out, const Move& move);
    bool operator==(const Move& lhs, const Move& rhs);
}