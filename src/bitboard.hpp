#pragma once

#include <array>

#include "utils.hpp"
#include "types.hpp"
namespace dunsparce {
/**
 * Header only Bitboard class.
 * Supports all native bit operators, lsb, and popcount
*/
class Bitboard {
    public:
        Bitboard() : board_{uint64_t{0}} {};
        Bitboard(uint64_t board) : board_{board} {};

        inline bool get(Square square) const { return (board_ >> square) & 1; }
        inline void set(Square square) { board_ |= square; }
        inline void popLast() { board_ >>= 1; }
        inline void pop(Square square) { board_ &= ~(1ULL << square); }

        template <Direction dir>
        inline void shiftDirection() {
            ;
        }

        Square bitScan() const {
            if (!empty()) {
                Bitboard cpy { board_ & -board_};
                return Square(cpy.popcount()-1);
            }

            return NULL_SQUARE;
        }
        // lsb
        Square bitScanForward() const {
            // cool algo
            static const std::array<int, 64> index64 = {
                0, 47, 1, 56, 48, 27, 2, 60,
                57, 49, 41, 37, 28, 16, 3, 61,
                54, 58, 35, 52, 50, 42, 21, 44,
                38, 32, 29, 23, 17, 11, 4, 62,
                46, 55, 26, 59, 40, 36, 15, 53,
                34, 51, 20, 43, 31, 22, 10, 45,
                25, 39, 14, 33, 19, 30, 9, 24,
                13, 18, 8, 12, 7, 6, 5, 63
            };
            static constexpr StaticBB debruijn64 = 0x03f79d71b4cb0a89;
            return Square(index64[((board_ ^ (board_ - 1)) * debruijn64) >> 58]);
        }

        inline void clearBit(Square square) { board_ ^= (uint64_t{1} << (N_SQUARES - int{square})); }

        int popcount() const;
        void print() const;

        inline Bitboard& operator=(uint64_t rhs) { board_ = rhs; return *this; }
        inline Bitboard& operator=(const Bitboard& other) { board_ = other.board_; return *this; }

        inline Bitboard operator~ () const { return Bitboard(~board_); }
        inline Bitboard operator& (int rhs) const { return Bitboard(board_ & rhs); }
        inline Bitboard operator| (int rhs) const { return Bitboard(board_ | rhs); }
        inline Bitboard operator^ (int rhs) const { return Bitboard(board_ ^ rhs); }
        inline Bitboard operator<< (int rhs) const { return Bitboard(board_ << rhs); }
        inline Bitboard operator>> (int rhs) const { return Bitboard(board_ >> rhs); }

        inline Bitboard& operator&= (uint64_t rhs) { Bitboard(board_ &= rhs); return *this; }
        inline Bitboard& operator|= (uint64_t rhs) { Bitboard(board_ |= rhs); return *this; }
        inline Bitboard& operator^= (uint64_t rhs) { Bitboard(board_ ^= rhs); return *this; }
        inline Bitboard& operator<<= (uint64_t rhs) { Bitboard(board_ <<= rhs); return *this; }
        inline Bitboard& operator>>= (uint64_t rhs) { Bitboard(board_ >>= rhs); return *this; }

        inline Bitboard operator& (const Bitboard& other) const { return Bitboard(board_ & other.board_); }
        inline Bitboard operator| (const Bitboard& other) const { return Bitboard(board_ | other.board_); }
        inline Bitboard operator^ (const Bitboard& other) const { return Bitboard(board_ ^ other.board_); }
        inline Bitboard operator<< (const Bitboard& other) const { return Bitboard(board_ << other.board_); }
        inline Bitboard operator>> (const Bitboard& other) const { return Bitboard(board_ >> other.board_); }

        inline Bitboard& operator&= (const Bitboard& other) { Bitboard(board_ &= other.board_); return *this; }
        inline Bitboard& operator|= (const Bitboard& other) { Bitboard(board_ |= other.board_); return *this; }
        inline Bitboard& operator^= (const Bitboard& other) { Bitboard(board_ ^= other.board_); return *this; }
        inline Bitboard& operator<<= (const Bitboard& other) { Bitboard(board_ <<= other.board_); return *this; }
        inline Bitboard& operator>>= (const Bitboard& other) { Bitboard(board_ >>= other.board_); return *this; }

        inline bool empty() const { return board_ == 0; }
        inline bool operator==(uint64_t rhs) const { return board_ == rhs; }
        inline bool operator!=(uint64_t rhs) const { return board_ != rhs; }
        inline bool operator==(const Bitboard& other) const { return board_ == other.board_; }
        inline bool operator!=(const Bitboard& other) const { return board_ != other.board_; }
        inline explicit operator bool() const { return !empty(); }

        inline friend std::ostream& operator<<(std::ostream& out, const Bitboard& rhs) { utils::printBits(rhs.board_); return out; }
        inline friend Bitboard operator&(uint64_t other, const Bitboard& rhs) { return other & rhs.board_; }

    private:
        uint64_t board_{0};
};

}