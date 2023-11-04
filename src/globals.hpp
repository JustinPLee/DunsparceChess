#pragma once

#include <array>
#include <string_view>

#include "types.hpp"

namespace dunsparce::globals {
    constexpr int pawn_value {100};
    constexpr int knight_value {320};
    constexpr int bishop_value {330};
    constexpr int rook_value {500};
    constexpr int queen_value {900};
    constexpr int king_value {10000};
    constexpr int checkmate_value {king_value};

    constexpr int max_ply {64};

    namespace sample_fens {
        constexpr std::string_view starting {"rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 0"};
        constexpr std::string_view empty {"8/8/8/8/8/8/8/8 w - - "};
        constexpr std::string_view test {"r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq -"};
    }
};
