#pragma once

#include <array>
#include <string_view>

#include "bitboard.hpp"
#include "types.hpp"


/**
 * Piece Values
*/
constexpr int PAWN_VALUE   = 100;
constexpr int KNIGHT_VALUE = 320;
constexpr int BISHOP_VALUE = 330;
constexpr int ROOK_VALUE   = 500;
constexpr int QUEEN_VALUE  = 900;
constexpr int KING_VALUE   = 10000;

/**
 *  Chess Setup
*/
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
const Bitboard FILEA_BB = Bitboard(0x0101010101010101ULL);
const Bitboard FILEB_BB = FILEA_BB << 1;
const Bitboard FILEC_BB = FILEA_BB << 2;
const Bitboard FILED_BB = FILEA_BB << 3;
const Bitboard FILEE_BB = FILEA_BB << 4;
const Bitboard FILEF_BB = FILEA_BB << 5;
const Bitboard FILEG_BB = FILEA_BB << 6;
const Bitboard FILEH_BB = FILEA_BB << 7;

const Bitboard RANK1_BB = Bitboard(0xFF);
const Bitboard RANK2_BB = RANK1_BB << (8 * 1);
const Bitboard RANK3_BB = RANK1_BB << (8 * 2);
const Bitboard RANK4_BB = RANK1_BB << (8 * 3);
const Bitboard RANK5_BB = RANK1_BB << (8 * 4);
const Bitboard RANK6_BB = RANK1_BB << (8 * 5);
const Bitboard RANK7_BB = RANK1_BB << (8 * 6);
const Bitboard RANK8_BB = RANK1_BB << (8 * 7);

/** 
 *  Castling
*/
constexpr uint8_t CASTLE_BLACK_KING  = 1;
constexpr uint8_t CASTLE_BLACK_QUEEN = 2;
constexpr uint8_t CASTLE_WHITE_KING  = 4;
constexpr uint8_t CASTLE_WHITE_QUEEN = 8;