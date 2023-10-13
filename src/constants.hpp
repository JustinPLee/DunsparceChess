#pragma once

#include <array>
#include <string_view>
#include "bitboard.hpp"
#include "types.hpp"

constexpr bool WHITE_MOVE = 0;
constexpr bool BLACK_MOVE = 1;

constexpr int PAWN_VALUE   = 100;
constexpr int KNIGHT_VALUE = 300;
constexpr int BISHOP_VALUE = 300;
constexpr int ROOK_VALUE   = 500;
constexpr int QUEEN_VALUE  = 900;
constexpr int KING_VALUE   = 9999;

constexpr std::array<std::string_view, 64> SQUARE_NAMES = {
    "a1","b1","c1","d1","e1","f1","g1","h1",
    "a2","b2","c2","d2","e2","f2","g2","h2",
    "a3","b3","c3","d3","e3","f3","g3","h3",
    "a4","b4","c4","d4","e4","f4","g4","h4",
    "a5","b5","c5","d5","e5","f5","g5","h5",
    "a6","b6","c6","d6","e6","f6","g6","h6",
    "a7","b7","c7","d7","e7","f7","g7","h7",
    "a8","b8","c8","d8","e8","f8","g8","h8"
};

// am lazy
constexpr std::array<int, 64> STARTING_POSITION = {
    3, 1, 2, 5, 4, 2, 1, 3,
    0, 0, 0, 0, 0, 0, 0, 0,
    12, 12, 12, 12, 12, 12, 12, 12,
    12, 12, 12, 12, 12, 12, 12, 12,
    12, 12, 12, 12, 12, 12, 12, 12,
    12, 12, 12, 12, 12, 12, 12, 12,
    6, 6, 6, 6, 6, 6, 6, 6,
    9, 7, 8, 10, 11, 8, 7, 9
};

// https://github.com/official-stockfish/Stockfish/blob/master/src/bitboard.h
constexpr Bitboard FileA = 0x0101010101010101ULL;
constexpr Bitboard FileB = FileA << 1;
constexpr Bitboard FileC = FileA << 2;
constexpr Bitboard FileD = FileA << 3;
constexpr Bitboard FileE = FileA << 4;
constexpr Bitboard FileF = FileA << 5;
constexpr Bitboard FileG = FileA << 6;
constexpr Bitboard FileH = FileA << 7;

constexpr Bitboard Rank1 = 0xFF;
constexpr Bitboard Rank2 = Rank1 << (8 * 1);
constexpr Bitboard Rank3 = Rank1 << (8 * 2);
constexpr Bitboard Rank4 = Rank1 << (8 * 3);
constexpr Bitboard Rank5 = Rank1 << (8 * 4);
constexpr Bitboard Rank6 = Rank1 << (8 * 5);
constexpr Bitboard Rank7 = Rank1 << (8 * 6);
constexpr Bitboard Rank8 = Rank1 << (8 * 7);

constexpr std::array<Bitboard, 8> Files = { FileA, FileB, FileC, FileD, FileE, FileF, FileG, FileH };
constexpr std::array<Bitboard, 8> Ranks = { Rank1, Rank2, Rank3, Rank4, Rank5, Rank6, Rank7, Rank8 };