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


int main() {
    using namespace dunsparce;
    attacks::initAllAttacks();

    Board board{ constants::fens::starting };
    movegen::populateAllPseudoLegalMoves(Both, board);
    board.printMoves();
    board.print();







    return 0;
}
