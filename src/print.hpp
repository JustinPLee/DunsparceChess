#pragma once

#include <iostream>
#include <string_view>
#include <array>

#include "board.hpp"
#include "types.hpp"

namespace DEBUG {
    std::string_view pieceToUnicode(Piece piece) {
        using enum Piece;
        switch(piece) {
            case BlackPawn:   return "♟︎"; break;
            case BlackKnight: return "♞"; break;
            case BlackBishop: return "♝"; break;
            case BlackRook:   return "♜"; break;
            case BlackQueen:  return "♛"; break;
            case BlackKing:   return "♚"; break;

            case WhitePawn:   return "♙"; break;
            case WhiteKnight: return "♘"; break;
            case WhiteBishop: return "♗"; break;
            case WhiteRook:   return "♔"; break;
            case WhiteQueen:  return "♕"; break;
            case WhiteKing:   return "♔"; break;

            case None:        return " "; break;
            default: throw "should never throw";
        }
    }
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

        std::cout << "\n\t  +-------------------------------+\n";
        for(int rank = 8; rank >= 1; rank--) {
            std::cout << "\t" << rank << " |";
            for(int file = 1; file <= 8; file++) {
                std::cout << " " << pieceToUnicode(pieces[(file-1)+(9-rank-1)*8]) << " |";
            }
            if(rank < 8) {
                std::cout << "\n\t  |---+---+---+---+---+---+---+---|\n";
            } else {
                std::cout << "\n\t  +-------------------------------+\n";
            }
        }
        std::cout << "\t    a   b   c   d   e   f   g   h \n\n";
    }
}