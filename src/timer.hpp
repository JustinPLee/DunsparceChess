#pragma once

#include <chrono>

namespace dunsparce {

class Timer {
    public:
        Timer(bool start_now = false);

        void start();
        uint64_t get_elasped() const;
        void print() const;

    private:
        std::chrono::high_resolution_clock::time_point start_;
};

} // namespace dunsparce