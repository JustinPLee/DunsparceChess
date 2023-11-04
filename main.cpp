#include <iostream>
#include <vector>

#include "src/board.hpp"
#include "src/perft.hpp"
#include "src/globals.hpp"

using namespace dunsparce;

int main() {
    //Board board {"r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq -"};
    Board board {globals::sample_fens::starting};
    return 0;
}

/*

valgrind --leak-check=full \
         --show-leak-kinds=all \
         --track-origins=yes \
         --verbose \
         --log-file=valgrind-out.txt \
         ./executable exampleParam1


*/
