#include "assert.h"

#include "src/types.hpp"
#include "src/board.hpp"
#include "src/bitboard.hpp"
#include "src/constants.hpp"
#include "src/print.hpp"


// Test reading FEN strings

void test_read_fen() {
    Board board;
    board.init("8/8/8/8/8/8/8/8 w KQkq - 0 0");

}