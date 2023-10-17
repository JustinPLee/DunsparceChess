#pragma once

#include "types.hpp"

/**
 * Classification of a Move
*/
class Move {
    public:
        Move();
        explicit Move(MoveType data);

        /**
         * @return `Square` Square of the initial square of the piece performing the move
        */
        Square get_from_square() const;

        /**
         * @return `Square` Square of the destination square of the piece performing the move
        */
        Square get_to_square() const;

        /**
         * @return `Piece` Piece performing the move
        */
        Piece get_piece() const;

        /**
         * @return `Piece` Captured piece, if any
        */
        Piece get_captured_piece() const;

        /**
         * @return `Piece` Promoted piece, if any
        */
        Piece get_promoted_piece() const;

        /**
         * @return `bool` Returns true if the move is a capture
        */
        bool is_capture() const;

        /**
         * @return `bool` Returns true if the move is a promotion
        */
        bool is_promotion() const;

        /**
         * @return `bool` Returns true if the move is a double push
        */
        bool is_double_push() const;

        /**
         * @return `bool` Returns true if the move is any type of castling
        */
        bool is_castle() const;
        
        /**
         * @return `bool` Returns true if the move is a croissant
        */
        bool is_croissant() const;

        inline bool operator==(const Move& other) { return move_ == other.move_; }
        inline bool operator!=(const Move& other) { return !(move_ == other.move_); }
        
    private:
        // all move data is encoded in one 32 bit number
        // data fields can be accessed and modified with bit shift operators
        uint32_t move_ = 0;
};