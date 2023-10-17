#pragma once

#include "utils.hpp"
#include "types.hpp"

/**
 * Classification of a Move
*/
class Move {
    public:
        Move();
        explicit Move(MoveType data);

        /**
         * @returns `Square` Square of the initial square of the piece performing the move
        */
        Square getFromSquare() const;

        /**
         * @returns `Square` Square of the destination square of the piece performing the move
        */
        Square getToSquare() const;

        /**
         * @returns `Piece` Piece performing the move
        */
        Piece getPiece() const;

        /**
         * @returns `Piece` Captured piece, if any
        */
        Piece getCapturedPiece() const;

        /**
         * @returns `Piece` Promoted piece, if any
        */
        Piece getPromotedPiece() const;

        /**
         * @param `Square` Square of the initial square of the piece performing the move
        */
        void setFromSquare(Square square);

        /**
         * @param `Square` Square of the destination square of the piece performing the move
        */
        void setToSquare(Square square);

        /**
         * @param `Piece` Piece performing the move
        */
        void setPiece(Piece piece);

        /**
         * @param `Piece` Captured piece, if any
        */
        void setCapturedPiece(Piece piece);

        /**
         * @param `Piece` Promoted piece, if any
        */
        void setPromotedPiece(Piece piece);

        /**
         * @returns `bool` Returns true if the move is a capture
        */
        bool isCapture() const;

        /**
         * @returns `bool` Returns true if the move is a promotion
        */
        bool isPromotion() const;

        /**
         * @returns `bool` Returns true if the move is a double push
        */
        bool isDoublePush() const;

        /**
         * @returns `bool` Returns true if the move is any type of castling
        */
        bool isCastle() const;
        
        /**
         * @returns `bool` Returns true if the move is a croissant
        */
        bool isCroissant() const;

        /**
         * @param `bool` Returns true if the move is a double push
        */
        void setIsDoublePush(bool is_double_push);

        /**
         * @param `bool` Returns true if the move is any type of castling
        */
        void setIsCastle(bool is_castle);
        
        /**
         * @param `bool` Returns true if the move is a croissant
        */
        void setIsCroissant(bool is_croissant);

        inline bool operator==(const Move& other) { return move_ == other.move_; }
        inline bool operator!=(const Move& other) { return !(move_ == other.move_); }

        void print() {
            utils::printBits(move_);
        };
        
    private:
        // all move data is encoded in one 32 bit number
        // data fields can be accessed and modified with bit shift operators
        uint32_t move_ = 0;
};