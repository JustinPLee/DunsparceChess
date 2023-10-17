#include "move.hpp"
#include "types.hpp"

Move::Move() : move_{uint32_t{0}} {}

Move::Move(MoveType data) {
    move_ =  uint32_t{data.from}           >> 0   |
            (uint32_t{data.to}             >> 6)  |
            (uint32_t{data.piece.type}     >> 12) |
            (uint32_t{data.piece.color}    >> 15) |
            (uint32_t{data.captured.type}  >> 16) |
            (uint32_t{data.captured.color} >> 19) |
            (uint32_t{data.promoted.type}  >> 20) |
            (uint32_t{data.promoted.color} >> 23) |
            (uint32_t{data.is_double_push} >> 24) |
            (uint32_t{data.is_croissant}   >> 25) |
            (uint32_t{data.is_castle}      >> 26);
}

Square Move::get_from_square() const {
    // Bits: 0-5
    return Square((move_ & 0x3f));
}

Square Move::get_to_square() const {
    // Bits: 6-11
    return Square(((move_ >> 6) & 0x3f));
}

Piece Move::get_piece() const {
    // Bits:
    //  Type: 12-14
    //  Color: 15
    return Piece{
        PieceType((move_ >> 12) & 0x7),
        Color((move_ >> 15) & 1)
    };
}

Piece Move::get_captured_piece() const {
    // Bits:
    //  Type: 16-18
    //  Color: 19
    return Piece{
        PieceType(((move_ >> 16) & 0x7)),
        Color(((move_ >> 19) & 1))
    };
}

Piece Move::get_promoted_piece() const {
    // Bits:
    //  Type: 20-22
    //  Color: 23
    return Piece{
        PieceType(((move_ >> 20) & 0x7)),
        Color(((move_ >> 23) & 1))
    };
}

bool Move::is_double_push() const {
    // Bits: 24
    return (move_ >> 24) & 1;
}

bool Move::is_croissant() const {
    // Bits: 25
    return (move_ >> 25) & 1;
}

bool Move::is_castle() const {
    // Bits: 26
    return (move_ >> 26) & 1;
}

bool Move::is_capture() const {
    return get_captured_piece().type != NONE;
}

bool Move::is_promotion() const {
    return get_promoted_piece().type != NONE;
}
