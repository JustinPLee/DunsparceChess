#include "timer.hpp"

#include <chrono>
#include <iostream>

namespace dunsparce {

Timer::Timer(bool start_now) {
    if(start_now) {
        start();
    }
}

void Timer::start() {
    start_ = std::chrono::high_resolution_clock::now();
}

uint64_t Timer::get_elasped() const {
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start_).count();
}

void Timer::print() const {
    std::cout << "Time: " << get_elasped() << "ms\n";
}

} // namespace dunsparce