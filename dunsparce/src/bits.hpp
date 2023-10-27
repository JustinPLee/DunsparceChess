#pragma once

#include <cstdint> // uint64_t
#include <iostream>

namespace bits {

    using Bitboard = uint64_t;
    constexpr Bitboard One{ Bitboard{1} };
    constexpr Bitboard Zero{ Bitboard{0} };

    constexpr Bitboard mask(int x) {
        return (One << x);
    }

    constexpr int get(const Bitboard& b, int x) {
        return (b & mask(x));
    }

    constexpr void set(Bitboard& b, int x) {
        b |= mask(x);
    }

    constexpr void pop(Bitboard& b, int x) {
        b &= ~mask(x);
    }

    constexpr bool empty(const Bitboard& b) {
        return b == 0;
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

    inline void pprint(const Bitboard& b) {
        for(int i{ 0 }; i < 8; ++i) {
            for(int j{ 0 }; j < 8; ++j) {
                std::cout << bits::get(b, i*8+j);
            }
            std::cout << '\n';
        }
    }
}