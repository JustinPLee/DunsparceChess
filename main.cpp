#include <iostream>
#include <vector>

#include "src/move.hpp"
#include "src/board.hpp"
#include "src/types.hpp"
#include "src/constants.hpp"
#include "src/utils.hpp"
#include "src/engine/movegen/attacks.hpp"
#include "src/engine/movegen/magic.hpp"
#include "src/engine/movegen/movegen.hpp"

using namespace dunsparce;
void initAll() {
    attacks::initAllAttacks();
}

int main() {

    initAll();

    Board board{ constants::fens::test };
    movegen::generateAllMoves(White, board);
    board.printMoves();
    board.print();



    return 0;
}
