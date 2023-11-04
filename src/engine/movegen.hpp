#pragma once

#include <vector>

#include "../board.hpp"
#include "../types.hpp"
#include "../bits.hpp"

namespace dunsparce {
    Bitboard generateBishopAttacksWithBlockers(Bitboard occupany_bb, Square source);
    Bitboard generateRookAttacksWithBlockers(Bitboard occupany_bb, Square source);

    Bitboard getPawnAttacks(Color side, Square source);
    Bitboard getKnightAttacks(Square source);
    Bitboard getKingAttacks(Square source);
    Bitboard getBishopAttacks(Bitboard occupancy_bb, Square source);
    Bitboard getRookAttacks(Bitboard occupancy_bb, Square source);
    Bitboard getQueenAttacks(Bitboard occupancy_bb, Square source);

    void initBishopAttacks();
    void initRookAttacks();

    bool isAttacked(const Board::BoardState& state, Square source);
}