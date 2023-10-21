#pragma once

#include <array>
#include <string_view>

#include "bitboard.hpp"
#include "types.hpp"

namespace dunsparce {

/**
 * Piece Values
*/
constexpr int PAWN_VALUE   = 100;
constexpr int KNIGHT_VALUE = 320;
constexpr int BISHOP_VALUE = 330;
constexpr int ROOK_VALUE   = 500;
constexpr int QUEEN_VALUE  = 900;
constexpr int KING_VALUE   = 10000;
constexpr int CHECKMATE_VALUE = KING_VALUE;

/**
 *  Chess Setup
*/
constexpr int MAX_PLY = 64;
constexpr int MAX_MOVES = 256;

constexpr std::string_view STARTING_FEN = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 0";

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
/**
 *  Files and Ranks
*/
constexpr uint64_t FILEA_BB = 0x0101010101010101ULL;
constexpr uint64_t FILEB_BB = FILEA_BB << 1;
constexpr uint64_t FILEC_BB = FILEA_BB << 2;
constexpr uint64_t FILED_BB = FILEA_BB << 3;
constexpr uint64_t FILEE_BB = FILEA_BB << 4;
constexpr uint64_t FILEF_BB = FILEA_BB << 5;
constexpr uint64_t FILEG_BB = FILEA_BB << 6;
constexpr uint64_t FILEH_BB = FILEA_BB << 7;
constexpr std::array<uint64_t, 64> FILES = { FILEA_BB, FILEB_BB, FILEC_BB, FILED_BB, FILEE_BB, FILEF_BB, FILEG_BB, FILEH_BB};

constexpr uint64_t RANK1_BB = 0xFF;
constexpr uint64_t RANK2_BB = RANK1_BB << (8 * 1);
constexpr uint64_t RANK3_BB = RANK1_BB << (8 * 2);
constexpr uint64_t RANK4_BB = RANK1_BB << (8 * 3);
constexpr uint64_t RANK5_BB = RANK1_BB << (8 * 4);
constexpr uint64_t RANK6_BB = RANK1_BB << (8 * 5);
constexpr uint64_t RANK7_BB = RANK1_BB << (8 * 6);
constexpr uint64_t RANK8_BB = RANK1_BB << (8 * 7);
constexpr std::array<uint64_t, 64> RANKS = { RANK1_BB, RANK2_BB, RANK3_BB, RANK4_BB, RANK5_BB, RANK6_BB, RANK7_BB, RANK8_BB };

/** 
 *  Castling
*/
constexpr uint8_t CASTLE_BLACK_KING  = 1;
constexpr uint8_t CASTLE_BLACK_QUEEN = 2;
constexpr uint8_t CASTLE_WHITE_KING  = 4;
constexpr uint8_t CASTLE_WHITE_QUEEN = 8;

};