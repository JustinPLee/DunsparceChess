#pragma once

#include <iostream>

#include "types.hpp"

namespace bits {

    constexpr Bitboard u64One{ Bitboard{1} };
    constexpr Bitboard u64Zero{ Bitboard{0} };

    constexpr Bitboard makeMask(int x) {
        return (u64One << x);
    }

    constexpr bool get(const Bitboard& b, int x) {
        return (b & makeMask(x));
    }

    constexpr void set(Bitboard& b, int x) {
        b |= makeMask(x);
    }

    constexpr void pop(Bitboard& b, int x) {
        b &= ~makeMask(x);
    }

    constexpr bool empty(const Bitboard& b, int x) {
        return !get(b, x);
    }

    constexpr int popCount(Bitboard b) {
        // kernighan
        int count{ 0 };
        while(b) {
            ++count;
            b &= b - 1;
        }
        return count;
    }

    constexpr int bitScanForward(Bitboard& b) {
        return popCount((b & -b) - 1);
    }

    inline void pprint(const Bitboard& b, char set = 'x', char empty = '.') {
        for(int rank = 0; rank < 8; ++rank) {
            for(int file = 0; file < 8; ++file) {
                if(file == 0) std::cout << "  " << 8-rank;
                std::cout << ' ';
                std::cout << (bits::get(b, squareIndex(rank, file)) ? set : empty);
            }
            std::cout << '\n';
        }
        std::cout << "    a b c d e f g h\n\n"; 
        std::cout << " Integer representation: " << b << "\n\n";
    }
}