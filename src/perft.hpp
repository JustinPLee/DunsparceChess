#pragma once

#include <cstdint> // uint64_t

#include "engine/movegen/movegen.hpp"
#include "board.hpp"


namespace dunsparce::perft {

class Perft {
    public:
        Perft(const Board& board);
        void profile(int depth);
        void full_profile(int depth);

    private:
        void run(int depth);
        Board board_;
        uint64_t nodes_ = 0;

};

} // namespace dunsparce::perft