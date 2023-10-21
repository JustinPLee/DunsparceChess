#pragma once

// Utilizes make/unmake

#include "../../types.hpp"
#include "../../board.hpp"

namespace dunsparce {
    template <Color attacker>
    bool isAttackedBy(Bitboard targeted, const Board& board);
}