#pragma once

#include <array>
#include <string_view>

#include "types.hpp"
#include "constants.hpp"
#include "bitboard.hpp"

class Board {
    public:
        Board(std::string_view fen = STARTING_FEN);
        struct BoardState {
            int castlingRights;
            Square croissant;
            int halfMoves;
            uint64_t zobrist_key; // !!! ooowow
        };

        void init(std::string_view fen);
        void processFen(std::string_view fen);
        std::string exportFen();
        int evalPieceMaterial();
        void reversePov();
        void print();
        void clear();

    private:
        void initBitboards();
        // bitboards
        std::array<std::array<Bitboard, N_COLORS>, N_PIECES> pieces_;
        std::array<Bitboard, N_COLORS> colors_;
        // pieces indexed 0 through 63 for fast access
        std::array<Piece, 64> squares_;
        // current state variables
        BoardState state_;
        Color nextMove_ = WHITE;
        int fullMoves_ = 0;

        bool pov_ = WHITE;
};
