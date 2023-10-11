#pragma once
#include <iostream>
#include <string>

namespace View {
    void printBoard() {
    /**
     *      +-------------------------------------------------------+
     *    1 |  BR  |  BB  |  BN  |  BK  |  BQ  |  BB  |  BN  |  BR  |  
     *      |------|------|------|------|------|------|------|------|  
     *    2 |  BP  |  BP  |  BP  |  BP  |  BP  |  BP  |  BP  |  BP  | 
     *      |------|------|------|------|------|------|------|------|
     *    3 |      |      |      |      |      |      |      |      |   
     *      |------|------|------|------|------|------|------|------|  
     *    4 |      |      |      |      |      |      |      |      |    
     *      |------|------|------|------|------|------|------|------|  
     *    5 |      |      |      |      |      |      |      |      | 
     *      |------|------|------|------|------|------|------|------| 
     *    6 |      |      |      |      |      |      |      |      | 
     *      |------|------|------|------|------|------|------|------| 
     *    7 |  WP  |  WP  |  WP  |  WP  |  WP  |  WP  |  WP  |  WP  |  
     *      |------|------|------|------|------|------|------|------|   
     *    8 |  WR  |  WN  |  WB  |  WQ  |  WK  |  WB  |  WN  |  WR  |  
     *      +-------------------------------------------------------+
     *         a      b      c      d      e      f      g      h     
    */
    std::string pieces[64];
    for(auto& piece: pieces) {
        piece = "WB";
    }
    std::cout << "\n\t  +-------------------------------------------------------+\n";
    for(int rank = 1; rank <= 8; rank++) {
        std::cout << "\t" << rank << " |";
        for(int piece = 0; piece < 8; piece++) {
            std::cout << "  " << pieces[0] << "  |";
        }
        if(rank < 8) {
            std::cout << "\n\t  |------|------|------|------|------|------|------|------|\n";
        } else {
            std::cout << "\n\t  +-------------------------------------------------------+\n";
        }
    }
    std::cout << "\t     a      b      c      d      e      f      g      h    \n\n";

    }
}