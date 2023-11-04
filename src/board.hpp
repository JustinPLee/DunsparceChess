#pragma once

#include <string>
#include <sstream>
#include <vector>
#include <array>

#include "types.hpp"
#include "bits.hpp"
#include "move.hpp"
#include "tables.hpp"

namespace dunsparce {
    class Board {
        public:
            Board();
            Board(std::string_view fen);

            struct BoardState {
                std::array<Bitboard, NPieces> pieces{};
                std::array<Bitboard, Both+1> occupancies{};
                Color side = White;
                Square croissant = NullSquare;
                uint8_t castling = (tables::castling::wq | tables::castling::wk | tables::castling ::bq || tables::castling::bk);
            };

            void clear();
            void pprint() const;
            void reversePov();
            void addMove(const Move& move);
            void addMove(Move&& move);
            void printMoves() const;
            BoardState parseFen(std::string_view fen);
            BoardState exportFen() const;

            BoardState state{};
        private:
            std::string fen_{};
            Color pov_ = White;
            std::vector<Move> move_list_{};
    };
}