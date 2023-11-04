#pragma once

#include <iostream>

#include "types.hpp"

namespace bits {
    using Bitboard = dunsparce::Bitboard;

    constexpr Bitboard u64One{ Bitboard{1} };
    constexpr Bitboard u64Zero{ Bitboard{0} };
    constexpr bool get(Bitboard b, int x);
    constexpr void set(Bitboard& b, int x);
    constexpr void pop(Bitboard& b, int x);
    constexpr bool empty(Bitboard b, int x);
    constexpr int popCount(Bitboard b);
    constexpr int bitScanForward(Bitboard b);
    static inline void pprint(Bitboard b, char empty = 'x', char set = '.');

    constexpr Bitboard oneBitMask(int x) {
        return (u64One << x);
    }

    constexpr bool get(Bitboard b, int x) {
        return (b & oneBitMask(x));
    }

    constexpr void set(Bitboard& b, int x) {
        b |= oneBitMask(x);
    }

    constexpr void pop(Bitboard& b, int x) {
        b &= ~oneBitMask(x);
    }

    constexpr bool empty(Bitboard b, int x) {
        return !get(b, x);
    }

    constexpr int popCount(Bitboard b) {
        // kernighan
        int count{};
        while(b) {
            ++count;
            b &= b - 1;
        }
        return count;
    }

    constexpr int bitScanForward(Bitboard b) {
        return popCount((b & -b) - 1);
    }

    static inline void pprint(Bitboard b, char set, char empty) {
        for(int rank = 0; rank < 8; ++rank) {
            for(int file = 0; file < 8; ++file) {
                if(file == 0) std::cout << "  " << 8-rank;
                std::cout << ' ';
                std::cout << (bits::get(b, rank * 8 + file) ? set : empty);
            }
            std::cout << '\n';
        }
        std::cout << "    a b c d e f g h\n\n"; 
        std::cout << " Integer representation: " << b << "\n\n";
    }
}