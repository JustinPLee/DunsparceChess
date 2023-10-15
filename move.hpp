#pragma once

#include <cstdint> // uint32_t
#include "types.hpp"

/**
 * A "move" is stored as a 32 bit int. 
 * Each property of a move, such as originSquare, targetSquare, and promotionTarget is stored
 * in each bit of the 32 bits. They can be accessed and changed using bitshift operators.
 * 
 * Bits:
 *      0-5: from
 *      6-11: to
 *      12-15: piece
 *      16-19: capture
 *      20-23: promotion
 *      FLAGS
 *      24: Color - 0 = Black, 1 = White
 *      25-31: free 
 * 
 **/


class Move {
    public:
        Move();
        Move(uint32_t from, uint32_t to);
        Move(uint32_t from, uint32_t to, uint32_t flags);
        void operator=(Move move) { this->move = move.move; };

        void clear();

        uint32_t getTo();
        uint32_t getFrom();
        uint32_t getCapture();
        uint32_t getPiece();
        uint32_t getPromotion();

        uint32_t setTo(uint32_t to);
        uint32_t setFrom(uint32_t from);
        uint32_t setCapture(uint32_t capture);
        uint32_t setPiece(uint32_t piece);
        uint32_t setPromotion(uint32_t promotion);

        bool isWhiteMove();
        bool isBlackMove();
        bool isCapture();
        bool isKingcaptured();
        bool isRookMove();
        bool isRookCaptured();
        bool isKingMove();
        bool isPawnMove();
        bool isPawnDoubleMove();
        bool isCroissant();
        bool isPromotion();
        bool isCastle();
        bool isCastleShort();
        bool isCastleLong();

    private:
        uint32_t move;
};