/*** Go fast ***/
#pragma once

#include <chrono>
#include <iostream>

class Ponyta {
    public:
        constexpr Ponyta();

        void run() const;
    private:
        int a;
};