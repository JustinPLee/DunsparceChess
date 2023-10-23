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
    const Color opp_side{ utils::oppSide(side) };
    const File promotion_file = (side == White ? 7 : 1);
    const File double_push_file = (side == White ? 2 : 6);
    const int rel_move_offset = (side == White ? -8 : 8);
    Piece piece{ utils::createPiece(side, BasePawn) };
    Bitboard pawn_bb{ board.pieces_[piece] };
    Square from_square, to_square;

    // exhaust every pawn in the bitboard
    while(pawn_bb) {
        from_square = utils::getFirstSquare(pawn_bb);
        to_square = Square(from_square + rel_move_offset);

        // in-bounds
        if((to_square >= A8 && to_square <= H1) && utils::isSquareEmpty(board.occupancies_[Both], to_square)) {
            // promotion
            if(utils::getFile(from_square) == promotion_file) {
                board.addMove(from_square, to_square, piece, utils::createPiece(opp_side, BaseQueen), false, false, false, false);
                board.addMove(from_square, to_square, piece, BQueen, false, false, false, false);
                board.addMove(from_square, to_square, piece, BQueen, false, false, false, false);
                board.addMove(from_square, to_square, piece, BQueen, false, false, false, false);
            } else {
                // single push

                // double push
                if(utils::getFile(from_square) == double_push_file && utils::isSquareEmpty(board.occupancies_[Both], Square(to_square + rel_move_offset))) {

                }
            }
        }
        Bitboard attack_bb{ attacks::pawns[side][from_square] & board.occupancies_[opp_side] };
        // exhaust every attack
        while(attack_bb) {
            to_square = utils::getFirstSquare(attack_bb);
            // promotion capture
            if(utils::getRank(to_square) == 7) {

            } else {

            } 
            utils::popSquare(attack_bb, to_square);
        }
        // croissssssant
        if((board.croissant_ != NullSquare) && (attacks::pawns[side][from_square] & (One << board.croissant_))) {
            // target_square = board.croissant_;
        }

        utils::popSquare(pawn_bb, from_square);
    }
}

void generatePseudoLegalKnightMoves(Color side, Board& board) {
    const Color oppSide{ utils::oppSide(side) };
    Bitboard knight_bb = (side == White ? board.pieces_[WKnight] : board.pieces_[BKnight]);
    while(knight_bb) {
        const Square from_square{ utils::getFirstSquare(knight_bb) };
        Bitboard attack_bb{ attacks::knights[from_square] & board.occupancies_[oppSide] };
        while(attack_bb) {
            const Square to_square{ utils::getFirstSquare(attack_bb) };

            // quiet
            if(utils::isSquareEmpty(board.occupancies_[oppSide], to_square)) {

            } else {
            // capture
                
            }

            utils::popSquare(attack_bb, to_square);
        }
        utils::popSquare(knight_bb, from_square);
    }
}

void generatePseudoLegalBishopMoves(Color side, Board& board) {
    const Color oppSide{ utils::oppSide(side) };
    Bitboard bishop_bb = (side == White ? board.pieces_[WBishop] : board.pieces_[BBishop]);
    while(bishop_bb) {
        const Square from_square{ utils::getFirstSquare(bishop_bb) };
        Bitboard attack_bb{ attacks::getBishopAttacks(from_square, board.occupancies_[Both]) & board.occupancies_[oppSide] };
        while(attack_bb) {
            const Square to_square{ utils::getFirstSquare(attack_bb) };

            // quiet
            if(utils::isSquareEmpty(board.occupancies_[oppSide], to_square)) {

            } else {
            // capture
                
            }

            utils::popSquare(attack_bb, to_square);
        }
        utils::popSquare(bishop_bb, from_square);
    }
}

