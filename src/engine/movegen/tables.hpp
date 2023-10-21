#pragma once

#include <array>

#include "bitboard.hpp"
#include "types.hpp"

namespace dunsparce::tables {

namespace dunsparce::tables::attacks {
    std::array<StaticBB, 64> WHITE_PAWN{};
    std::array<StaticBB, 64> BLACK_PAWN{};
    std::array<StaticBB, 64> KNIGHT{};
    std::array<StaticBB, 64> KING{};
    std::array<std::array<StaticBB, 64>, 64> RANK{};
    std::array<std::array<StaticBB, 64>, 64> FILE{};
    std::array<std::array<StaticBB, 64>, 64> DIAGA8H1{};
    std::array<std::array<StaticBB, 64>, 64> DIAGA1H8{};

} // ::attacks

namespace dunsparce::tables::moves {

    std::array<StaticBB, 64> BLACK_PAWN_SINGLE{};
    std::array<StaticBB, 64> BLACK_PAWN_DOUBLE{};
    std::array<StaticBB, 64> WHITE_PAWN_SINGLE{};
    std::array<StaticBB, 64> WHITE_PAWN_DOUBLE{};

} // ::moves

namespace dunsparce::tables::magics {
    constexpr std::array<StaticBB, 8> FILE = {
        0x8040201008040200,
        0x4020100804020100,
        0x2010080402010080,
        0x1008040201008040,
        0x0804020100804020,
        0x0402010080402010,
        0x0201008040201008,
        0x0100804020100804
    };

    constexpr std::array<StaticBB, 15> DIAGA8H1 = {
        0x0,
        0x0,
        0x0101010101010100,
        0x0101010101010100,
        0x0101010101010100,
        0x0101010101010100,
        0x0101010101010100,
        0x0101010101010100,
        0x0080808080808080,
        0x0040404040404040,
        0x0020202020202020,
        0x0010101010101010,
        0x0008080808080808,
        0x0,
        0x0
    };

    constexpr std::array<StaticBB, 15> DIAGA1H8 = {
        0x0,
        0x0,
        0x0101010101010100,
        0x0101010101010100,
        0x0101010101010100,
        0x0101010101010100,
        0x0101010101010100,
        0x0101010101010100,
        0x8080808080808000,
        0x4040404040400000,
        0x2020202020000000,
        0x1010101000000000,
        0x0808080000000000,
        0x0,
        0x0
    };

} // ::magics

namespace dunsparce::tables::masks {

    std::array<StaticBB, 64> RANK{};
    std::array<StaticBB, 64> FILE{};
    std::array<StaticBB, 64> FILE_MAGIC{};
    std::array<StaticBB, 64> DIAGA8H1{};
    std::array<StaticBB, 64> DIAGA8H1_MAGIC{};
    std::array<StaticBB, 64> DIAGA1H8{};
    std::array<StaticBB, 64> DIAGA1H8_MAGIC{};
    
    // used for castling
    std::array<StaticBB, 2> maskEG{};
    std::array<StaticBB, 2> maskFG{};
    std::array<StaticBB, 2> maskBD{};
    std::array<StaticBB, 2> maskCE{};

} // ::masks

std::array<std::array<uint8_t, 64>, 8> SLIDING_ATTACKS{}; // !!

} // dunsparce::tables::