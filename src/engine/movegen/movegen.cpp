#include <vector>

#include "movegen.hpp"

#include "../../move.hpp"
#include "../../board.hpp"
#include "../../constants.hpp"
#include "../../types.hpp"
#include "../../utils.hpp"
#include "tables.hpp"
#include "magic.hpp"

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
    std::vector<MoveType> generatePseudoLegalMoves(const Board& board) {
        //REFACTORRRRRrrRRrR
        std::vector<MoveType> move_list;
        move_list.reserve(MAX_MOVES);

        generatePseudoLegalPawnMoves<us>(move_list, board);
        generatePseudoLegalKnightMoves<us>(move_list, board);
        generatePseudoLegalBishopMoves<us>(move_list, board);
        generatePseudoLegalRookMoves<us>(move_list, board);
        generatePseudoLegalQueenMoves<us>(move_list, board);
        generatePseudoLegalKingMoves<us>(move_list, board);

        return move_list;
    }
    template <Color us>
    void generatePseudoLegalPawnMoves(std::vector<MoveType>& move_list, const Board& board) {
        constexpr Color opp{ static_cast<Color>(!us) };
        constexpr int double_push_rank{ (us == BLACK) ? 7 : 2 }; 
        constexpr int promotion_rank{ (us == BLACK) ? 8 : 1 };
        Bitboard candidate_pieces{ board.pieces_[us][PAWN] };
        Bitboard candidate_squares{ ~board.occupancies_[us] };

        while(candidate_pieces) {
            const Square from_square{ utils::bitScanForward(candidate_pieces) };

            // single push
            Bitboard candidate_moves { tables::moves::PAWN_SINGLE[us][from_square] & candidate_squares };
            if(utils::getRank(from_square) == double_push_rank && candidate_moves) {
                // double push
                candidate_moves |= (tables::moves::PAWN_DOUBLE[us][from_square] & candidate_squares);
            }
            // captures
            candidate_moves |= (tables::attacks::PAWN[us] & board.occupancies_[opp]);

            // loop over every possible pseudo legal move of this piece
            while(candidate_moves) {
                const Square to_square{ utils::bitScanForward(candidate_moves) };
                const Piece capture{ board.pieceAt(to_square) };
                if(utils::getRank(to_square) == promotion_rank) {
                    // promotion
                    move_list.emplace_back(from_square, to_square, Piece{ PAWN, us }, capture, Piece{ QUEEN, us }, false, false, false);
                    move_list.emplace_back(from_square, to_square, Piece{ PAWN, us }, capture, Piece{ ROOK, us }, false, false, false);
                    move_list.emplace_back(from_square, to_square, Piece{ PAWN, us }, capture, Piece{ BISHOP, us }, false, false, false);
                    move_list.emplace_back(from_square, to_square, Piece{ PAWN, us }, capture, Piece{ KNIGHT, us }, false, false, false);
                } else {
                    const bool double_push{ std::abs(from_square-to_square) > 10 };
                    move_list.emplace_back(from_square, to_square, Piece{ PAWN, us }, capture, NONE, double_push, false, false);
                }
                utils::clearBit(candidate_moves, to_square);
            }
            if(board.state_.croissant != NULL_SQUARE) {
                // if attacks a croissant square
                if(tables::attacks::PAWN[us][from_square] & board.state_.croissant) {
                    // !!!!!!!! careful !!!!!!!!
                    move_list.emplace_back(from_square, board.state_.croissant, Piece{ PAWN, us }, NONE, Piece{PAWN, opp}, false, true, false);
                }
            }
            utils::clearBit(candidate_pieces, from_square);
        }
    }

    template <Color us>
    void generatePseudoLegalKnightMoves(std::vector<MoveType>& move_list, const Board& board) {
        Bitboard candidate_pieces{ board.pieces_[us][KNIGHT] };
        Bitboard candidate_squares{ ~board.occupancies_[us] };

        while(candidate_pieces) {
            const Square from_square{ utils::bitScanForward(candidate_pieces) };
            Bitboard candidate_moves { tables::attacks::KNIGHT[us][from_square] & candidate_squares };
        
            while(candidate_moves) {
                const Square to_square{ utils::bitScanForward(candidate_moves) };
                const Piece capture{ board.pieceAt(to_square) };
                move_list.emplace_back(from_square, to_square, Piece{ KNIGHT, us }, capture, NONE, false, false, false);
                utils::clearBit(candidate_moves, to_square);
            }
            utils::clearBit(candidate_pieces, from_square);
        }
    }

    template <Color us>
    void generatePseudoLegalBishopMoves(std::vector<MoveType>& move_list, const Board& board) {
        Bitboard candidate_pieces{ board.pieces_[us][BISHOP] };
        Bitboard candidate_squares{ ~board.occupancies_[us] };

        while(candidate_pieces) {
            const Square from_square{ utils::bitScanForward(candidate_pieces) };
            Bitboard candidate_moves { tables::attacks::BISHOP[us][from_square] };
    
            while(candidate_moves) {
                const Square to_square{ utils::bitScanForward(candidate_moves) };
                const Piece capture{ board.pieceAt(to_square) };
                move_list.emplace_back(from_square, to_square, Piece{ BISHOP, us }, capture, NONE, false, false, false);
                utils::clearBit(candidate_moves, to_square);
            }
            utils::clearBit(candidate_pieces, from_square);
        }
    }

    template <Color us>
    void generatePseudoLegalRookMoves(std::vector<MoveType>& move_list, const Board& board) {
        Bitboard candidate_pieces{ board.pieces_[us][ROOK] };
        Bitboard candidate_squares{ ~board.occupancies_[us] };

        while(candidate_pieces) {
            const Square from_square{ utils::bitScanForward(candidate_pieces) };

            Bitboard candidate_moves { tables::attacks::ROOK[us][from_square] };
        
            while(candidate_moves) {
                const Square to_square{ utils::bitScanForward(candidate_moves) };
                const Piece capture{ board.pieceAt(to_square) };
                move_list.emplace_back(from_square, to_square, Piece{ ROOK, us }, capture, NONE, false, false, false);
                utils::clearBit(candidate_moves, to_square);
            }
            utils::clearBit(candidate_pieces, from_square);
        }
    }
    
    template <Color us>
    void generatePseudoLegalQueenMoves(std::vector<MoveType>& move_list, const Board& board) {
        Bitboard candidate_pieces{ board.pieces_[us][QUEEN] };
        Bitboard candidate_squares{ ~board.occupancies_[us] };

        while(candidate_pieces) {

            const Square from_square{ utils::bitScanForward(candidate_pieces) };
            Bitboard candidate_moves { tables::attacks::QUEEN[us][from_square] };
            
            while(candidate_moves) {
                const Square to_square{ utils::bitScanForward(candidate_moves) };
                const Piece capture{ board.pieceAt(to_square) };
                
                move_list.emplace_back(from_square, to_square, Piece{ QUEEN, us }, capture, NONE, false, false, false);

                utils::clearBit(candidate_moves, to_square);
            }

            utils::clearBit(candidate_pieces, from_square);
        }
    }
    
    template <Color us>
    void generatePseudoLegalKingMoves(std::vector<MoveType>& move_list, const Board& board) {
        constexpr Color opp{ static_cast<Color>(!us) };
        Bitboard candidate_pieces{ board.pieces_[us][BISHOP] };
        Bitboard candidate_squares{ ~board.occupancies_[us] };

        Square from_square, to_square;
        Piece capture, promotion, actor;

        while(candidate_pieces) {
            from_square = utils::bitScanForward(candidate_pieces);

            Bitboard candidate_moves { tables::attacks::BISHOP[us][from_square] };
            while(candidate_moves) {
                to_square = utils::bitScanForward(candidate_moves);
                capture = board.pieceAt(to_square);
                move_list.emplace_back(from_square, to_square, Piece{ BISHOP, us }, capture, NONE, false, false, false);
                utils::clearBit(candidate_moves, to_square);
            }
            // castling
            if constexpr (us == BLACK) {
                // black == 0
                // king side
                if constexpr (board.state_.castling_rights & 1
                        && !(tables::masks::FG[us] & (board.occupancies_[us] | board.occupancies_[opp]))
                        && !(isAttackedBy<opp>(tables::masks::EG[us], board))) {

                        move_list.emplace_back(Square(E8), Square(G8), Piece{ KING, us }, NONE, NONE, false, false, true);
                }
                // queen side
                if constexpr ((board.state_.castling_rights >> 1) & 1
                        && !(tables::masks::BD[us] & (board.occupancies_[us] | board.occupancies_[opp]))
                        && !(isAttackedBy<opp>(tables::masks::CE[us], board))) {

                        move_list.emplace_back(Square(E8), Square(C8), Piece{ KING, us }, NONE, NONE, false, false, true);
                }
            } else if constexpr (us == WHITE) {
                if constexpr ((board.state_.castling_rights >> 2) & 1
                        && !(tables::masks::FG[us] & (board.occupancies_[us] | board.occupancies_[opp]))
                        && !(isAttackedBy<opp>(tables::masks::EG[us], board))) {

                        move_list.emplace_back(Square(E1), Square(G1), Piece{ KING, us }, NONE, NONE, false, false, true);
                }
                // queen side
                if constexpr ((board.state_.castling_rights >> 3) & 1
                        && !(tables::masks::BD[us] & (board.occupancies_[us] | board.occupancies_[opp]))
                        && !(isAttacked<opp>(tables::masks::CE[us], board))) {

                        move_list.emplace_back(Square(E1), Square(C1), Piece{ KING, us }, NONE, NONE, false, false, true);
                }
            }
        }

    }

    template <Color attacker>
    bool isAttackedBy(Bitboard targeted, const Board& board) {
        constexpr Color us{ static_cast<Color>(!attacker) };

        while(targeted) {
            const Square to_square{ utils::bitScanForward(targeted) };

            if(board.pieces_[attacker][PAWN] & tables::attacks::PAWN[us][to_square]
                || board.pieces_[attacker][KNIGHT] & tables::attacks::KNIGHT[us][to_square]
                || board.pieces_[attacker][KING] & tables::attacks::KING[us][to_square]) {
                return true;
            }

            constexpr StaticBB rank_and_file_attackers{ board.pieces_[attacker][QUEEN] | board.pieces_[attacker][ROOK] };
            if(rank_and_file_attackers) {
                if(tables::attacks::RANK[to_square][(((board.occupancies_[attacker] | board.occupancies_[us]) & tables::masks::RANK[to_square]) >> RANKSHIFT[to_square])] & rank_and_file_attackers) return true;
                if(tables::attacks::FILE[to_square][(((board.occupancies_[attacker] | board.occupancies_[us]) & tables::masks::FILE[to_square]) * tables::magics::FILE[to_square]) >> 57] & rank_and_file_attackers) return true;
            }

            constexpr StaticBB diag_attackers{ board.pieces_[attacker][QUEEN] | board.pieces_[attacker][BISHOP] };
            if(diag_attackers) {
                if (tables::attacks::DIAGA8H1[to_square][(((board.occupancies_[attacker] | board.occupancies_[us]) & tables::masks::DIAGA8H1[to_square]) * tables::magics::DIAGA8H1[to_square]) >> 57] & diag_attackers) return true;
                if (tables::attacks::DIAGA1H8[to_square][(((board.occupancies_[attacker] | board.occupancies_[us]) & tables::masks::DIAGA1H8[to_square]) * tables::magics::DIAGA1H8[to_square]) >> 57] & diag_attackers) return true; // TODO: pls fix
            }
            utils::clearBit(targeted, to_square);
        }
    }
}