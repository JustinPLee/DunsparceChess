#include <iostream>
#include <vector>

#include "src/move.hpp"
#include "src/board.hpp"
#include "src/types.hpp"
#include "src/constants.hpp"
#include "src/utils.hpp"
#include "src/engine/movegen/attacks.hpp"

int main() {
    using namespace dunsparce;
    attacks::initLeapersAttacks();

    for(int rank = 0; rank < 8; ++rank) {
        for(int file = 0; file < 8; ++file) {
            int square = rank * 8 + file;
            std::cout << utils::popcount(attacks::generateRookAttacksNoBlockers(Square(square))) << ", ";
        }
        std::cout << '\n';
    }

    return 0;
}