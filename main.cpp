#include <iostream>
#include <vector>

#include "src/move.hpp"
#include "src/board.hpp"
#include "src/types.hpp"
#include "src/constants.hpp"
#include "src/utils.hpp"
#include "src/engine/movegen/attacks.hpp"
#include "src/engine/movegen/magic.hpp"

using namespace dunsparce;
void initAll() {
    attacks::initLeapersAttacks();
    magic::init();
    attacks::initSlidersAttacks(ROOK);
    attacks::initSlidersAttacks(BISHOP);
}

int main() {
    initAll();

    Bitboard ex{ ZERO };
    utils::setSquare(ex, C5);
    utils::setSquare(ex, F2);
    utils::setSquare(ex, G7);
    utils::setSquare(ex, B2);
    utils::setSquare(ex, G5);
    utils::setSquare(ex, E2);
    utils::setSquare(ex, E7);

    utils::printBB(attacks::generateBishopMagicAttacks(D4, ex));



    return 0;
}
