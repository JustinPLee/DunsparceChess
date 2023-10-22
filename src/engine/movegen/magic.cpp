#include "magic.hpp"

namespace dunsparce::magic {

     // index determines which bits are set, it corresponds with popcount(attack_bb) 
    inline Bitboard generateOccupanies(int index, Bitboard attack_bb) {
        Bitboard occupancy{ uint64_t{0} };

        for(int nth_bit = 0; nth_bit < utils::popcount(attack_bb); ++nth_bit) {
            int square{ utils::getLSBIndex(attack_bb) };
            utils::popBit(attack_bb, square);

            if(index & (1 << nth_bit)) {
                occupancy |= (uint64_t{1} << square);
            }
        }
        
        return occupancy;
    }   

}