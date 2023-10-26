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

#include "src/perft.hpp"

using namespace dunsparce;

int main() {
    attacks::initAllAttacks();

    Board board{ "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq –"};

    perft::Perft pineapple{ board };
    pineapple.profile(2);

    return 0;
}
