#include "magic.hpp"

#include <iostream>
#include <array>
#include <stdio.h>

#include "../../types.hpp"
#include "../../utils.hpp"
#include "../../constants.hpp"
#include "attacks.hpp"
#include "tables.hpp"

namespace dunsparce::magic {

    void init() {
        for(int i = 0; i < N_SQUARES; ++i) {
            std::cout << (hash(Square(i), tables::relevant_bits::rooks[i], ROOK)) << "ULL,\n";
            std::cout << (hash(Square(i), tables::relevant_bits::bishops[i], BISHOP)) << "ULL,\n";
        }
    }

    Bitboard generateAttackPermutation(int index, int relevant_bits, Bitboard attack_bb) {

        // init occupancy
        Bitboard occupancy_bb{ ZERO };

        // loop over every possible attacked squares
        for(int nth_bit = 0; nth_bit < relevant_bits; ++nth_bit) {

            // store first square
            const Square square{ utils::getFirstSquare(attack_bb) };
            
            // only set bits under the index mask
            if(index & (ONE << nth_bit)) {
                utils::setSquare(occupancy_bb, square);
            }

            // remove square from remaining list of possible squares
            utils::popSquare(attack_bb, square);
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

    Bitboard generateMagicNumber() {
        // slice bits up to 16
        const auto randMagicNumber = []() {

            // create four, random 16 bit slices
            Bitboard n1 = Bitboard{ reseed() } & 0xFFFF;
            Bitboard n2 = Bitboard{ reseed() } & 0xFFFF;
            Bitboard n3 = Bitboard{ reseed() } & 0xFFFF;
            Bitboard n4 = Bitboard{ reseed() } & 0xFFFF;

            // combine slices at the according positions
            return n1 | (n2 << 16) | (n3 << 32) | (n4 << 48);
        };

        // further randomize magic number
        return randMagicNumber() & randMagicNumber() & randMagicNumber() & randMagicNumber();
    }

    Bitboard hash(Square source, int relevant_bits, PieceType p_type) {   

        /*  the max number of relevant bits is 12
            2^12 is 4096, covering all permutations
            (remember: ideally one time cost)   */

        //
        std::array<Bitboard, 4096> occupancy_tables{ ZERO };
        
        std::array<Bitboard, 4096> attack_tables{ ZERO };
        
        std::array<Bitboard, 4096> used_attack_tables{ ZERO };

        // get all possible attack squares
        Bitboard attack_bb = (p_type == BISHOP) ? attacks::generateBishopAttacksNoBlockers(source) : attacks::generateRookAttacksNoBlockers(source);
    
        // get num of possible permutations
        int num_permutations{ 1 << relevant_bits };
        
        for(int p_idx = 0; p_idx < num_permutations; ++p_idx) {
            
            // populate occupancy tables with all possible attacks
            occupancy_tables[p_idx] = generateAttackPermutation(p_idx, relevant_bits, attack_bb);

            // populate proper attack tables with blocked attacks using occupancy tables
            // i do this to generate a properly formed ray, for example this sequence of bits for a rook is invalid: 00011001
            attack_tables[p_idx] = (p_type == BISHOP) ? attacks::generateBishopAttacksWithBlockers(source, occupancy_tables[p_idx]) : attacks::generateRookAttacksWithBlockers(source, occupancy_tables[p_idx]);
        
        }

        // loop a bunch of times to find a valid magic hash
        // (this should very rarely fail)
        for(int i = 0; i < 1000000000; ++i) {
            
            // randomly populated bitboard
            Bitboard magic_num{ generateMagicNumber() };
            
            // skip if too few bits
            if(utils::popcount((attack_bb * magic_num & 0xFF00000000000000) < 6)) continue;

            bool fail{ false };

            // loop over every permutation
            for(int index = 0; index < num_permutations; ++index) {
                
                // plug in candidate magic_num into known formula
                int magic_index{ static_cast<int>((occupancy_tables[index] * magic_num) >> (64 - relevant_bits)) };
                
                // check that the magic hash correctly transforms every position
                // store seen positions in used_attack_tables
                // if the tables do not match, the magic number is invalid
                if(used_attack_tables[magic_index] == ZERO) {

                    used_attack_tables[magic_index] = attack_tables[magic_index];

                } else if(used_attack_tables[magic_index] != attack_tables[magic_index]) {

                    fail = true;
                    break;

                }

            }

            if(fail == false) {
                return magic_num;
            }

        }
        // no magic num found
        std::cout << "ERROR!";

        return 0ULL;
    }

}