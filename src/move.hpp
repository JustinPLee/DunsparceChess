#pragma once

#include "types.hpp"

class Move {
    public:
        Move() = default;
        Move(MoveType data);
        inline bool operator==(const Move& other) { return move_ == other.move_; }
        inline bool operator!=(const Move& other) { return !(move_ == other.move_); }
        Square getFromSquare() const;
        Square getToSquare() const;
        Piece getPiece() const;
        Piece getCapturedPiece() const;
        Piece getPromotedPiece() const;
        bool isCapture() const;
        bool isPromotion() const;
        bool isDoublePush() const;
        bool isCastle() const;
        bool isCroissant() const;
    private:
        // all move data is encoded in one 32 bit number
        // data fields can be accessed and modified with bit shift operators
        uint32_t move_;
};