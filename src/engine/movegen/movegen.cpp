#include <vector>

#include "movegen.hpp"
#include "move.hpp"
#include "board.hpp"
#include "constants.hpp"
#include "types.hpp"

/***************************************************************
 * *************************************************************
 * *************************************************************
 * *************************************************************
 * **************** TODO: FACTOR!!!! URGENT!! ******************
 * *************************************************************
 * *************************************************************
 * *************************************************************
 * *************************************************************
 * *************************************************************
*/

namespace dunsparce {

    template <Color us>
    void generatePseudoLegalMoves(const Board& board) {
        //REFACTORRRRRrrRRrR
        std::vector<MoveType> move_list;
        move_list.reserve(MAX_MOVES);

        generatePseudoLegalPawnMoves<us>(move_list, board);
    }
    template <Color us>
    void generatePseudoLegalPawnMoves(std::vector<MoveType>& move_list, const Board& board) {
        constexpr Bitboard us_board{ board.pieces_[us][PAWN] };
        constexpr StaticBB candidate_squares{ ~board.occupancies_[us] };
        MoveType move;
        move.setPiece(Piece{ PAWN, us });
        move.setFrom(us_board.bitScanForward());

        Bitboard candidate_moves { tables::moves::B}

    }

}