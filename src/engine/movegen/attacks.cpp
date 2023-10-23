#include "attacks.hpp"
#include "../../utils.hpp"
#include "../../constants.hpp"
#include "../../types.hpp"
#include "magic.hpp"
#include "tables.hpp"
namespace dunsparce::attacks {

Bitboard generatePawnAttacks(Square source, Color side) {
    Bitboard attack_bb{ Zero };
    
    const Bitboard pawn_bb{ One << source };

    // generate relative moves
    if((utils::shiftRel(pawn_bb, NorthWest, side)) & constants::not_filea_bb) attack_bb |= (utils::shiftRel(pawn_bb, NorthWest, side));
    if((utils::shiftRel(pawn_bb, NorthEast, side)) & constants::not_fileh_bb) attack_bb |= (utils::shiftRel(pawn_bb, NorthEast, side));

    return attack_bb;
}

[[nodiscard]] Bitboard generateKnightAttacks(Square source) {
    Bitboard attack_bb{ Zero };
    // bb with only from square
    const Bitboard knight_bb{ One << source };
    // left shifts
    if((knight_bb >> 17) & constants::not_fileh_bb)  attack_bb |= (knight_bb >> 17);
    if((knight_bb >> 15) & constants::not_filea_bb)  attack_bb |= (knight_bb >> 15);
    if((knight_bb >> 10) & constants::not_filehg_bb) attack_bb |= (knight_bb >> 10);
    if((knight_bb >> 6)  & constants::not_fileab_bb) attack_bb |= (knight_bb >> 6);

    // rights shifts
    if((knight_bb << 17) & constants::not_filea_bb)  attack_bb |= (knight_bb << 17);
    if((knight_bb << 15) & constants::not_fileh_bb)  attack_bb |= (knight_bb << 15);
    if((knight_bb << 10) & constants::not_fileab_bb) attack_bb |= (knight_bb << 10);
    if((knight_bb << 6)  & constants::not_filehg_bb) attack_bb |= (knight_bb << 6);

    return attack_bb;
}

[[nodiscard]] Bitboard generateKingAttacks(Square source) {
    Bitboard attack_bb{ Zero };
    // bb with only from square
    const Bitboard king_bb{ One << source };

    if (king_bb >> North)                                  attack_bb |= (king_bb >> North);
    if((king_bb >> NorthEast)  & constants::not_fileh_bb)  attack_bb |= (king_bb >> NorthEast);
    if((king_bb >> NorthWest)  & constants::not_filea_bb)  attack_bb |= (king_bb >> NorthWest);
    if((king_bb >> West)       & constants::not_filehg_bb) attack_bb |= (king_bb >> West);

    if (king_bb << South)                                  attack_bb |= (king_bb << South);
    if((king_bb << SouthEast)  & constants::not_filea_bb)  attack_bb |= (king_bb << SouthEast);
    if((king_bb << SouthWest)  & constants::not_fileh_bb)  attack_bb |= (king_bb << SouthWest);
    if((king_bb << West)       & constants::not_filea_bb)  attack_bb |= (king_bb << West);

    return attack_bb;
}

[[nodiscard]] Bitboard generateBishopAttacksNoBlockers(Square source) {
    Bitboard attack_bb{ Zero };
    
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
    Bitboard attack_bb{ Zero };
    
    const File o_file{ utils::getFile(source) };
    const Rank o_rank{ utils::getRank(source) };

    File file;
    Rank rank;
    
    // only need 6 bits
    // bottom-right diag
    for(file = o_file+1, rank = o_rank+1; file <= 7 && rank <= 7; ++file, ++rank) {
        Bitboard ray_br{ One << (rank * 8 + file) };
        attack_bb |= ray_br;
        // if ray is blocked, break
        if(ray_br & occupany_bb) break;
    }
    // top-right diag
    for(file = o_file+1, rank = o_rank-1; file <= 7 && rank >= 0; ++file, --rank) {
        Bitboard ray_tr{ One << (rank * 8 + file) };
        attack_bb |= ray_tr;
        // if ray is blocked, break
        if(ray_tr & occupany_bb) break;
    }
    // bottom-left diag
    for(file = o_file-1, rank = o_rank+1; file >= 0 && rank <= 7; --file, ++rank) {
        Bitboard ray_bl{ One << (rank * 8 + file) };
        attack_bb |= ray_bl;
        // if ray is blocked, break
        if(ray_bl & occupany_bb) break;
    }
    // top-left diag
    for(file = o_file-1, rank = o_rank-1; file >= 0 && rank >= 0; --file, --rank) {
        Bitboard ray_tl{ One << (rank * 8 + file) };
        attack_bb |= ray_tl;
        // if ray is blocked, break
        if(ray_tl & occupany_bb) break;
    }

    return attack_bb;
}

[[nodiscard]] Bitboard generateRookAttacksNoBlockers(Square source) {
    Bitboard attack_bb{ Zero };
    
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
    Bitboard attack_bb{ Zero };
    
    const File o_file{ utils::getFile(source) };
    const Rank o_rank{ utils::getRank(source) };

    File file;
    Rank rank;
    
    // only need 6 bits
    // North
    for(rank = o_rank+1; rank <= 7; ++rank) {
        Bitboard ray_n{ One << (rank * 8 + o_file) };
        attack_bb |= ray_n;
        // if ray is blocked, break
        if(ray_n & occupany_bb) break;
    }
    // South
    for(rank = o_rank-1; rank >= 0; --rank) {
        Bitboard ray_s{ One << (rank * 8 + o_file) };
        attack_bb |= ray_s;
        // if ray is blocked, break
        if(ray_s & occupany_bb) break;
    }
    // East
    for(file = o_file+1; file <= 7; ++file) {
        Bitboard ray_e{ One << (o_rank * 8 + file) };
        attack_bb |= ray_e;
        // if ray is blocked, break
        if(ray_e & occupany_bb) break;
    }
    // West
    for(file = o_file-1; file >= 0; --file) {
        Bitboard ray_w{ One << (o_rank * 8 + file) };
        attack_bb |= ray_w;
        // if ray is blocked, break
        if(ray_w & occupany_bb) break;
    }

    return attack_bb;
}

Bitboard getBishopAttacks(Square square, Bitboard occupancy_bb) {
    occupancy_bb &= bishops_all[square];
    occupancy_bb *= tables::magics::bishops[square];
    occupancy_bb >>= (64 - tables::relevant_bits::bishops[square]);
    return attacks::bishops[square][occupancy_bb];
}

Bitboard getRookAttacks(Square square, Bitboard occupancy_bb) {
    occupancy_bb &= rooks_all[square];
    occupancy_bb *= tables::magics::rooks[square];
    occupancy_bb >>= (64 - tables::relevant_bits::rooks[square]);
    return attacks::rooks[square][occupancy_bb];
}

Bitboard getQueenAttacks(Square square, const Bitboard& occupancy_bb) {    
    // thank goodness
    return getRookAttacks(square, occupancy_bb) | getBishopAttacks(square, occupancy_bb);
}

void initLeapersAttacks() {
    for(int i = 0; i < NSquares; ++i) {
        // pawns
        pawns[White][i] = generatePawnAttacks(Square(i), White);
        pawns[Black][i] = generatePawnAttacks(Square(i), Black);
        
        // knights
        knights[i] = generateKnightAttacks(Square(i));

        // kings
        kings[i] = generateKingAttacks(Square(i));
    }
}

void initSlidersAttacks(BishopOrRook p_type) {
    for(int i = 0; i < NSquares; ++i) {
        if(p_type == Bishop) {
            bishops_all[i] = generateBishopAttacksNoBlockers(Square(i));
        } else {
            rooks_all[i] = generateRookAttacksNoBlockers(Square(i));
        }

        Bitboard attack_bb = (p_type == Bishop) ? bishops_all[i] : rooks_all[i];
        int relevant_bits = utils::popcount(attack_bb);
        int num_permutations{ 1 << relevant_bits };
        for(int p_idx = 0; p_idx < num_permutations; ++p_idx) {
            if(p_type == Bishop) {
                Bitboard permutation_bb{ magic::generateAttackPermutation(p_idx, relevant_bits, attack_bb) };
                int magic_index{ static_cast<int>((permutation_bb * tables::magics::bishops[i]) >> (64 - tables::relevant_bits::bishops[i])) };
                attacks::bishops[i][magic_index] = generateBishopAttacksWithBlockers(Square(i), permutation_bb);
            } else {
                Bitboard permutation_bb{ magic::generateAttackPermutation(p_idx, relevant_bits, attack_bb) };
                int magic_index{ static_cast<int>((permutation_bb * tables::magics::rooks[i]) >> (64 - tables::relevant_bits::rooks[i])) };
                attacks::rooks[i][magic_index] = generateRookAttacksWithBlockers(Square(i), permutation_bb);
            }
        }
    }
}

bool isSquareAttacked(Square square, Color side, std::array<Bitboard, 12> pieces, std::array<Bitboard, 3> occupancies) {
    // attacked by pawn
    if((side == White) && (attacks::pawns[Black][square] & pieces[WPawn])) return true;
    if((side == Black) && (attacks::pawns[White][square] & pieces[BPawn])) return true;

    // attacked by knight
    if(attacks::knights[square] & (side == White ? pieces[WKnight] : pieces[BKnight])) return true;

    // attacked by king
    if(attacks::kings[square] & (side == White ? pieces[WKing] : pieces[BKing])) return true;

    // attacked by bishop
    if(attacks::getBishopAttacks(square, occupancies[Both]) & (side == White ? pieces[WBishop] : pieces[BBishop])) return true;

    // attacked by rook
    if(attacks::getRookAttacks(square, occupancies[Both]) & (side == White ? pieces[WRook] : pieces[BRook])) return true;

    // attacked by queen
    if(attacks::getQueenAttacks(square, occupancies[Both]) & (side == White ? pieces[WQueen] : pieces[BQueen])) return true;

    return false;
}

} // namespace dunsparce::attacks