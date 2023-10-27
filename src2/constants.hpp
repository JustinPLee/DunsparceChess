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

/**
 *  Files and Ranks
*/

constexpr Bitboard filea_bb{  0x101010101010101ULL  };
constexpr Bitboard fileh_bb{  0x8080808080808080ULL };
constexpr Bitboard fileab_bb{ 0x303030303030303ULL  };
constexpr Bitboard filehg_bb{ 0xC0C0C0C0C0C0C0C0ULL };

/** 
 *  Castling
*/
constexpr uint8_t castle_wk{ 0b0001 };
constexpr uint8_t castle_wq{ 0b0010 };
constexpr uint8_t castle_bk{ 0b0100 };
constexpr uint8_t castle_bq{ 0b1000 };

// to minimize if branches
// represents a 8 bit num
constexpr std::array<int, 64> castling_rights{
    7,  15, 15, 15, 3,  15, 15, 11,
    15, 15, 15, 15, 15, 15, 15, 15,
    15, 15, 15, 15, 15, 15, 15, 15,
    15, 15, 15, 15, 15, 15, 15, 15,
    15, 15, 15, 15, 15, 15, 15, 15,
    15, 15, 15, 15, 15, 15, 15, 15,
    15, 15, 15, 15, 15, 15, 15, 15,
    13, 15, 15, 15, 12, 15, 15, 14
};


}; // namespace dunsparce::constants

namespace dunsparce::constants::fens {

inline const std::string starting{ "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 0" };
inline const std::string empty{ "8/8/8/8/8/8/8/8 w - - " };
inline const std::string test{ "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq -" };

} // namespace dunsparce::constants::fens