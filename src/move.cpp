#include <iostream>

#include "move.hpp"
#include "types.hpp"

namespace dunsparce {

Move::Move() : move_{uint32_t{0}} {}

Move::Move(MoveType data) {
    move_ =  uint32_t{data.from}           << 0   |
            (uint32_t{data.to}             << 6)  |
            (uint32_t{data.piece.type}     << 12) |
            (uint32_t{data.piece.color}    << 15) |
            (uint32_t{data.captured.type}  << 16) |
            (uint32_t{data.captured.color} << 19) |
            (uint32_t{data.promoted.type}  << 20) |
            (uint32_t{data.promoted.color} << 23) |
            (uint32_t{data.is_double_push} << 24) |
            (uint32_t{data.is_croissant}   << 25) |
            (uint32_t{data.is_castle}      << 26);
}

Square Move::getFromSquare() const {
    // Bits: 0-5
    return Square((move_ & 0x3f));
}

Square Move::getToSquare() const {
    // Bits: 6-11
    return Square(((move_ >> 6) & 0x3f));
}

Piece Move::getPiece() const {
    // Bits:
    //  Type:  12-14
    //  Color: 15
    return Piece{
        PieceType((move_ >> 12) & 0x7),
        Color((move_ >> 15) & 1)
    };
}

Piece Move::getCapturedPiece() const {
    // Bits:
    //  Type: 16-18
    //  Color: 19
    return Piece{
        PieceType(((move_ >> 16) & 0x7)),
        Color(((move_ >> 19) & 1))
    };
}

Piece Move::getPromotedPiece() const {
    // Bits:
    //  Type: 20-22
    //  Color: 23
    return Piece{
        PieceType(((move_ >> 20) & 0x7)),
        Color(((move_ >> 23) & 1))
    };
}

void Move::setFromSquare(Square square) {
    // Bits: 0-5
    move_ &= ~0x3f;
    move_ |= square;
}

void Move::setToSquare(Square square) {
    // Bits: 6-11
    move_ &= ~(0x3f << 6);
    move_ |= (square << 6);
}

void Move::setPiece(Piece piece) {
    // Bits:
    //  Type: 12-14
    //  Color: 15
    move_ &= ~(0x7 << 12);
    move_ |= (piece.type << 12);
    move_ &= ~(1 << 15);
    move_ |= (piece.color << 15);
}

void Move::setCapturedPiece(Piece piece) {
    // Bits:
    //  Type: 16-18
    //  Color: 19
    move_ &= ~(0x7 << 16);
    move_ |= (piece.type << 16);
    move_ &= ~(1 << 19);
    move_ |= (piece.color << 19);
}

void Move::setPromotedPiece(Piece piece) {
    // Bits:
    //  Type: 20-22
    //  Color: 23
    move_ &= ~(0x7 << 20);
    move_ |= (piece.type << 20);
    move_ &= ~(1 << 23);
    move_ |= (piece.color << 23);
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

void Move::setIsDoublePush(bool is_double_push) {
    // Bits: 24
    move_ &= ~(1 << 24);
    move_ |= (is_double_push << 24);
}

void Move::setIsCroissant(bool is_croissant) {
    // Bits: 25
    move_ &= ~(1 << 25);
    move_ |= (is_croissant << 25);
}

void Move::setIsCastle(bool is_castle) {
    // Bits: 26
    move_ &= ~(1 << 26);
    move_ |= (is_castle << 26);
}

}