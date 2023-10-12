#pragma once

#include "types.hpp"

namespace Dunsparce {
    class Bitboard {
        public:
            Bitboard(U64 board = 0ULL): board{board} {}

            Bitboard operator~ () const { return ~board; }

            Bitboard operator& (U64 rhs) const { return board & rhs; }
            Bitboard operator| (U64 rhs) const { return board | rhs; }
            Bitboard operator^ (U64 rhs) const { return board ^ rhs; }
            Bitboard operator<< (U64 rhs) const { return board << rhs; }
            Bitboard operator>> (U64 rhs) const { return board >> rhs; }

            Bitboard& operator&= (U64 rhs) { board &= rhs; return *this; }
            Bitboard& operator|= (U64 rhs) { board |= rhs; return *this; }
            Bitboard& operator^= (U64 rhs) { board ^= rhs; return *this; }
            Bitboard& operator<<= (U64 rhs) { board <<= rhs; return *this; }
            Bitboard& operator>>= (U64 rhs) { board >>= rhs; return *this; }

            Bitboard operator& (const Bitboard& other) const { return board & other.board; }
            Bitboard operator| (const Bitboard& other) const { return board | other.board; }
            Bitboard operator^ (const Bitboard& other) const { return board ^ other.board; }
            Bitboard operator<< (const Bitboard& other) const { return board << other.board; }
            Bitboard operator>> (const Bitboard& other) const { return board >> other.board; }

            Bitboard& operator&= (const Bitboard& other) { board &= other.board; return *this; }
            Bitboard& operator|= (const Bitboard& other) { board |= other.board; return *this; }
            Bitboard& operator^= (const Bitboard& other) { board ^= other.board; return *this; }
            Bitboard& operator<<= (const Bitboard& other) { board <<= other.board; return *this; }
            Bitboard& operator>>= (const Bitboard& other) { board >>= other.board; return *this; }

            bool operator==(U64 rhs) { return board == rhs; }
            bool operator==(const Bitboard& other) { return board == other.board; }

            bool isSet(int n) {
                return (board >> n) & 1;
            }
            
            int popcount() {
                // https://stackoverflow.com/a/109025
                U64 i = board;
                i = i - ((i >> 1) & 0x55555555);
                i = (i & 0x33333333) + ((i >> 2) & 0x33333333);
                i = (i + (i >> 4)) & 0x0F0F0F0F;
                i *= 0x01010101;
                return  i >> 24;
            }

        private:
            uint64_t board;
    };
}