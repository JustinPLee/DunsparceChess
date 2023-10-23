#include "attacks.hpp"
#include "../../utils.hpp"
#include "../../constants.hpp"
#include "../../types.hpp"
namespace dunsparce::attacks {

    [[nodiscard]] Bitboard generateKnightAttacks(Square source) {
        Bitboard attack_bb{ ZERO };
        // bb with only from square
        const Bitboard knight_bb{ utils::squareToBB(source) };

        // left shifts
        if((knight_bb >> KNIGHT_OFFSETS[0]) & NOT_FILEH_BB)  attack_bb |= (knight_bb >> KNIGHT_OFFSETS[0]);
        if((knight_bb >> KNIGHT_OFFSETS[1]) & NOT_FILEA_BB)  attack_bb |= (knight_bb >> KNIGHT_OFFSETS[1]);
        if((knight_bb >> KNIGHT_OFFSETS[2]) & NOT_FILEHG_BB) attack_bb |= (knight_bb >> KNIGHT_OFFSETS[2]);
        if((knight_bb >> KNIGHT_OFFSETS[3]) & NOT_FILEAB_BB) attack_bb |= (knight_bb >> KNIGHT_OFFSETS[3]);

        // rights shifts
        if((knight_bb << KNIGHT_OFFSETS[0]) & NOT_FILEA_BB)  attack_bb |= (knight_bb << KNIGHT_OFFSETS[0]);
        if((knight_bb << KNIGHT_OFFSETS[1]) & NOT_FILEH_BB)  attack_bb |= (knight_bb << KNIGHT_OFFSETS[1]);
        if((knight_bb << KNIGHT_OFFSETS[2]) & NOT_FILEAB_BB) attack_bb |= (knight_bb << KNIGHT_OFFSETS[2]);
        if((knight_bb << KNIGHT_OFFSETS[3]) & NOT_FILEHG_BB) attack_bb |= (knight_bb << KNIGHT_OFFSETS[3]);

        return attack_bb;
    }

    [[nodiscard]] Bitboard generateKingAttacks(Square source) {
        Bitboard attack_bb{ ZERO };
        // bb with only from square
        const Bitboard king_bb{ utils::squareToBB(source) };

        if (king_bb >> NORTH)                       attack_bb |= (king_bb >> NORTH);
        if((king_bb >> NORTH_EAST) & NOT_FILEH_BB)  attack_bb |= (king_bb >> NORTH_EAST);
        if((king_bb >> NORTH_WEST) & NOT_FILEA_BB)  attack_bb |= (king_bb >> NORTH_WEST);
        if((king_bb >> WEST)       & NOT_FILEH_BB)  attack_bb |= (king_bb >> WEST);

        if (king_bb << SOUTH)                       attack_bb |= (king_bb << SOUTH);
        if((king_bb << SOUTH_EAST) & NOT_FILEA_BB)  attack_bb |= (king_bb << SOUTH_EAST);
        if((king_bb << SOUTH_WEST) & NOT_FILEH_BB)  attack_bb |= (king_bb << SOUTH_WEST);
        if((king_bb << WEST)       & NOT_FILEA_BB)  attack_bb |= (king_bb << WEST);

        return attack_bb;
    }

    [[nodiscard]] Bitboard generateBishopAttacksNoBlockers(Square source) {
        Bitboard attack_bb{ ZERO };
        
        const File o_file{ utils::getFile(source) };
        const Rank o_rank{ utils::getRank(source) };

        File file;
        Rank rank;
        
        // only need 6 bits
        // bottom-right diag
        for(file = o_file+1, rank = o_rank+1; file <= 6 && rank <= 6; ++file, ++rank) {
            utils::setSquare(attack_bb, utils::convertToSquare(rank, file));
        }
        // top-right diag
        for(file = o_file+1, rank = o_rank-1; file <= 6 && rank >= 1; ++file, --rank) {
            utils::setSquare(attack_bb, utils::convertToSquare(rank, file));
        }
        // bottom-left diag
        for(file = o_file-1, rank = o_rank+1; file >= 1 && rank <= 6; --file, ++rank) {
            utils::setSquare(attack_bb, utils::convertToSquare(rank, file));
        }
        // top-left diag
        for(file = o_file-1, rank = o_rank-1; file >= 1 && rank >= 1; --file, --rank) {
            utils::setSquare(attack_bb, utils::convertToSquare(rank, file));
        }

        return attack_bb;
    }

