#include "attacks.hpp"
#include "../../utils.hpp"
#include "../../constants.hpp"
#include "../../types.hpp"
namespace dunsparce::attacks {

    Bitboard generateKnightAttacks(Square square) {
        Bitboard attack_bb{ uint64_t{0} };
        // bb with only from square
        const Bitboard knight_bb{ utils::squareToBB(square) };

        // left shifts
        if((knight_bb >> KNIGHT_OFFSETS[0]) & (~FILEH_BB)) attack_bb |= (knight_bb >> KNIGHT_OFFSETS[0]);
        if((knight_bb >> KNIGHT_OFFSETS[1]) & (~FILEA_BB)) attack_bb |= (knight_bb >> KNIGHT_OFFSETS[1]);
        if((knight_bb >> KNIGHT_OFFSETS[2]) & (~FILEHG_BB)) attack_bb |= (knight_bb >> KNIGHT_OFFSETS[2]);
        if((knight_bb >> KNIGHT_OFFSETS[3]) & (~FILEAB_BB)) attack_bb |= (knight_bb >> KNIGHT_OFFSETS[3]);

        // rights shifts
        if((knight_bb << KNIGHT_OFFSETS[0]) & (~FILEA_BB)) attack_bb |= (knight_bb << KNIGHT_OFFSETS[0]);
        if((knight_bb << KNIGHT_OFFSETS[1]) & (~FILEH_BB)) attack_bb |= (knight_bb << KNIGHT_OFFSETS[1]);
        if((knight_bb << KNIGHT_OFFSETS[2]) & (~FILEAB_BB)) attack_bb |= (knight_bb << KNIGHT_OFFSETS[2]);
        if((knight_bb << KNIGHT_OFFSETS[3]) & (~FILEHG_BB)) attack_bb |= (knight_bb << KNIGHT_OFFSETS[3]);

        return attack_bb;
    }

    Bitboard generateKingAttacks(Square square) {
        Bitboard attack_bb{ uint64_t{0} };
        // bb with only from square
        const Bitboard king_bb{ utils::squareToBB(square) };

        if (king_bb >> NORTH)                       attack_bb |= (king_bb >> NORTH);
        if((king_bb >> NORTH_EAST) & (~FILEH_BB))   attack_bb |= (king_bb >> NORTH_EAST);
        if((king_bb >> NORTH_WEST) & (~FILEA_BB))   attack_bb |= (king_bb >> NORTH_WEST);
        if((king_bb >> WEST)       & (~FILEH_BB))   attack_bb |= (king_bb >> WEST);

        if (king_bb << SOUTH)                       attack_bb |= (king_bb << SOUTH);
        if((king_bb << SOUTH_EAST) & (~FILEA_BB))   attack_bb |= (king_bb << SOUTH_EAST);
        if((king_bb << SOUTH_WEST) & (~FILEH_BB))   attack_bb |= (king_bb << SOUTH_WEST);
        if((king_bb << WEST)       & (~FILEA_BB))   attack_bb |= (king_bb << WEST);

        return attack_bb;
    }

    Bitboard generateBishopAttacksNoBlockers(Square square) {
        Bitboard attack_bb{ uint64_t{0} };
        
        int o_file = square % 8;
        int o_rank = square / 8;

        int file, rank;
        
        // only need 6 bits
        // bottom-right diag
        for(file = o_file+1, rank = o_rank+1; file <= 6 && rank <= 6; ++file, ++rank) {attack_bb |= utils::squareToBB(utils::getSquare(Rank(rank), File(file))); }
        // top-right diag
        for(file = o_file+1, rank = o_rank-1; file <= 6 && rank >= 1; ++file, --rank) {attack_bb |= utils::squareToBB(utils::getSquare(Rank(rank), File(file))); }
        // bottom-left diag
        for(file = o_file-1, rank = o_rank+1; file >= 1 && rank <= 6; --file, ++rank) {attack_bb |= utils::squareToBB(utils::getSquare(Rank(rank), File(file))); }
        // top-left diag
        for(file = o_file-1, rank = o_rank-1; file >= 1 && rank >= 1; --file, --rank) {attack_bb |= utils::squareToBB(utils::getSquare(Rank(rank), File(file))); }

        return attack_bb;
    }

