#pragma once

#include "types.hpp"

/* WE LOVE CONSTEXPR */

class Bitboard {
    public:
        constexpr Bitboard(uint64_t board = 0ULL): board{board} {}

        constexpr Bitboard operator~ () const { return ~board; }

        constexpr Bitboard operator& (uint64_t rhs) const { return board & rhs; }
        constexpr Bitboard operator| (uint64_t rhs) const { return board | rhs; }
        constexpr Bitboard operator^ (uint64_t rhs) const { return board ^ rhs; }
        constexpr Bitboard operator<< (uint64_t rhs) const { return board << rhs; }
        constexpr Bitboard operator>> (uint64_t rhs) const { return board >> rhs; }

        constexpr Bitboard& operator&= (uint64_t rhs) { board &= rhs; return *this; }
        constexpr Bitboard& operator|= (uint64_t rhs) { board |= rhs; return *this; }
        constexpr Bitboard& operator^= (uint64_t rhs) { board ^= rhs; return *this; }
        constexpr Bitboard& operator<<= (uint64_t rhs) { board <<= rhs; return *this; }
        constexpr Bitboard& operator>>= (uint64_t rhs) { board >>= rhs; return *this; }

        constexpr Bitboard operator& (const Bitboard& other) const { return board & other.board; }
        constexpr Bitboard operator| (const Bitboard& other) const { return board | other.board; }
        constexpr Bitboard operator^ (const Bitboard& other) const { return board ^ other.board; }
        constexpr Bitboard operator<< (const Bitboard& other) const { return board << other.board; }
        constexpr Bitboard operator>> (const Bitboard& other) const { return board >> other.board; }

        constexpr Bitboard& operator&= (const Bitboard& other) { board &= other.board; return *this; }
        constexpr Bitboard& operator|= (const Bitboard& other) { board |= other.board; return *this; }
        constexpr Bitboard& operator^= (const Bitboard& other) { board ^= other.board; return *this; }
        constexpr Bitboard& operator<<= (const Bitboard& other) { board <<= other.board; return *this; }
        constexpr Bitboard& operator>>= (const Bitboard& other) { board >>= other.board; return *this; }

        constexpr bool operator==(uint64_t rhs) { return board == rhs; }
        constexpr bool operator==(const Bitboard& other) { return board == other.board; }

        constexpr inline bool empty() {
            return board != 0;
        }

        constexpr inline int getLeastSignificantBit() {
            return board &= -board;
        }
        
        constexpr inline int popcount(){
            // https://stackoverflow.com/a/109025
            uint64_t i = board;
            i = i - ((i >> 1) & 0x55555555);
            i = (i & 0x33333333) + ((i >> 2) & 0x33333333);
            i = (i + (i >> 4)) & 0x0F0F0F0F;
            i *= 0x01010101;
            return  i >> 24;
        }

    private:
        uint64_t board;
};