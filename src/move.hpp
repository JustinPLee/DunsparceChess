#pragma once

#include "types.hpp"

namespace dunsparce::move {

struct Move {
    Move(Square from_square, Square to_square, Piece piece, Piece promoted_piece, bool capture_flag, bool double_push_flag, bool croissant_flag, bool castling_flag);
    uint32_t move;
};

Square getFromSquare(const Move& move);
Square getToSquare(const Move& move);
Piece getPiece(const Move& move);
Piece getPromotedPiece(const Move& move);
bool getCaptureFlag(const Move& move);
bool getDoublePushFlag(const Move& move);
bool getCroissantFlag(const Move& move);
bool getCastlingFlag(const Move& move);

} // namespace dunsparce::move