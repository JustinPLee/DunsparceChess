#pragma once

#include "types.hpp"

class Bitboard {
    public:
        inline Bitboard(uint64_t board = 0x0) : board_{board} {}
        inline Bitboard& operator=(uint64_t board) { board_ = board_; return *this; }
        inline Bitboard& operator=(const Bitboard& other) { board_ = other.board_; return *this; }

        inline Bitboard operator~ () const { return ~board_; }
        inline Bitboard operator& (uint64_t rhs) const { return board_ & rhs; }
        inline Bitboard operator| (uint64_t rhs) const { return board_ | rhs; }
        inline Bitboard operator^ (uint64_t rhs) const { return board_ ^ rhs; }
        inline Bitboard operator<< (uint64_t rhs) const { return board_ << rhs; }
        inline Bitboard operator>> (uint64_t rhs) const { return board_ >> rhs; }

        inline Bitboard& operator&= (uint64_t rhs) { board_ &= rhs; return *this; }
        inline Bitboard& operator|= (uint64_t rhs) { board_ |= rhs; return *this; }
        inline Bitboard& operator^= (uint64_t rhs) { board_ ^= rhs; return *this; }
        inline Bitboard& operator<<= (uint64_t rhs) { board_ <<= rhs; return *this; }
        inline Bitboard& operator>>= (uint64_t rhs) { board_ >>= rhs; return *this; }

        inline Bitboard operator& (const Bitboard& other) const { return board_ & other.board_; }
        inline Bitboard operator| (const Bitboard& other) const { return board_ | other.board_; }
        inline Bitboard operator^ (const Bitboard& other) const { return board_ ^ other.board_; }
        inline Bitboard operator<< (const Bitboard& other) const { return board_ << other.board_; }
        inline Bitboard operator>> (const Bitboard& other) const { return board_ >> other.board_; }

        inline Bitboard& operator&= (const Bitboard& other) { board_ &= other.board_; return *this; }
        inline Bitboard& operator|= (const Bitboard& other) { board_ |= other.board_; return *this; }
        inline Bitboard& operator^= (const Bitboard& other) { board_ ^= other.board_; return *this; }
        inline Bitboard& operator<<= (const Bitboard& other) { board_ <<= other.board_; return *this; }
        inline Bitboard& operator>>= (const Bitboard& other) { board_ >>= other.board_; return *this; }

        inline bool operator==(uint64_t rhs) const { return board_ == rhs; }
        inline bool operator!=(uint64_t rhs) const { return board_ != rhs; }
        inline bool operator==(const Bitboard& other) const { return board_ == other.board_; }
        inline bool operator!=(const Bitboard& other) const { return board_ != other.board_; }

        inline bool empty() const { return board_ == 0; }

        inline int getLeastSignificantBit() const { return board_ & -board_; }
        
        inline int popcount() const {
            // https://stackoverflow.com/a/109025
            uint64_t i = board_;
            i = i - ((i >> 1) & 0x55555555);
            i = (i & 0x33333333) + ((i >> 2) & 0x33333333);
            i = (i + (i >> 4)) & 0x0F0F0F0F;
            i *= 0x01010101;
            return  i >> 24;
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

    private:
        uint64_t board_{0};
};