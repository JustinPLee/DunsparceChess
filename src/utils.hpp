#pragma once

#include <vector>
#include <array>
#include <string>
#include <sstream>
#include <bit>
#include <iostream>

#include "types.hpp"
#include "constants.hpp"
namespace dunsparce::utils {

    Square getSquare(Rank rank, File file);
    Square getSquare(File file, Rank rank);

    Rank getRank(Square square);
    File getFile(Square square);

    int getRankShift(Square square);
    
    char pieceToChar(const Piece& piece);
    Piece charToPiece(char c);
    std::string pieceToUnicode(Piece piece);
    std::string_view squareToCoordinates(Square square);

    std::vector<std::string> tokenize(const std::string& str);

    void printBits(uint64_t bits);

    int popcount(uint64_t b);

    bool getBit(const uint64_t& b, Square square);
    void setBit(uint64_t& b, Square square);
    // lsb
    // returns 64 if bitboard is empty
    int getLSBIndex(const Bitboard& b);

    void popBit(uint64_t& b, int square);

    Bitboard squareToBB(Square square);

    void printBB(const uint64_t& b);

    template <Color color>
    inline Bitboard shiftRel(Bitboard bb, int val) {
        if constexpr (color == WHITE) {
            bb >>= val;
        } else {
            bb <<= val;
        }
        return bb;
    }
}