#pragma once

#include <vector>

#include "../../types.hpp"
#include "../../constants.hpp"
#include "../../board.hpp"
namespace dunsparce::attacks {

inline std::vector<std::vector<Bitboard>> pawns(NColors-1, std::vector<Bitboard>(NSquares)); // pawns can only move in one direction
inline std::vector<Bitboard> knights(NSquares);
inline std::vector<Bitboard> kings(NSquares);

// sliders
inline std::vector<Bitboard> bishops_unblocked(NSquares);
inline std::vector<Bitboard> rooks_unblocked(NSquares);
inline std::vector<std::vector<Bitboard>> bishops(NSquares, std::vector<Bitboard>(512));
inline std::vector<std::vector<Bitboard>> rooks(NSquares, std::vector<Bitboard>(4096));

Bitboard generatePawnAttacks(Color side, Square source);
Bitboard generateKnightAttacks(Square source);
Bitboard generateBishopAttacksNoBlockers(Square source);
Bitboard generateBishopAttacksWithBlockers(Square source, const Bitboard& occupany_bb);
Bitboard generateRookAttacksNoBlockers(Square source);
Bitboard generateRookAttacksWithBlockers(Square source, const Bitboard& occupany_bb);

Bitboard getPawnAttacks(Color side, Square source);
Bitboard getKnightAttacks(Square source);
Bitboard getKingAttacks(Square source);
Bitboard getBishopAttacks(Square source, Bitboard occupancy_bb);
Bitboard getRookAttacks(Square source, Bitboard occupancy_bb);
Bitboard getQueenAttacks(Square source, const Bitboard& occupancy_bb);

void initPawnAttacks();
void initKnightAttacks();
void initBishopAttacks();
void initRookAttacks();
void initKingAttacks();
void initAllAttacks();

bool isAttacked(Square source, Color side, const Board& board);

} // namespace dunsparce::attacks