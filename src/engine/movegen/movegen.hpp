#pragma once

#include "../../board.hpp"
#include "../../types.hpp"

/** Make, UnMake **/
namespace dunsparce::movegen {

    enum MoveClassification {
        QUIET,
        CAPTURE
    };

    void generatePseudoLegalPawnMoves(Color side, Board& board);
    void generatePseudoLegalKnightMoves(Color side, Board& board);
    void generatePseudoLegalBishopMoves(Color side, Board& board);
    void generatePseudoLegalRookMoves(Color side, Board& board);
    void generatePseudoLegalKingMoves(Color side, Board& board);
    void generatePseudoLegalQueenMoves(Color side, Board& board);
    void generateAllMoves(Color side, Board& board);


} // namespace dunspare::movegen