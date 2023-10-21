#include <iostream>

#include "bitboard.hpp"

namespace dunsparce {

int Bitboard::popcount() const {
    uint64_t cpy = board_;
    int count = 0;
    while(cpy) {
        ++count;
        cpy >>= 1;
    }
    return count;
}

void Bitboard::print() const {
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++) {
            const int n = 63-8*i-j;
            std::cout << ((board_ >> n) & 1 ? 'x' : '.');
        }
        std::cout << '\n';
    }
}

}