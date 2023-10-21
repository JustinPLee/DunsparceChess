#pragma once

#include "utils.hpp"
#include "types.hpp"

namespace dunsparce {

/**
 * Classification of a Move
*/
class Move {
    public:
        Move();
        explicit Move(MoveType data);

        Square getFromSquare() const;
        Square getToSquare() const;

        Piece getPiece() const;
        Piece getCapturedPiece() const;
        Piece getPromotedPiece() const;

        void setFromSquare(Square square);
        void setToSquare(Square square);

        void setPiece(Piece piece);
        void setCapturedPiece(Piece piece);
        void setPromotedPiece(Piece piece);
        void setIsDoublePush(bool is_double_push);
        void setIsCastle(bool is_castle);
        void setIsCroissant(bool is_croissant);

        bool isCapture() const;
        bool isPromotion() const;
        bool isDoublePush() const;
        bool isCastle() const;
        bool isCroissant() const;

        void print() { utils::printBits(move_); }

        bool operator==(const Move& other) const { return move_ == other.move_; }
        bool operator!=(const Move& other) const { return move_ != other.move_; }

        
    private:
        // all move data is encoded in one 32 bit number (could be done with only 16)
        // data fields can be accessed and modified with bit shift operators
        uint32_t move_{ 0 };
};

}