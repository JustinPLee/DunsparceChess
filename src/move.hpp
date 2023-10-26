#pragma once

#include <iostream>

#include "types.hpp"

namespace dunsparce::move {

enum class Type {
    Quiet,
    Capture,
    All
};
struct Move {
    Move() = delete;
    explicit Move(Square from_square, Square to_square, Piece piece, Piece promoted_piece, bool capture_flag, bool double_push_flag, bool croissant_flag, bool castling_flag);
    
    Square get_from_square() const;
    Square get_to_square() const;
    Piece get_piece() const;
    Piece get_promotion_piece() const;
    bool get_capture_flag() const;
    bool get_double_push_flag() const;
    bool get_croissant_flag() const;
    bool get_castling_flag() const;

    uint32_t move;
};

std::ostream& operator<<(std::ostream& out, const Move& move);


} // namespace dunsparce::move