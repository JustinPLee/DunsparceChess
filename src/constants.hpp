#pragma once

#include <array>
#include <string_view>

#include "types.hpp"

namespace dunsparce {

constexpr uint64_t ONE{ 1ULL };
constexpr uint64_t ZERO{ 0ULL };

/**
 * Piece Values
*/
constexpr int PAWN_VALUE{ 100 };
constexpr int KNIGHT_VALUE{ 320 };
constexpr int BISHOP_VALUE{ 330 };
constexpr int ROOK_VALUE{ 500 };
constexpr int QUEEN_VALUE{ 900 };
constexpr int KING_VALUE{ 10000 };
constexpr int CHECKMATE_VALUE{ KING_VALUE };

/**
 *  Chess Setup
*/
constexpr int MAX_PLY{ 64 };
constexpr int MAX_MOVES{ 256 };

constexpr std::string_view STARTING_FEN{ "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 0" };

constexpr std::array<std::string_view, 64> SQUARE_NAMES {
    "a8" "b8" "c8" "d8" "e8" "f8" "g8" "h8"
    "a7" "b7" "c7" "d7" "e7" "f7" "g7" "h7"
    "a6" "b6" "c6" "d6" "e6" "f6" "g6" "h6"
    "a5" "b5" "c5" "d5" "e5" "f5" "g5" "h5"
    "a4" "b4" "c4" "d4" "e4" "f4" "g4" "h4"
    "a3" "b3" "c3" "d3" "e3" "f3" "g3" "h3"
    "a2" "b2" "c2" "d2" "e2" "f2" "g2" "h2"
    "a1" "b1" "c1" "d1" "e1" "f1" "g1" "h1"
};

constexpr std::array<int, 4> KNIGHT_OFFSETS{ 17, 15, 10, 6 };


/**
 *  Files and Ranks
*/

constexpr Bitboard NOT_FILEA_BB{  ~0x101010101010101ULL  };
constexpr Bitboard NOT_FILEH_BB{  ~0x8080808080808080ULL };
constexpr Bitboard NOT_FILEAB_BB{ ~0x303030303030303ULL  };
constexpr Bitboard NOT_FILEHG_BB{ ~0xC0C0C0C0C0C0C0C0ULL };

/** 
 *  Castling
*/
constexpr uint8_t CASTLE_BLACK_KING{  0b0001 };
constexpr uint8_t CASTLE_BLACK_QUEEN{ 0b0010 };
constexpr uint8_t CASTLE_WHITE_KING{  0b0100 };
constexpr uint8_t CASTLE_WHITE_QUEEN{ 0b1000 };

};