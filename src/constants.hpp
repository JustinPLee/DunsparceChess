#pragma once

#include <array>
#include <string_view>

#include "types.hpp"

namespace dunsparce::constants {
/**
 * Piece Values
*/
constexpr int pawn_value{ 100 };
constexpr int knight_value{ 320 };
constexpr int bishop_value{ 330 };
constexpr int rook_value{ 500 };
constexpr int queen_value{ 900 };
constexpr int king_value{ 10000 };
constexpr int checkmate_value{ king_value };

/**
 *  Chess Setup
*/
constexpr int max_ply{ 64 };
constexpr int max_moves{ 256 };

/**
 *  Files and Ranks
*/

constexpr Bitboard not_filea_bb{  ~0x101010101010101ULL  };
constexpr Bitboard not_fileh_bb{  ~0x8080808080808080ULL };
constexpr Bitboard not_fileab_bb{ ~0x303030303030303ULL  };
constexpr Bitboard not_filehg_bb{ ~0xC0C0C0C0C0C0C0C0ULL };

/** 
 *  Castling
*/
constexpr uint8_t castle_wk{  0b0001 };
constexpr uint8_t castle_wq{ 0b0010 };
constexpr uint8_t castle_bk{  0b0100 };
constexpr uint8_t castle_bq{ 0b1000 };

}; // namespace dunsparce::constants

namespace dunsparce::constants::fens {

inline const std::string starting{ "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 0" };
inline const std::string empty{ "8/8/8/8/8/8/8/8 w - - " };

} // namespace dunsparce::constants::fens