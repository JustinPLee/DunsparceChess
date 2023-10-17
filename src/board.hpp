#pragma once

#include <array>
#include <string_view>

#include "types.hpp"
#include "constants.hpp"
#include "bitboard.hpp"
/**
 * The Board class manages piece and color bitboards and holds essential board data.
*/
class Board {
    public:
        explicit Board(std::string_view fen = STARTING_FEN);
        // defaults for essential board information
        // copied and modiified in move gen and eval
        struct BoardState {
            uint8_t castling_rights = CASTLE_BLACK_KING | CASTLE_BLACK_QUEEN | CASTLE_WHITE_KING | CASTLE_WHITE_QUEEN;
            Square croissant = NULL_SQUARE;
            int half_moves = 0;
            // contains information about piece locations
            uint64_t zobrist_key = 0ULL; // !!! ooowow
        };

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
         * @param `std::string_view` Valid FEN string
        */
        void process_fen(std::string_view fen);

        /** TODO:
         * Analyzes the current `Board` state and variables.
         * @return `std::string` Valid FEN string
        */
        std::string export_fen();
        
        /** TODO:
         * Returns the total piece material of one side
         * @return `int` Total piece value
         * @notetemplate <typename Color> ?
        */
        int get_piece_material();

        /**
         * Reverses the POV from white to black or black to white.
        */
        void reverse_pov();

        /**
         * Prints a pretty representation of all the current pieces' positions to the command-line.
         * @note Orientation depends on `pov_`
        */
        void print();

        /**
         * Sets all `Board` variables to their default state.
        */
        void clear();

        /**
         * Returns a `Piece` object at a specific `Square` index.
         * @param `Square` Any square
         * @return `Piece` Any piece
        */
        Piece piece_at(Square square);

    private:
        /* bitboards */
        void init_bitboards();
        // bitboard for every piece
        std::array<std::array<Bitboard, N_COLORS>, N_PIECES> pieces_;
        // occupancy bitboard for each color
        std::array<Bitboard, N_COLORS> colors_;

        /* Board data */
        // pieces are indexed 0 through 63 for fast access
        std::array<Piece, 64> squares_;
        BoardState state_ = BoardState{};
        Color next_move_ = WHITE;
        // counts total number of moves ex: white move + black move = 1
        int full_moves_ = 0;
        // board orientation used for correct printing
        bool pov_ = WHITE;
};
