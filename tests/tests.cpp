#include "tt.hpp"

#include "../src/types.hpp"
#include "../src/board.hpp"
#include "../src/move.hpp"
#include "../src/globals.hpp"
#include "../src/uci.hpp"
#include "../src/engine/movegen/movegen.hpp"

/*****************
 * 
 * 
 *   Start Here
 * 
 * 
 ****************/

using namespace tt;


void testPseudoLegalMoveGeneration() {
    std::cout << "Pseudolegal Move Generation\n";
    std::cout << "===========================\n";

    test("Starting Fen", [&]() {
        Board board;
        board.parseFen(globals::sample_fens::starting);
        generatePseudoLegalPawnMoves(board.state);
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
    initAll();

    std::vector<std::function<void()>> allTests {
        testPseudoLegalMoveGeneration,
        testSanity
    };

    executeAll(allTests);


    return 0;
}