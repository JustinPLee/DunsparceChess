#pragma once

#include <array>

#include "../../types.hpp"
#include "../../constants.hpp"
#include "../../board.hpp"
namespace dunsparce::attacks {

inline std::array<std::array<Bitboard, NColors>, NSquares> pawns; // pawns can only move in one direction
inline std::array<Bitboard, NSquares> knights;
inline std::array<Bitboard, NSquares> kings;

// sliders
inline std::array<Bitboard, NSquares> bishops_all;
inline std::array<Bitboard, NSquares> rooks_all;
inline std::array<std::array<Bitboard, NSquares>, 512> bishops;
inline std::array<std::array<Bitboard, NSquares>, 4096> rooks;

Bitboard generatePawnAttacks(Color side, Square source);

Bitboard generateKnightAttacks(Square source);

Bitboard generateBishopAttacksNoBlockers(Square source);

Bitboard generateBishopAttacksWithBlockers(Square source, const Bitboard& occupany_bb);

Bitboard generateRookAttacksNoBlockers(Square source);

Bitboard generateRookAttacksWithBlockers(Square source, const Bitboard& occupany_bb);

Bitboard getBishopAttacks(Square source, Bitboard occupancy_bb);
Bitboard getRookAttacks(Square source, Bitboard occupancy_bb);
Bitboard getQueenAttacks(Square source, const Bitboard& occupancy_bb);

bool isSquareAttacked(Square source, Color side, const Board& board);

void initPawnAttacks();
void initKnightAttacks();
void initBishopAttacks();
void initRookAttacks();
void initKingAttacks();
void initAllAttacks();

} // namespace dunsparce::attacks