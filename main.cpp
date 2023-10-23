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
    attacks::initSlidersAttacks(Rook);
    attacks::initSlidersAttacks(Bishop);
}

int main() {
    initAll();

    Board board{};
    board.parseFen("8/8/8/3p4/8/8/8/8 w - -");
    board.print();
    utils::printBB(attacks::generatePawnAttacks(D5, White));



    return 0;
}
