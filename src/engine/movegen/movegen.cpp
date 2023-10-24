#include "movegen.hpp"

#include "../../constants.hpp"
#include "../../board.hpp"
#include "../../types.hpp"
#include "../../utils.hpp"
#include "../../board.hpp"
#include "tables.hpp"
#include "attacks.hpp"

namespace dunsparce::movegen {

// store pawn pushes in lookup table (?)
void generatePseudoLegalPawnMoves(Color side, Board& board) {
    const int promotion_rank = (side == White ? 1 : 6);
    const int double_push_rank = (side == White ? 6 : 1);
    const int rel_move_offset = (side == White ? -8 : 8);
    const Piece pawn{ utils::createPiece(side, BasePawn) };
    Bitboard pawn_bb{ board.get_piece_bb(pawn) };
    // exhaust every pawn in the bitboard
    while(pawn_bb) {
        const Square from_square{ utils::getFirstSquare(pawn_bb) };
        // special logic for pawns since their move square differs from their capture square
        const Square to_move_square{ Square(from_square + rel_move_offset) };
        // in-bounds
        if((to_move_square >= A8 && to_move_square <= H1) && utils::isSquareEmpty(board.get_occupancy_bb(Both), to_move_square)) {
            // promotion
            if(rank_of(from_square) == promotion_rank) {
                board.addMove(from_square, to_move_square, pawn, utils::createPiece(side, BaseQueen), false, false, false, false);
                board.addMove(from_square, to_move_square, pawn, utils::createPiece(side, BaseRook), false, false, false, false);
                board.addMove(from_square, to_move_square, pawn, utils::createPiece(side, BaseBishop), false, false, false, false);
                board.addMove(from_square, to_move_square, pawn, utils::createPiece(side, BaseKnight), false, false, false, false);
            } else {
                // single push
                board.addMove(from_square, to_move_square, pawn, NullPiece, false, false, false, false);
                // double push
                if(rank_of(from_square) == double_push_rank && utils::isSquareEmpty(board.get_occupancy_bb(Both), Square(to_move_square + rel_move_offset))) {
                    board.addMove(from_square, Square(to_move_square + rel_move_offset), pawn, NullPiece, false, true, false, false);
                }
            }
        }
        Bitboard attack_bb{ attacks::pawns[side][from_square] & board.get_occupancy_bb(utils::oppSide(side)) };
        std::cout << utils::squareToCoordinates(from_square) << " ";
        utils::printBB(attacks::pawns[side][from_square]);
        // exhaust every attack
        while(attack_bb) {
            const Square to_attack_square{ utils::getFirstSquare(attack_bb) };
            // promotion capture
            if(rank_of(to_attack_square) == promotion_rank) {
                board.addMove(from_square, to_attack_square, pawn, utils::createPiece(side, BaseQueen), true, false, false, false);
                board.addMove(from_square, to_attack_square, pawn, utils::createPiece(side, BaseRook), true, false, false, false);
                board.addMove(from_square, to_attack_square, pawn, utils::createPiece(side, BaseBishop), true, false, false, false);
                board.addMove(from_square, to_attack_square, pawn, utils::createPiece(side, BaseKnight), true, false, false, false);
            } else {
                board.addMove(from_square, to_attack_square, pawn, NullPiece, true, false, false, false);
            } 
            utils::popSquare(attack_bb, to_attack_square);
        }
        // croissssssant
        if(board.get_croissant_square() != NullSquare) {
            const Bitboard croissant_attacks { attacks::pawns[side][from_square] & (One << board.get_croissant_square()) };
            if(croissant_attacks) {
                const Square croissant_square{ utils::getFirstSquare(croissant_attacks) };
                board.addMove(from_square, croissant_square, pawn, NullPiece, true, false, true, false);
            }
        }
        utils::popSquare(pawn_bb, from_square);
    }
}

void generatePseudoLegalKnightMoves(Color side, Board& board) {
    const Bitboard targetable_squares_bb{ ~board.get_occupancy_bb(side) };
    const Piece knight{ utils::createPiece(side, BaseKnight) };
    Bitboard knight_bb{ board.get_piece_bb(knight) };
    while(knight_bb) {
        const Square from_square{ utils::getFirstSquare(knight_bb) };
        Bitboard attack_bb{ attacks::knights[from_square] & targetable_squares_bb };
        while(attack_bb) {
            const Square to_square{ utils::getFirstSquare(attack_bb) };
            if(utils::isSquareEmpty(board.get_occupancy_bb(utils::oppSide(side)), to_square)) {
                // quiet
                board.addMove(from_square, to_square, knight, NullPiece, false, false, false, false);
            } else {
                // capture
                board.addMove(from_square, to_square, knight, NullPiece, true, false, false, false);
            }
            utils::popSquare(attack_bb, to_square);
        }
        utils::popSquare(knight_bb, from_square);
    }
}

void generatePseudoLegalBishopMoves(Color side, Board& board) {
    const Bitboard targetable_squares_bb{ ~board.get_occupancy_bb(side) };
    const Piece bishop{ utils::createPiece(side, BaseBishop) };
    Bitboard bishop_bb{ board.get_piece_bb(bishop) };
    while(bishop_bb) {
        const Square from_square{ utils::getFirstSquare(bishop_bb) };
        Bitboard attack_bb{ attacks::getBishopAttacks(from_square, board.get_occupancy_bb(Both)) & targetable_squares_bb };
        while(attack_bb) {
            const Square to_square{ utils::getFirstSquare(attack_bb) };
            if(utils::isSquareEmpty(board.get_occupancy_bb(utils::oppSide(side)), to_square)) {
                // quiet
                board.addMove(from_square, to_square, bishop, NullPiece, false, false, false, false);
            } else {
                // capture
                board.addMove(from_square, to_square, bishop, NullPiece, true, false, false, false);
            }
            utils::popSquare(attack_bb, to_square);
        }
        utils::popSquare(bishop_bb, from_square);
    }
}

void generatePseudoLegalRookMoves(Color side, Board& board) {
    const Bitboard targetable_squares_bb{ ~board.get_occupancy_bb(side) };
    const Piece rook{ utils::createPiece(side, BaseRook) };
    Bitboard rook_bb{ board.get_piece_bb(rook) };
    while(rook_bb) {
        const Square from_square{ utils::getFirstSquare(rook_bb) };
        Bitboard attack_bb{ attacks::getRookAttacks(from_square, board.get_occupancy_bb(Both)) & targetable_squares_bb };
        while(attack_bb) {
            const Square to_square{ utils::getFirstSquare(attack_bb) };
            if(utils::isSquareEmpty(board.get_occupancy_bb(utils::oppSide(side)), to_square)) {
                // quiet
                board.addMove(from_square, to_square, rook, NullPiece, false, false, false, false);
            } else {
                // capture
                board.addMove(from_square, to_square, rook, NullPiece, true, false, false, false);
            }
            utils::popSquare(attack_bb, to_square);
        }
        utils::popSquare(rook_bb, from_square);
    }
}

void generatePseudoLegalQueenMoves(Color side, Board& board) {
    const Piece queen{ utils::createPiece(side, BaseQueen) };
    Bitboard queen_bb{ board.get_piece_bb(queen) };
    while(queen_bb) {
        const Square from_square{ utils::getFirstSquare(queen_bb) };
        Bitboard attack_bb{ attacks::getQueenAttacks(from_square, board.get_occupancy_bb(Both)) & ~board.get_occupancy_bb(side) };
        while(attack_bb) {
            const Square to_square{ utils::getFirstSquare(attack_bb) };
            if(utils::isSquareEmpty(board.get_occupancy_bb(utils::oppSide(side)), to_square)) {
                // quiet
                board.addMove(from_square, to_square, queen, NullPiece, false, false, false, false);
            } else {
                // capture
                board.addMove(from_square, to_square, queen, NullPiece, true, false, false, false);
            }
            utils::popSquare(attack_bb, to_square);
        }
        utils::popSquare(queen_bb, from_square);
    }
}

void generatePseudoLegalKingMoves(Color side, Board& board) {
    const Bitboard targetable_squares_bb{ ~board.get_occupancy_bb(side) };
    const Piece king{ utils::createPiece(side, BaseKing) };
    Bitboard king_bb{ board.get_piece_bb(king) };
    while(king_bb) {
        const Square from_square{ utils::getFirstSquare(king_bb) };
        Bitboard attack_bb{ attacks::kings[from_square] & targetable_squares_bb };
        while(attack_bb) {
            const Square to_square{ utils::getFirstSquare(attack_bb) };
            if(utils::isSquareEmpty(board.get_occupancy_bb(utils::oppSide(side)), to_square)) {
                // quiet
                board.addMove(from_square, to_square, king, NullPiece, false, false, false, false);
            } else {
                // capture
                board.addMove(from_square, to_square, king, NullPiece, true, false, false, false);
            }
            utils::popSquare(attack_bb, to_square);
        }
        utils::popSquare(king_bb, from_square);
    }

    if(side == White) {
        if(board.get_castling() & constants::castle_wk) {
            if(utils::isSquareEmpty(board.get_occupancy_bb(Both), F1) && utils::isSquareEmpty(board.get_occupancy_bb(Both), G1)) {
                if(!attacks::isSquareAttacked(E1, Black, board) && !attacks::isSquareAttacked(F1, Black, board)) {
                    board.addMove(E1, G1, king, NullPiece, false, false, false, true);
                }
            }
        }
        if(board.get_castling() & constants::castle_wq) {
            if(utils::isSquareEmpty(board.get_occupancy_bb(Both), D1) && utils::isSquareEmpty(board.get_occupancy_bb(Both), C1) && utils::isSquareEmpty(board.get_occupancy_bb(Both), B1)) {
                if(!attacks::isSquareAttacked(E1, Black, board) && !attacks::isSquareAttacked(D1, Black, board)) {
                    board.addMove(E1, C1, king, NullPiece, false, false, false, true);
                }
            }
        }
    } else {
        if(board.get_castling() & constants::castle_bk) {
            if(utils::isSquareEmpty(board.get_occupancy_bb(Both), F8) && utils::isSquareEmpty(board.get_occupancy_bb(Both), G8)) {
                if(!attacks::isSquareAttacked(E8, White, board) && !attacks::isSquareAttacked(F8, White, board)) {
                    board.addMove(E8, G8, king, NullPiece, false, false, false, true);
                }
            }
        }
        if(board.get_castling() & constants::castle_bq) {
            if(utils::isSquareEmpty(board.get_occupancy_bb(Both), D8) && utils::isSquareEmpty(board.get_occupancy_bb(Both), C8) && utils::isSquareEmpty(board.get_occupancy_bb(Both), B8)) {
                if(!attacks::isSquareAttacked(E8, White, board) && !attacks::isSquareAttacked(D8, White, board)) {
                    board.addMove(E8, C8, king, NullPiece, false, false, false, true);
                }
            }
        }
    }
}

void generateAllMoves(Color side, Board& board) {
    generatePseudoLegalPawnMoves(side, board);
    generatePseudoLegalKnightMoves(side, board);
    generatePseudoLegalBishopMoves(side, board);
    generatePseudoLegalRookMoves(side, board);
    generatePseudoLegalQueenMoves(side, board);
    generatePseudoLegalKingMoves(side, board);
}

} // namespace dunsparce::movegen