    [[nodiscard]] Bitboard generateBishopAttacksWithBlockers(Square source, const Bitboard& occupany_bb) {
        // with occupancy check
        Bitboard attack_bb{ ZERO };
        
        const File o_file{ utils::getFile(source) };
        const Rank o_rank{ utils::getRank(source) };

        File file;
        Rank rank;
        
        // only need 6 bits
        // bottom-right diag
        for(file = o_file+1, rank = o_rank+1; file <= 7 && rank <= 7; ++file, ++rank) {
            Bitboard ray_br{ utils::squareToBB(utils::convertToSquare(rank, file)) };
            attack_bb |= ray_br;
            // if ray is blocked, break
            if(ray_br & occupany_bb) break;
        }
        // top-right diag
        for(file = o_file+1, rank = o_rank-1; file <= 7 && rank >= 0; ++file, --rank) {
            Bitboard ray_tr{ utils::squareToBB(utils::convertToSquare(rank, file)) };
            attack_bb |= ray_tr;
            // if ray is blocked, break
            if(ray_tr & occupany_bb) break;
        }
        // bottom-left diag
        for(file = o_file-1, rank = o_rank+1; file >= 0 && rank <= 7; --file, ++rank) {
            Bitboard ray_bl{ utils::squareToBB(utils::convertToSquare(rank, file)) };
            attack_bb |= ray_bl;
            // if ray is blocked, break
            if(ray_bl & occupany_bb) break;
        }
        // top-left diag
        for(file = o_file-1, rank = o_rank-1; file >= 0 && rank >= 0; --file, --rank) {
            Bitboard ray_tl{ utils::squareToBB(utils::convertToSquare(rank, file)) };
            attack_bb |= ray_tl;
            // if ray is blocked, break
            if(ray_tl & occupany_bb) break;
        }

        return attack_bb;
    }

    [[nodiscard]] Bitboard generateRookAttacksNoBlockers(Square source) {
        Bitboard attack_bb{ ZERO };
        
        const File o_file{ utils::getFile(source) };
        const Rank o_rank{ utils::getRank(source) };

        File file;
        Rank rank;
        
        // only need 6 bits
        // North
        for(rank = o_rank+1; rank <= 6; ++rank) {
            utils::setSquare(attack_bb, utils::convertToSquare(rank, o_file));
        }
        // South
        for(rank = o_rank-1; rank >= 1; --rank) {
            utils::setSquare(attack_bb, utils::convertToSquare(rank, o_file));
        }
        // East
        for(file = o_file+1; file <= 6; ++file) {
            utils::setSquare(attack_bb, utils::convertToSquare(o_rank, file));
        }
        // West
        for(file = o_file-1; file >= 1; --file) {
            utils::setSquare(attack_bb, utils::convertToSquare(o_rank, file));
        }

        return attack_bb;
    }

    [[nodiscard]] Bitboard generateRookAttacksWithBlockers(Square source, const Bitboard& occupany_bb) {
        Bitboard attack_bb{ ZERO };
        
        const File o_file{ utils::getFile(source) };
        const Rank o_rank{ utils::getRank(source) };

        File file;
        Rank rank;
        
        // only need 6 bits
        // North
        for(rank = o_rank+1; rank <= 7; ++rank) {
            Bitboard ray_n{ utils::squareToBB(utils::convertToSquare(rank, o_file)) };
            attack_bb |= ray_n;
            // if ray is blocked, break
            if(ray_n & occupany_bb) break;
        }
        // South
        for(rank = o_rank-1; rank >= 0; --rank) {
            Bitboard ray_s{ utils::squareToBB(utils::convertToSquare(rank, o_file)) };
            attack_bb |= ray_s;
            // if ray is blocked, break
            if(ray_s & occupany_bb) break;
        }
        // East
        for(file = o_file+1; file <= 7; ++file) {
            Bitboard ray_e{ utils::squareToBB(utils::convertToSquare(o_rank, file)) };
            attack_bb |= ray_e;
            // if ray is blocked, break
            if(ray_e & occupany_bb) break;
        }
        // West
        for(file = o_file-1; file >= 0; --file) {
            Bitboard ray_w{ utils::squareToBB(utils::convertToSquare(o_rank, file)) };
            attack_bb |= ray_w;
            // if ray is blocked, break
            if(ray_w & occupany_bb) break;
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