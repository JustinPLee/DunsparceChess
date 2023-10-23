#pragma once

#include "../../constants.hpp"
#include "../../board.hpp"
#include "../../types.hpp"
#include "../../utils.hpp"
#include "tables.hpp"
#include "attacks.hpp"

/** Make, UnMake **/
namespace dunsparce::movegen {

    enum MoveClassification {
        QUIET,
        CAPTURE
    };

    void generatePseudoLegalPawnMoves(Color side, const Board& board);
    void generatePseudoLegalKnightMoves(Color side, const Board& board);
    void generatePseudoLegalBishopMoves(Color side, const Board& board);
    void generatePseudoLegalRookMoves(Color side, const Board& board);
    void generatePseudoLegalKingMoves(Color side, const Board& board);
    void generatePseudoLegalQueenMoves(Color side, const Board& board);


} // namespace dunspare::movegen