void generatePseudoLegalRookMoves(Color side, Board& board) {
    const Color oppSide{ utils::oppSide(side) };
    Bitboard rook_bb = (side == White ? board.pieces_[WRook] : board.pieces_[BRook]);
    while(rook_bb) {
        const Square from_square{ utils::getFirstSquare(rook_bb) };
        Bitboard attack_bb{ attacks::getRookAttacks(from_square, board.occupancies_[Both]) & board.occupancies_[oppSide] };
        while(attack_bb) {
            const Square to_square{ utils::getFirstSquare(attack_bb) };

            // quiet
            if(utils::isSquareEmpty(board.occupancies_[oppSide], to_square)) {

            } else {
            // capture
                
            }

            utils::popSquare(attack_bb, to_square);
        }
        utils::popSquare(rook_bb, from_square);
    }
}

void generatePseudoLegalQueenMoves(Color side, Board& board) {
    const Color oppSide{ utils::oppSide(side) };
    Bitboard queen_bb = (side == White ? board.pieces_[WQueen] : board.pieces_[BQueen]);
    while(queen_bb) {
        const Square from_square{ utils::getFirstSquare(queen_bb) };
        Bitboard attack_bb{ attacks::getQueenAttacks(from_square, board.occupancies_[Both]) & board.occupancies_[oppSide] };
        while(attack_bb) {
            const Square to_square{ utils::getFirstSquare(attack_bb) };

            // quiet
            if(utils::isSquareEmpty(board.occupancies_[oppSide], to_square)) {

            } else {
            // capture
                
            }

            utils::popSquare(attack_bb, to_square);
        }
        utils::popSquare(queen_bb, from_square);
    }
}

void generatePseudoLegalKingMoves(Color side, Board& board) {
    const Color oppSide{ utils::oppSide(side) };
    Bitboard king_bb = (side == White ? board.pieces_[WKing] : board.pieces_[BKing]);
    while(king_bb) {
        const Square from_square{ utils::getFirstSquare(king_bb) };
        Bitboard attack_bb{ attacks::kings[from_square] & board.occupancies_[oppSide] };
        while(attack_bb) {
            const Square to_square{ utils::getFirstSquare(attack_bb) };

            // quiet
            if(utils::isSquareEmpty(board.occupancies_[oppSide], to_square)) {

            } else {
            // capture
                
            }

            utils::popSquare(attack_bb, to_square);
        }
        utils::popSquare(king_bb, from_square);
    }

    if(side == White) {
        if(board.castling_ & constants::castle_wk) {
            if(utils::isSquareEmpty(board.occupancies_[Both], F1) && utils::isSquareEmpty(board.occupancies_[Both], G1)) {
                if(!attacks::isSquareAttacked(E1, Black, board.pieces_, board.occupancies_[Both]) && !attacks::isSquareAttacked(F1, Black, board.pieces_, board.occupancies_[Both])) {

                }
            }
        }
        if(board.castling_ & constants::castle_wq) {
            if(utils::isSquareEmpty(board.occupancies_[Both], D1) && utils::isSquareEmpty(board.occupancies_[Both], C1) && utils::isSquareEmpty(board.occupancies_[Both], B1)) {
                if(!attacks::isSquareAttacked(E1, Black, board.pieces_, board.occupancies_[Both]) && !attacks::isSquareAttacked(D1, Black, board.pieces_, board.occupancies_[Both])) {
                    
                }
            }
        }
    } else {
        if(board.castling_ & constants::castle_bk) {
            if(utils::isSquareEmpty(board.occupancies_[Both], F8) && utils::isSquareEmpty(board.occupancies_[Both], G8)) {
                if(!attacks::isSquareAttacked(E8, White, board.pieces_, board.occupancies_[Both]) && !attacks::isSquareAttacked(F8, White, board.pieces_, board.occupancies_[Both])) {
                    
                }
            }
        }
        if(board.castling_ & constants::castle_bq) {
            if(utils::isSquareEmpty(board.occupancies_[Both], D8) && utils::isSquareEmpty(board.occupancies_[Both], C8) && utils::isSquareEmpty(board.occupancies_[Both], B8)) {
                if(!attacks::isSquareAttacked(E8, White, board.pieces_, board.occupancies_[Both]) && !attacks::isSquareAttacked(D8, White, board.pieces_, board.occupancies_[Both])) {
                    
                }
            }
        }
    }

}

} // namespace dunsparce::movegen