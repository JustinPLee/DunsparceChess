#include "attacks.hpp"
#include "../../utils.hpp"
#include "../../constants.hpp"
#include "../../types.hpp"
#include "../../board.hpp"
#include "magic.hpp"
#include "tables.hpp"
#include "assert.h"
namespace dunsparce::attacks {

Bitboard generatePawnAttacks(Color side, Square source) {
    Bitboard attack_bb{ Zero };
    const Bitboard pawn_bb{ One << source };
    if(side == White) {
        if((pawn_bb >> 7) & (~constants::filea_bb)) attack_bb |= (pawn_bb >> 7);
        if((pawn_bb >> 9) & (~constants::fileh_bb)) attack_bb |= (pawn_bb >> 9);
    } else {
        if((pawn_bb << 7) & (~constants::fileh_bb)) attack_bb |= (pawn_bb << 7);
        if((pawn_bb << 9) & (~constants::filea_bb)) attack_bb |= (pawn_bb << 9);
    }
    return attack_bb;
}

Bitboard generateKnightAttacks(Square source) {
    Bitboard attack_bb{ Zero };
    const Bitboard knight_bb{ One << source };

    if((knight_bb >> 17) & ~constants::fileh_bb)  attack_bb |= (knight_bb >> 17);
    if((knight_bb >> 15) & ~constants::filea_bb)  attack_bb |= (knight_bb >> 15);
    if((knight_bb >> 10) & ~constants::filehg_bb) attack_bb |= (knight_bb >> 10);
    if((knight_bb >> 6)  & ~constants::fileab_bb) attack_bb |= (knight_bb >> 6); 

    if((knight_bb << 17) & ~constants::filea_bb)  attack_bb |= (knight_bb << 17);
    if((knight_bb << 15) & ~constants::fileh_bb)  attack_bb |= (knight_bb << 15);
    if((knight_bb << 10) & ~constants::fileab_bb) attack_bb |= (knight_bb << 10);
    if((knight_bb << 6)  & ~constants::filehg_bb) attack_bb |= (knight_bb << 6);

    return attack_bb;
}

Bitboard generateKingAttacks(Square source) {
    Bitboard attack_bb{ Zero };
    const Bitboard king_bb{ One << source };

    if (king_bb >> North)                               attack_bb |= (king_bb >> North);
    if((king_bb >> NorthEast)  & ~constants::fileh_bb)  attack_bb |= (king_bb >> NorthEast);
    if((king_bb >> NorthWest)  & ~constants::filea_bb)  attack_bb |= (king_bb >> NorthWest);
    if((king_bb >> West)       & ~constants::fileh_bb)  attack_bb |= (king_bb >> West);   

    if (king_bb << South)                               attack_bb |= (king_bb << South);
    if((king_bb << SouthEast)  & ~constants::filea_bb)  attack_bb |= (king_bb << SouthEast);
    if((king_bb << SouthWest)  & ~constants::fileh_bb)  attack_bb |= (king_bb << SouthWest);
    if((king_bb << West)       & ~constants::filea_bb)  attack_bb |= (king_bb << West);

    return attack_bb;
}

Bitboard generateBishopAttacksNoBlockers(Square source) {
    Bitboard attack_bb{ Zero };
    const int source_rank{ rank_of(source) };
    const int source_file{ file_of(source) };
    // only need 6 bits
    // bottom-right diag
    for(int rank = source_rank+1, file = source_file+1; rank <= 6 && file <= 6; ++rank, ++file) {
        attack_bb |= (One << get_square_index(rank, file));
    }
    // top-right diag
    for(int rank = source_rank-1, file = source_file+1; rank >= 1 && file <= 6; --rank, ++file) {
        attack_bb |= (One << get_square_index(rank, file));
    }
    // bottom-left diag
    for(int rank = source_rank+1, file = source_file-1; rank <= 6 && file >= 1; ++rank, --file) {
        attack_bb |= (One << get_square_index(rank, file));
    }
    // top-left diag
    for(int rank = source_rank-1, file = source_file-1; rank >= 1 && file >= 1; --rank, --file) {
        attack_bb |= (One << get_square_index(rank, file));
    }

    return attack_bb;
}

Bitboard generateBishopAttacksWithBlockers(Square source, const Bitboard& occupany_bb) {
    Bitboard attack_bb{ Zero };
    const int source_rank{ rank_of(source) };
    const int source_file{ file_of(source) };
    // SE
    for(int rank = source_rank+1, file = source_file+1; rank <= 7 && file <= 7; ++rank, ++file) {
        Bitboard ray_br{ One << get_square_index(rank, file) };
        attack_bb |= ray_br;
        if(ray_br & occupany_bb) break;
    }
    // NE
    for(int rank = source_rank-1, file = source_file+1; rank >= 0 && file <= 7; --rank, ++file) {
        Bitboard ray_tr{ One << get_square_index(rank, file) };
        attack_bb |= ray_tr;
        if(ray_tr & occupany_bb) break;
    }
    // SW
    for(int rank = source_rank+1, file = source_file-1; rank <= 7 && file >= 0; ++rank, --file) {
        Bitboard ray_bl{ One << get_square_index(rank, file) };
        attack_bb |= ray_bl;
        if(ray_bl & occupany_bb) break;
    }
    // NW
    for(int rank = source_rank-1, file = source_file-1; rank >= 0 && file >= 0; --rank, --file) {
        Bitboard ray_tl{ One << get_square_index(rank, file) };
        attack_bb |= ray_tl;
        if(ray_tl & occupany_bb) break;
    }

    return attack_bb;
}

Bitboard generateRookAttacksNoBlockers(Square source) {
    Bitboard attack_bb{ Zero };
    const int source_rank{ rank_of(source) };
    const int source_file{ file_of(source) };
    // North
    for(int rank = source_rank+1; rank <= 6; ++rank) {
        attack_bb |= (One << get_square_index(rank, source_file));
    }
    // South
    for(int rank = source_rank-1; rank >= 1; --rank) {
        attack_bb |= (One << get_square_index(rank, source_file));
    }
    // East
    for(int file = source_file+1; file <= 6; ++file) {
        attack_bb |= (One << get_square_index(source_rank, file));
    }
    // West
    for(int file = source_file-1; file >= 1; --file) {
        attack_bb |= (One << get_square_index(source_rank, file));
    }

    return attack_bb;
}

Bitboard generateRookAttacksWithBlockers(Square source, const Bitboard& occupany_bb) {
    Bitboard attack_bb{ Zero };
    const int source_rank{ rank_of(source) };
    const int source_file{ file_of(source) };    
    // North
    for(int rank = source_rank+1; rank <= 7; ++rank) {
        Bitboard ray_n{ One << get_square_index(rank, source_file) };
        attack_bb |= ray_n;
        if(ray_n & occupany_bb) break;
    }
    // South
    for(int rank = source_rank-1; rank >= 0; --rank) {
        Bitboard ray_s{ One << get_square_index(rank, source_file) };
        attack_bb |= ray_s;
        if(ray_s & occupany_bb) break;
    }
    // East
    for(int file = source_file+1; file <= 7; ++file) {
        Bitboard ray_e{ One << get_square_index(source_rank, file) };
        attack_bb |= ray_e;
        if(ray_e & occupany_bb) break;
    }
    // West
    for(int file = source_file-1; file >= 0; --file) {
        Bitboard ray_w{ One << get_square(source_rank, file) };
        attack_bb |= ray_w;
        if(ray_w & occupany_bb) break;
    }

    return attack_bb;
}

Bitboard getPawnAttacks(Color side, Square source) {
    return attacks::pawns[side][source];
}
Bitboard getKnightAttacks(Square source) {
    return attacks::knights[source];
}
Bitboard getKingAttacks(Square source) {
    return attacks::kings[source];
}

Bitboard getBishopAttacks(Square source, Bitboard occupancy_bb) {
    occupancy_bb &= bishops_unblocked[source];
    occupancy_bb *= tables::magics::bishops[source];
    occupancy_bb >>= (64 - tables::relevant_bits::bishops[source]);
    return attacks::bishops[source][occupancy_bb];
}

Bitboard getRookAttacks(Square source, Bitboard occupancy_bb) {
    occupancy_bb &= rooks_unblocked[source];
    occupancy_bb *= tables::magics::rooks[source];
    occupancy_bb >>= 64 - tables::relevant_bits::rooks[source];
    return attacks::rooks[source][occupancy_bb];
}

Bitboard getQueenAttacks(Square source, const Bitboard& occupancy_bb) {    
    // thank goodness
    return getRookAttacks(source, occupancy_bb) | getBishopAttacks(source, occupancy_bb);
}

void initPawnAttacks() {
    for(int square = 0; square < NSquares; ++square) {
        pawns[White][square] = generatePawnAttacks(White, Square(square));
        pawns[Black][square] = generatePawnAttacks(Black, Square(square));
    }
}

void initKnightAttacks() {
    for(int square = 0; square < NSquares; ++square) {
        knights[square] = generateKnightAttacks(Square(square));
    }
}

void initKingAttacks() {
    for(int square = 0; square < NSquares; ++square) {
        kings[square] = generateKingAttacks(Square(square));
    }
}

void initBishopAttacks() {
    for(int square = 0; square < NSquares; ++square) {
        bishops_unblocked[square] = generateBishopAttacksNoBlockers(Square(square));
        const Bitboard attack_bb{ bishops_unblocked[square] };
        const int relevant_bits{ utils::popcount(attack_bb) };
        const int num_permutations{ 1 << relevant_bits };
        for(int p_idx = 0; p_idx < num_permutations; ++p_idx) {
            const Bitboard permutation_bb{ magic::generateOccupancyBBPermutation(p_idx, relevant_bits, attack_bb) };
            const int magic_index{ static_cast<int>((permutation_bb * tables::magics::bishops[square]) >> (64 - tables::relevant_bits::bishops[square])) };
            attacks::bishops[square][magic_index] = generateBishopAttacksWithBlockers(Square(square), permutation_bb);
        }
    }
}

void initRookAttacks() {
    for(int square = 0; square < NSquares; ++square) {
        rooks_unblocked[square] = generateRookAttacksNoBlockers(Square(square));
        const Bitboard attack_bb{ rooks_unblocked[square] };
        const int relevant_bits{ utils::popcount(attack_bb) };
        const int num_permutations{ 1 << relevant_bits };
        for(int p_idx = 0; p_idx < num_permutations; ++p_idx) {
            const Bitboard permutation_bb{ magic::generateOccupancyBBPermutation(p_idx, relevant_bits, attack_bb) };
            const int magic_index{ static_cast<int>((permutation_bb * tables::magics::rooks[square]) >> (64 - tables::relevant_bits::rooks[square])) };
            attacks::rooks[square][magic_index] = generateRookAttacksWithBlockers(Square(square), permutation_bb);
        }
    }   
}

void initAllAttacks() {
    initPawnAttacks();
    initKnightAttacks();
    initBishopAttacks();
    initRookAttacks();
    initKingAttacks();
}

bool isAttacked(Square source, Color side, const Board& board) {
    // cast ray from source square using every piece type
    if((getPawnAttacks(utils::oppSide(side), source) & board.get_piece_bb(side, BasePawn))) return true;

    if(getKnightAttacks(source) & board.get_piece_bb(side, BaseKnight)) return true;

    if(getBishopAttacks(source, board.get_occupancy_bb(Both)) & board.get_piece_bb(side, BaseBishop)) return true;

    if(getRookAttacks(source, board.get_occupancy_bb(Both)) & board.get_piece_bb(side, BaseRook)) return true;
    
    if(getKingAttacks(source) & board.get_piece_bb(side, BaseKing)) return true;

    if(getQueenAttacks(source, board.get_occupancy_bb(Both)) & board.get_piece_bb(side, BaseQueen)) return true;

    return false;
}

} // namespace dunsparce::attacks