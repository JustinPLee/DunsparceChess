#include "types.hpp"
#include "move.hpp"

namespace dunsparce::move {

Move::Move(Square from_square, Square to_square, Piece piece, Piece promoted_piece, bool capture_flag, bool double_push_flag, bool croissant_flag, bool castling_flag)
    : move{ 
        (from_square)              |
        (to_square          << 6)  |
        (piece              << 12)    |
        (promoted_piece     << 16) |
        (capture_flag       << 20) |
        (double_push_flag   << 21) |
        (croissant_flag     << 22) |
        (castling_flag      << 23) 
    } {}

Square getFromSquare(const Move& move) {
    return Square((move.move & 0x3f));
}
Square getToSquare(const Move& move) {
    return Square((move.move & 0xfc0) >> 6);
}
Piece getPiece(const Move& move) {
    return Piece((move.move & 0xf000) >> 12);
}
Piece getPromotedPiece(const Move& move) {
    return Piece((move.move & 0xf0000) >> 16);
}
bool getCaptureFlag(const Move& move) {
    return (move.move & 0x100000);
}
bool getDoublePushFlag(const Move& move) {
    return (move.move & 0x200000);
}
bool getCroissantFlag(const Move& move) {
    return (move.move & 0x400000);
}
bool getCastlingFlag(const Move& move) {
    return (move.move & 0x800000);
}

} // namespace dunsparce::move