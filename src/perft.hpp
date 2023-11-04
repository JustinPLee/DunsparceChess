#pragma once

#include <iostream>
#include <iomanip> // std::fixed
#include <chrono>

#include "engine/movegen.hpp"
#include "board.hpp"
#include "move.hpp"


namespace dunsparce::perft {

class Perft {
    public:
        Perft(const Board& board);

        void profile(int depth);
        void full_profile(int depth);

        class Timer {
            public:
                Timer(bool start_now = false);

                void start();
                uint64_t get_elasped() const;
                void print() const;

            private:
                std::chrono::high_resolution_clock::time_point start_;
        };

    private:
        void run(int depth);
        Board board_;
        uint64_t nodes_ = 0;

};

} // namespace dunsparce::perft