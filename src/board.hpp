#pragma once

#include <array>
#include <string_view>

#include "types.hpp"
#include "constants.hpp"

namespace dunsparce {
/**
 * The Board class manages piece and color bitboards and holds essential board data.
*/
class Board {
    public:
        explicit Board(std::string_view fen = constants::fens::starting);
        // defaults for essential board information
        // copied and modiified in move gen and eval

        /**
         * Clears board and calls processFen.
         * @param `std::string_view` Valid FEN string
         * @note Called on `Board`'s construction
        */
        void init(std::string_view fen);

        /**
         * Parses a given FEN string.
         * Extracts and assigns pieces, the next move, castling rights,
         * the croissant square, half moves, and full moves to the `Board` object.  
         * @param `std::string` Valid FEN string
        */
        void parseFen(const std::string& fen);

        /** TODO:
         * Analyzes the current `Board` state and variables.
         * @return `std::string` Valid FEN string
        */
        std::string exportFen();
        
        /** TODO:
         * Returns the total piece material of one side
         * @return `int` Total piece value
         * @notetemplate <typename Color> ?
        */
        int getPieceMaterial();

        /**
         * Reverses the POV from white to black or black to white.
        */
        void reversePov();

        /**
         * Prints a pretty representation of all the current pieces' positions to the command-line.
         * @note Orientation depends on `pov_`
        */
        void print();

        /**
         * Sets all `Board` variables to their default state.
        */
        void clear();

        uint64_t generateZobristKey();

        std::array<Bitboard, 12> pieces_;
        std::array<Bitboard, 3> occupancies_;

        Color side_;
        Square croissant_;
        uint8_t castling_;
        Color pov_;
};

} // namespace::dunsparce