    Bitboard generateBishopAttacksWithBlockers(Square square, const Bitboard& occupany_bb) {
        // with occupancy check
        Bitboard attack_bb{ uint64_t{0} };
        
        int o_file = square % 8;
        int o_rank = square / 8;

        int file, rank;
        
        // only need 6 bits
        // bottom-right diag
        for(file = o_file+1, rank = o_rank+1; file <= 7 && rank <= 7; ++file, ++rank) {
            auto attack = utils::squareToBB(utils::getSquare(Rank(rank), File(file)));
            attack_bb |= attack;
            // if ray is blocked, break
            if(attack & occupany_bb) break;
        }
        // top-right diag
        for(file = o_file+1, rank = o_rank-1; file <= 7 && rank >= 0; ++file, --rank) {
            auto attack = utils::squareToBB(utils::getSquare(Rank(rank), File(file)));
            attack_bb |= attack;
            // if ray is blocked, break
            if(attack & occupany_bb) break;
        }
        // bottom-left diag
        for(file = o_file-1, rank = o_rank+1; file >= 0 && rank <= 7; --file, ++rank) {
            auto attack = utils::squareToBB(utils::getSquare(Rank(rank), File(file)));
            attack_bb |= attack;
            // if ray is blocked, break
            if(attack & occupany_bb) break;
        }
        // top-left diag
        for(file = o_file-1, rank = o_rank-1; file >= 0 && rank >= 0; --file, --rank) {
            auto attack = utils::squareToBB(utils::getSquare(Rank(rank), File(file)));
            attack_bb |= attack;
            // if ray is blocked, break
            if(attack & occupany_bb) break;
        }

        return attack_bb;
    }

    Bitboard generateRookAttacksNoBlockers(Square square) {
        Bitboard attack_bb{ uint64_t{0} };
        
        int o_file = square % 8;
        int o_rank = square / 8;

        int file, rank;
        
        // only need 6 bits
        // North
        for(rank = o_rank+1; rank <= 6; ++rank) attack_bb |= utils::squareToBB(utils::getSquare(Rank(rank), File(o_file)));
        // South
        for(rank = o_rank-1; rank >= 1; --rank) attack_bb |= utils::squareToBB(utils::getSquare(Rank(rank), File(o_file)));
        // East
        for(file = o_file+1; file <= 6; ++file) attack_bb |= utils::squareToBB(utils::getSquare(Rank(o_rank), File(file)));
        // West
        for(file = o_file-1; file >= 1; --file) attack_bb |= utils::squareToBB(utils::getSquare(Rank(o_rank), File(file)));

        return attack_bb;
    }

    Bitboard generateRookAttacksWithBlockers(Square square, const Bitboard& occupany_bb) {
        Bitboard attack_bb{ uint64_t{0} };
        
        int o_file = square % 8;
        int o_rank = square / 8;

        int file, rank;
        
        // only need 6 bits
        // North
        for(rank = o_rank+1; rank <= 7; ++rank) {
            auto attack = utils::squareToBB(utils::getSquare(Rank(rank), File(o_file)));
            attack_bb |= attack;
            // if ray is blocked, break
            if(attack & occupany_bb) break;
        }
        // South
        for(rank = o_rank-1; rank >= 0; --rank) {
            auto attack = utils::squareToBB(utils::getSquare(Rank(rank), File(o_file)));
            attack_bb |= attack;
            // if ray is blocked, break
            if(attack & occupany_bb) break;
        }
        // East
        for(file = o_file+1; file <= 7; ++file) {
            auto attack = utils::squareToBB(utils::getSquare(Rank(o_rank), File(file)));
            attack_bb |= attack;
            // if ray is blocked, break
            if(attack & occupany_bb) break;
        }
        // West
        for(file = o_file-1; file >= 0; --file) {
            auto attack = utils::squareToBB(utils::getSquare(Rank(o_rank), File(file)));
            attack_bb |= attack;
            // if ray is blocked, break
            if(attack & occupany_bb) break;
        }

        return attack_bb;
    }

    void initLeapersAttacks() {
        for(int i = 0; i < N_SQUARES; ++i) {
            // pawns
            pawns[WHITE][i] = generatePawnAttacks<WHITE>(Square(i));
            pawns[BLACK][i] = generatePawnAttacks<BLACK>(Square(i));
            
            // knights
            knights[i] = generateKnightAttacks(Square(i));

            // kings
            kings[i] = generateKingAttacks(Square(i));
        }
    }
}