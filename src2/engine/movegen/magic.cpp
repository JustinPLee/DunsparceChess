#include "magic.hpp"

#include <iostream>
#include <array>

#include "../../types.hpp"
#include "../../utils.hpp"
#include "../../constants.hpp"
#include "attacks.hpp"
#include "tables.hpp"
namespace dunsparce::magic {

void initMagic() {
    // for(int i = 0; i < NSquares; ++i) {
    //     tables::magics::rooks[i] = generateMagicNumber(Square(i), tables::relevant_bits::rooks[i], BaseRook);
    //     tables::magics::bishops[i] = generateMagicNumber(Square(i), tables::relevant_bits::bishops[i], BaseBishop);
    // }
   std::cout << "don't init magic\n";
}

Bitboard generateOccupancyBBPermutation(int index, int relevant_bits, Bitboard attack_bb) {
    // init occupancy
    Bitboard occupancy_bb{ Zero };
    // loop over every possible attacked squares
    for(int count = 0; count < relevant_bits; ++count) {
        // store first square
        const Square square{ utils::findLSB(attack_bb) };
        // remove square from remaining list of possible squares
        utils::popSquare(attack_bb, square);
        // only set bits under the index mask
        if(index & (1 << count)) {
            occupancy_bb |= (One << square);
        }
    }
    return occupancy_bb;
}

uint32_t reseed() {
    // xor shift randomizer
    seed ^= (seed << 13);
    seed ^= (seed >> 17);
    seed ^= (seed << 5);
    return seed;
}

Bitboard generateRandomBB() {
    // create four, random 16 bit slices
    Bitboard n1 = Bitboard{ reseed() } & 0xFFFF;
    Bitboard n2 = Bitboard{ reseed() } & 0xFFFF;
    Bitboard n3 = Bitboard{ reseed() } & 0xFFFF;
    Bitboard n4 = Bitboard{ reseed() } & 0xFFFF;
    // combine slices at the according positions
    return n1 | (n2 << 16) | (n3 << 32) | (n4 << 48);
}

Bitboard generateMagicNumber(Square source, int relevant_bits, BasePiece base_piece) {   
    /*  the max number of relevant bits is 12
        2^12 is 4096, covering all permutations
        (remember: ideally one time cost)   */
    std::array<Bitboard, 4096> occupancy_tables{ Zero };
    std::array<Bitboard, 4096> attack_tables{ Zero };
    std::array<Bitboard, 4096> used_attack_tables{ Zero };
    // get all possible attack squares
    Bitboard attack_mask = (base_piece == BaseBishop) ? attacks::generateBishopAttacksNoBlockers(source) : attacks::generateRookAttacksNoBlockers(source);
    // get num of possible permutations
    int occupancy_indicies{ 1 << relevant_bits };
    for(int index = 0; index < occupancy_indicies; ++index) {
        // populate occupancy tables with all possible attacks
        occupancy_tables[index] = generateOccupancyBBPermutation(index, relevant_bits, attack_mask);
        // populate proper attack tables with blocked attacks using occupancy tables
        // i do this to generate a properly formed ray, for example this sequence of bits for a rook is invalid: 00011001
        attack_tables[index] = (base_piece == BaseBishop) ? attacks::generateBishopAttacksWithBlockers(source, occupancy_tables[index]) : attacks::generateRookAttacksWithBlockers(source, occupancy_tables[index]);
    }
    // loop a bunch of times to find a valid magic hash
    // (this should very rarely fail)
    for(int i = 0; i < 10000000; ++i) {
        // randomly populated bitboard
        Bitboard magic_num{ generateRandomBB() & generateRandomBB() & generateRandomBB() & generateRandomBB() };
        // skip if too few bits
        if(utils::popcount((attack_mask * magic_num) & 0xFF00000000000000) < 6) continue;
        bool fail{ false };
        // loop over every permutation
        for(int index = 0; index < occupancy_indicies; ++index) {
            // plug in candidate magic_num into known formula
            int magic_index{ static_cast<int>((occupancy_tables[index] * magic_num) >> (64 - relevant_bits)) };
            // check that the magic hash correctly transforms every position
            // store seen positions in used_attack_tables
            // if the tables do not match, the magic number is invalid
            if(used_attack_tables[magic_index] == Zero) {
                used_attack_tables[magic_index] = attack_tables[index];
            } else if(used_attack_tables[magic_index] != attack_tables[index]) {
                fail = true;
                break;
            }
        }
        if(fail == false) {
            return magic_num;
        }
    }
    std::cout << "Fail\n";
    return 0ULL;
}

} // namespace dunsparce::magic