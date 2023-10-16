#include "move.hpp"
#include "types.hpp"

Move::Move() : move_(0) {}

/*
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
*/
Move::Move(MoveType data) {
    move_ = (uint32_t)data.from            >> 0   |
            ((uint32_t)data.to             >> 6)  |
            ((uint32_t)data.piece.type     >> 12) |
            ((uint32_t)data.piece.color    >> 15) |
            ((uint32_t)data.captured.type  >> 16) |
            ((uint32_t)data.captured.color >> 19) |
            ((uint32_t)data.promoted.type  >> 20) |
            ((uint32_t)data.promoted.color >> 23) |
            ((uint32_t)data.isDoublePush   >> 24) |
            ((uint32_t)data.isCroissant    >> 25) |
            ((uint32_t)data.isCastle       >> 26);
}
Square Move::getFromSquare() const {
    // Bits: 0-5
    return (Square)(move_ & 0x3f);
}
Square Move::getToSquare() const {
    // Bits: 6-11
    return (Square)((move_ >> 6) & 0x3f);
}
Piece Move::getPiece() const {
    // Bits:
    //  Type: 12-14
    //  Color: 15
    return {
        (PieceType)((move_ >> 12) & 0x7),
        (Color)((move_ >> 15) & 1)
    };
}
Piece Move::getCapturedPiece() const {
    // Bits:
    //  Type: 16-18
    //  Color: 19
    return {
        (PieceType)((move_ >> 16) & 0x7),
        (Color)((move_ >> 19) & 1)
    };
}
Piece Move::getPromotedPiece() const {
    // Bits:
    //  Type: 20-22
    //  Color: 23
    return {
        (PieceType)((move_ >> 20) & 0x7),
        (Color)((move_ >> 23) & 1)
    };
}
bool Move::isDoublePush() const {
    // Bits: 24
    return (move_ >> 24) & 1;
}
bool Move::isCroissant() const {
    // Bits: 25
    return (move_ >> 25) & 1;
}
bool Move::isCastle() const {
    // Bits: 26
    return (move_ >> 26) & 1;
}
bool Move::isCapture() const {
    return getCapturedPiece().type != NONE;
}
bool Move::isPromotion() const {
    return getPromotedPiece().type != NONE;
}