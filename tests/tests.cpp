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

using namespace my_testing_thing;

namespace dunsparce::tests {

/*****************
 * 
 * 
 *   Start Here
 * 
 * 
 ****************/


void testBitboardOperations() {
    std::cout << "Bitboard Operations\n";
    std::cout << "===================\n";
}

/**
 * TODO: fix exportFen
*/
void testReadFen() {
    std::cout << "Reading/Exporting FEN\n";
    std::cout << "=====================\n";
}

void testMoveRepr() {
    std::cout << "Move Representation\n";
    std::cout << "===================\n";
}

void testSanity() {
    std::cout << "Sanity Check\n";
    std::cout << "============\n";
    test("^", [](){});
}

}

int main() {
    using namespace dunsparce::tests;

    std::vector<std::function<void()>> allTests {
        testBitboardOperations,
        testReadFen,
        testMoveRepr,
        testSanity
    };

    executeAll(allTests);


    return 0;
}