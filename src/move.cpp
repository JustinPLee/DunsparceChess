#include <iostream>

#include "types.hpp"
#include "move.hpp"
#include "utils.hpp"
namespace dunsparce::move {

Move::Move(Square from_square, Square to_square, Piece piece, Piece promoted_piece, bool capture_flag, bool double_push_flag, bool croissant_flag, bool castling_flag)
    : move{ 
        (uint32_t{from_square})    |
        (to_square          << 6)  |
        (piece              << 12) |
        (promoted_piece     << 16) |
        (capture_flag       << 20) |
        (double_push_flag   << 21) |
        (croissant_flag     << 22) |
        (castling_flag      << 23) 
    } {}

Square Move::get_from_square() const {
    return Square((move & 0x3f));
}
Square Move::get_to_square() const {
    return Square((move & 0xfc0) >> 6);
}
Piece Move::get_piece() const {
    return Piece((move & 0xf000) >> 12);
}
Piece Move::get_promoted_piece() const {
    return Piece((move & 0xf0000) >> 16);
}
bool Move::get_capture_flag() const {
    return (move & 0x100000);
}
bool Move::get_double_push_flag() const {
    return (move & 0x200000);
}
bool Move::get_croissant_flag() const {
    return (move & 0x400000);
}
bool Move::get_castling_flag() const {
    return (move & 0x800000);
}

std::ostream& operator<<(std::ostream& out, const Move& move) {
    using namespace utils;
    using namespace move;
    std::cout << "("
              << "From: "           << squareToCoordinates(move.get_from_square())  << ", "
              << "To: "             << squareToCoordinates(move.get_to_square())    << ", "
              << "Piece: "          << pieceToUnicode(move.get_piece())             << ", "
              << "Promoted piece: " << pieceToUnicode(move.get_promoted_piece())    << ", "
              << "Capture: "        << (move.get_capture_flag() ? 'T' : 'F')        << ", "
              << "Double push: "    << (move.get_double_push_flag() ? 'T' : 'F')    << ", "
              << "Croissant: "      << (move.get_croissant_flag() ? 'T' : 'F')      << ", "
              << "Castle: "         << (move.get_castling_flag() ? 'T' : 'F')
              << ")";
    return out;
}

} // namespace dunsparce::move