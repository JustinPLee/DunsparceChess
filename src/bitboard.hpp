#pragma once

#include "utils.hpp"
#include "types.hpp"

/**
 * Header only Bitboard class.
 * Supports all native bit operators, lsb, and popcount
*/
class Bitboard {
    public:
        explicit inline Bitboard(uint64_t board = uint64_t{0}) : board_{board} {}

        inline int getLeastSignificantBit() const { return lsb(); }
        inline int lsb() const { return board_ & -board_; }
        
        inline int popcount() const {
            // slow popcount
            uint64_t cpy = board_;
            int count = 0;
            while(cpy > 0) {
                cpy >>= 1;
                ++count;
            }
            return count;
        }

        inline void print() const {
            for(int i = 0; i < 8; i++){
                for(int j = 0; j < 8; j++) {
                    const int n = 63-8*i-j;
                    std::cout << ((board_ >> n) & 1 ? 'x' : '.');
                }
                std::cout << '\n';
            }
        }

        inline bool empty() const { return board_ == 0; }

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

        inline bool operator==(uint64_t rhs) const { return board_ == rhs; }
        inline bool operator!=(uint64_t rhs) const { return board_ != rhs; }
        inline bool operator==(const Bitboard& other) const { return board_ == other.board_; }
        inline bool operator!=(const Bitboard& other) const { return board_ != other.board_; }

        friend inline std::ostream& operator<<(std::ostream& out, const Bitboard& rhs) { utils::printBits(rhs.board_); return out; }


    private:
        uint64_t board_{0};
};