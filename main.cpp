#include <iostream>

#include "src/board.hpp"
#include "src/constants.hpp"
#include "src/utils.hpp"

int main() {
    using namespace dunsparce;
    Board board;
    std::cout << utils::getFile(Square(H1));
    return 0;
}