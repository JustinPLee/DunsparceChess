#pragma once

#include "types.hpp"

class Move {
    public:
        Move() = default;
        Move(MoveType data);
        inline bool operator==(const Move& other) { return move == other.move; }
        inline bool operator!=(const Move& other) { return !(move == other.move); }
        Square getFromSquare() const;
        Square getToSquare() const;
        Piece getPiece() const;
        Piece getCaptured() const;
        Piece getPromoted() const;
        bool getDoublePush() const;
        bool getCroissant() const;
        bool getCastle() const;
    private:
        // all move data is encoded in one 32 bit number
        // data fields can be accessed and modified with bit shift operators
        uint32_t move;
};