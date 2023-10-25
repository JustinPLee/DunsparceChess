#pragma once

#include "../../board.hpp"
#include "../../types.hpp"

/** Make, UnMake **/
namespace dunsparce::movegen {
    void populatePseudoLegalPawnMoves(Color side, Board& board);
    void populatePseudoLegalKnightMoves(Color side, Board& board);
    void populatePseudoLegalBishopMoves(Color side, Board& board);
    void populatePseudoLegalRookMoves(Color side, Board& board);
    void populatePseudoLegalKingMoves(Color side, Board& board);
    void populatePseudoLegalQueenMoves(Color side, Board& board);
    void populateAllPseudoLegalMoves(Color side, Board& board);
} // namespace dunspare::movegen