#include <iostream>
#include <vector>

#include "src/move.hpp"
#include "src/board.hpp"
#include "src/types.hpp"
#include "src/constants.hpp"
#include "src/utils.hpp"
#include "src/engine/movegen/attacks.hpp"
#include "src/engine/movegen/magic.hpp"

int main() {
    initAll();
    return 0;
}

void initAll() {
    using namespace dunsparce;
    attacks::initLeapersAttacks();
}