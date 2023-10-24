/**
 * This file could become very long very quickly.
*/
#include <iostream>
#include <vector>
#include <functional>
#include <string>

#include "my_testing_thing.hpp"

#include "../src/types.hpp"
#include "../src/board.hpp"
#include "../src/constants.hpp"
#include "../src/move.hpp"
#include "../src/utils.hpp"
#include "../src/uci.hpp"
#include "../src/engine/movegen/movegen.hpp"
#include "../src/engine/movegen/magic.hpp"
#include "../src/engine/movegen/attacks.hpp"

using namespace my_testing_thing;

namespace dunsparce::tests {

/*****************
 * 
 * 
 *   Start Here
 * 
 * 
 ****************/


void testPseudoLegalMoveGeneration() {
    std::cout << "Pseudolegal Move Generation\n";
    std::cout << "===========================\n";

    test("Starting Fen", [&]() {
        Board board{};
        board.parseFen(constants::fens::starting);
        movegen::generatePseudoLegalPawnMoves(White, board);
        movegen::generatePseudoLegalPawnMoves(Black, board);
        pray(board.getMoves().size() == 32);
    });

}


void testSanity() {
    std::cout << "Sanity Check\n";
    std::cout << "============\n";
    test("^", [](){});
}

}

void initAll() {
    using namespace dunsparce;
    attacks::initLeapersAttacks();
    attacks::initSlidersAttacks(Rook);
    attacks::initSlidersAttacks(Bishop);
}

int main() {
    using namespace dunsparce;

    initAll();

    std::vector<std::function<void()>> allTests {
        tests::testPseudoLegalMoveGeneration,
        tests::testSanity
    };

    executeAll(allTests);


    return 0;
}