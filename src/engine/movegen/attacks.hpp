#pragma once

#include <array>

#include "../../types.hpp"
#include "../../constants.hpp"
#include "../../utils.hpp"

namespace dunsparce::attacks {
    inline std::array<std::array<Bitboard, N_COLORS>, N_SQUARES> pawns; // pawns can only move in one direction
    inline std::array<Bitboard, N_SQUARES> knights;
    inline std::array<Bitboard, N_SQUARES> kings;

    // sliders
    inline std::array<Bitboard, N_SQUARES> bishops_all;
    inline std::array<Bitboard, N_SQUARES> rooks_all;
    inline std::array<std::array<Bitboard, N_SQUARES>, 512> bishops;
    inline std::array<std::array<Bitboard, N_SQUARES>, 4096> rooks;

    template <Color to_move>
    inline Bitboard generatePawnAttacks(Square source) {
        Bitboard attack_bb{ ZERO };
        // bb with only from square
        const Bitboard pawn_bb{ utils::squareToBB(source) };

        // generate relative moves
        if((utils::shiftRel<to_move>(pawn_bb, NORTH_WEST)) & NOT_FILEA_BB) attack_bb |= (utils::shiftRel<to_move>(pawn_bb, NORTH_WEST));
        if((utils::shiftRel<to_move>(pawn_bb, NORTH_EAST)) & NOT_FILEH_BB) attack_bb |= (utils::shiftRel<to_move>(pawn_bb, NORTH_EAST));
    
        return attack_bb;
    }

    Bitboard generateKnightAttacks(Square source);

    Bitboard generateBishopAttacksNoBlockers(Square source);

    Bitboard generateBishopAttacksWithBlockers(Square source, const Bitboard& occupany_bb);

    Bitboard generateRookAttacksNoBlockers(Square source);

    Bitboard generateRookAttacksWithBlockers(Square source, const Bitboard& occupany_bb);

    Bitboard generateBishopMagicAttacks(Square square, Bitboard occupancy_bb);
    Bitboard generateRookMagicAttacks(Square square, Bitboard occupancy_bb);

    void initLeapersAttacks();
    void initSlidersAttacks(PieceType p_type);
} // namespace dunsparce::attacks