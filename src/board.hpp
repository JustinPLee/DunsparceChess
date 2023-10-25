#pragma once

#include <vector>
#include <string_view>

#include "types.hpp"
#include "constants.hpp"
#include "move.hpp"

namespace dunsparce {
/**
 * The Board class manages piece and color bitboards and holds essential board data.
*/
class Board {
    public:
        explicit Board(const std::string& fen = constants::fens::starting);
        // defaults for essential board information
        // copied and modiified in move gen and eval

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
        int get_material();

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

        // returns index of added move
        int addMove(const move::Move& move);
        int addMove(Square from_square, Square to_square, Piece piece, Piece promoted_piece, bool capture_flag, bool double_push_flag, bool croissant_flag, bool castling_flag);
        void printMoves() const;
        void printMove(int index) const;

        Bitboard get_piece_bb(Color color, BasePiece base_piece) const;
        Bitboard get_piece_bb(Piece piece) const;
        Bitboard get_occupancy_bb(Color color) const;
        Square get_croissant_square() const;
        uint8_t get_castling() const;
        std::vector<move::Move> get_moves() const;


        uint64_t generateZobristKey();

    private:
        std::vector<Bitboard> pieces_;
        std::vector<Bitboard> occupancies_;
        std::vector<move::Move> move_list_;
        Color side_;
        Square croissant_;
        uint8_t castling_;
        Color pov_;

        struct BoardState {
            std::vector<Bitboard> pieces_;
            std::vector<Bitboard> occupancies_;
            Color side_;
            Square croissant_;
            uint8_t castling_;
        };

        BoardState copyBoardState() const;
        void consumeBoardState(BoardState& board_state);
};

} // namespace::dunsparce