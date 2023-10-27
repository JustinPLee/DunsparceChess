#pragma once

#include <string>
#include <array>
#include <sstream>

class Board {
    public:
        constexpr Board(std::string_view fen) {
            parseFen(fen);
        };

};

namespace {

    struct FenData {
        std::array<int, 64> squares;
        int side_to_move;
        int castle;
        int croissant;
        int half_moves;
        int full_moves;
    };

    constexpr FenData parseFen(std::string_view fen) {
        int sum{ 0 };
        for(int i = 0; i < 1; ++i) {
            sum += i;
        }
        return {};
    }

}