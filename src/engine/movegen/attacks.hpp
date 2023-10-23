#pragma once

#include <array>

#include "../../types.hpp"
#include "../../constants.hpp"

namespace dunsparce::attacks {

inline std::array<std::array<Bitboard, NColors>, NSquares> pawns; // pawns can only move in one direction
inline std::array<Bitboard, NSquares> knights;
inline std::array<Bitboard, NSquares> kings;

// sliders
inline std::array<Bitboard, NSquares> bishops_all;
inline std::array<Bitboard, NSquares> rooks_all;
inline std::array<std::array<Bitboard, NSquares>, 512> bishops;
inline std::array<std::array<Bitboard, NSquares>, 4096> rooks;

Bitboard generatePawnAttacks(Square source, Color side);

Bitboard generateKnightAttacks(Square source);

Bitboard generateBishopAttacksNoBlockers(Square source);

Bitboard generateBishopAttacksWithBlockers(Square source, const Bitboard& occupany_bb);

Bitboard generateRookAttacksNoBlockers(Square source);

Bitboard generateRookAttacksWithBlockers(Square source, const Bitboard& occupany_bb);

Bitboard getBishopAttacks(Square square, Bitboard occupancy_bb);
Bitboard getRookAttacks(Square square, Bitboard occupancy_bb);
Bitboard getQueenAttacks(Square square, const Bitboard& occupancy_bb);

bool isSquareAttacked(Square square, Color side, const std::array<Bitboard, NPieces>& pieces, const Bitboard& occupancy_bb);

void initLeapersAttacks();
void initSlidersAttacks(BishopOrRook p_type);

} // namespace dunsparce::attacks