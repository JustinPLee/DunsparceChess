#pragma once

#include <array>

#include "../../types.hpp"
#include "../../constants.hpp"
#include "../../utils.hpp"

namespace dunsparce::attacks {

    inline std::array<std::array<Bitboard, N_COLORS>, N_SQUARES> pawns; // pawns can only move in one direction
    inline std::array<Bitboard, N_SQUARES> knights;
    inline std::array<Bitboard, N_SQUARES> kings;

    template <Color to_move>
    inline Bitboard generatePawnAttacks(Square square) {
        Bitboard attack_bb{ uint64_t{0} };
        // bb with only from square
        const Bitboard pawn_bb{ utils::squareToBB(square) };

        // generate relative moves
        if((utils::shiftRel<to_move>(pawn_bb, NORTH_WEST)) & (~FILEA_BB)) attack_bb |= (utils::shiftRel<to_move>(pawn_bb, NORTH_WEST));
        if((utils::shiftRel<to_move>(pawn_bb, NORTH_EAST)) & (~FILEH_BB)) attack_bb |= (utils::shiftRel<to_move>(pawn_bb, NORTH_EAST));
    
        return attack_bb;
    }

    Bitboard generateKnightAttacks(Square square);

    Bitboard generateBishopAttacksNoBlockers(Square square);

    Bitboard generateBishopAttacksWithBlockers(Square square, const Bitboard& occupany_bb);

    Bitboard generateRookAttacksNoBlockers(Square square);

    Bitboard generateRookAttacksWithBlockers(Square square, const Bitboard& occupany_bb);

    void initLeapersAttacks();

} // namespace dunsparce::attacks