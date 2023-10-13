#pragma once

#include <iostream>
#include <string_view>
#include <array>

#include "board.hpp"
#include "types.hpp"

// TODO: support reversed board, reversed board display
void printUnicodeBoard(std::array<Piece, 64> pieces) {
    //    +-------------------------------+
    //  1 | ♜ | ♞ | ♝ | ♚ | ♛ | ♝ | ♞ | ♜ |
    //    |---+---+---+---+---+---+---+---|   
    //  2 | ♟︎ | ♟︎ | ♟︎ | ♟︎ | ♟︎ | ♟︎ | ♟︎ | ♟︎ |
    //    |---+---+---+---+---+---+---+---| 
    //  3 |   |   |   |   |   |   |   |   |
    //    |---+---+---+---+---+---+---+---|     
    //  4 |   |   |   |   |   |   |   |   |
    //    |---+---+---+---+---+---+---+---|        
    //  5 |   |   |   |   |   |   |   |   |
    //    |---+---+---+---+---+---+---+---|    
    //  6 |   |   |   |   |   |   |   |   |
    //    |---+---+---+---+---+---+---+---|   
    //  7 | ♙ | ♙ | ♙ | ♙ | ♙ | ♙ | ♙ | ♙ |
    //    |---+---+---+---+---+---+---+---|  
    //  8 | ♖ | ♘ | ♗ | ♕ | ♔ | ♗ | ♘ | ♖ |  
    //    +-------------------------------+
    //      a   b   c   d   e   f   g   h     
    for(Piece piece : pieces) {
        std::cout << static_cast<int>(piece);
    }
}