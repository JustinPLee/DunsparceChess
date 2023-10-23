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
    attacks::initLeapersAttacks();
    magic::init();
    attacks::initSlidersAttacks(Rook);
    attacks::initSlidersAttacks(Bishop);
}

int main() {

    initAll();

    Board board{};
    board.parseFen("8/8/8/3p4/8/8/8/8 w - -");
    for(int i = 0; i < 1000; ++i) {
    board.addMove(D7, E8, BBishop, WQueen, false, false, false, true);
    board.addMove(A2, D7, BBishop, WPawn, true, false, false, true);
    board.addMove(B7, E8, WPawn, WQueen, false, false, true, false);
    board.addMove(F5, B7, BBishop, BBishop, false, false, false, true);
    board.addMove(D7, B7, WPawn, BBishop, false, true, false, true);
    }
    board.printMoves();



    return 0;
}
