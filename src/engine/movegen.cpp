#include "movegen.hpp"

namespace dunsparce {
    [[nodiscard]] Bitboard generateOccupancyPermutation(Bitboard attack_bb, int index, int relevant_bits) {
        Bitboard occupancy_bb {bits::u64Zero};
        // loop over every possible attacked squares
        for(int count = 0; count < relevant_bits; ++count) {
            // store first square
            const Square square {bits::bitScanForward(attack_bb)};
            // remove square from remaining list of possible squares
            bits::pop(attack_bb, square);
            // only set bits under the index mask
            if(index & (1 << count)) {
                occupancy_bb |= bits::oneBitMask(square);
            }
        }
        return occupancy_bb;
    }
    Bitboard generateBishopAttacksWithBlockers(Bitboard occupany_bb, Square source) {
        Bitboard attack_bb {bits::u64Zero};
        // SE
        for(int rank = rank_of(source)+1, file = file_of(source)+1; rank <= 7 && file <= 7; ++rank, ++file) {
            Bitboard ray_br {bits::oneBitMask(index_of(rank, file))};
            attack_bb |= ray_br;
            if(ray_br & occupany_bb) break;
        }
        // NE
        for(int rank = rank_of(source)-1, file = file_of(source)+1; rank >= 0 && file <= 7; --rank, ++file) {
            const Bitboard ray_tr {bits::oneBitMask(index_of(rank, file))};
            attack_bb |= ray_tr;
            if(ray_tr & occupany_bb) break;
        }
        // SW
        for(int rank = rank_of(source)+1, file = file_of(source)-1; rank <= 7 && file >= 0; ++rank, --file) {
            const Bitboard ray_bl {bits::oneBitMask(index_of(rank, file))};
            attack_bb |= ray_bl;
            if(ray_bl & occupany_bb) break;
        }
        // NW
        for(int rank = rank_of(source)-1, file = file_of(source)-1; rank >= 0 && file >= 0; --rank, --file) {
            const Bitboard ray_tl {bits::oneBitMask(index_of(rank, file))};
            attack_bb |= ray_tl;
            if(ray_tl & occupany_bb) break;
        }
        return attack_bb;
    }
    Bitboard generateRookAttacksWithBlockers(Bitboard occupany_bb, Square source) {
        Bitboard attack_bb {bits::u64Zero}; 
        // North
        for(int rank = rank_of(source)+1; rank <= 7; ++rank) {
            Bitboard ray_n {bits::oneBitMask(index_of(rank, file_of(source)))};
            attack_bb |= ray_n;
            if(ray_n & occupany_bb) break;
        }
        // South
        for(int rank = rank_of(source)-1; rank >= 0; --rank) {
            Bitboard ray_s {bits::oneBitMask(index_of(rank, file_of(source)))};
            attack_bb |= ray_s;
            if(ray_s & occupany_bb) break;
        }
        // East
        for(int file = file_of(source)+1; file <= 7; ++file) {
            Bitboard ray_e {bits::oneBitMask(index_of(rank_of(source), file))};
            attack_bb |= ray_e;
            if(ray_e & occupany_bb) break;
        }
        // West
        for(int file = file_of(source)-1; file >= 0; --file) {
            Bitboard ray_w {bits::oneBitMask(index_of(rank_of(source), file))};
            attack_bb |= ray_w;
            if(ray_w & occupany_bb) break;
        }
        return attack_bb;
    }
    [[nodiscard]] std::vector<Move> generatePseudoLegalPawnMoves(const Board::BoardState& state) {
        std::vector<Move> moves(256);
        Bitboard pawns {state.pieces[WPawn]};
        while(pawns) {
            const Square source_square {bits::bitScanForward(pawns)};
            const Square target_move_square {Square(source_square + relPawnOffset(state.side))};
            // in-bounds
            if((target_move_square >= A8 && target_move_square <= H1) && bits::empty(state.occupancies[Both], target_move_square)) {
                // promotion
                if(rank_of(source_square) == promotionRank(state.side)) {
                    moves.emplace_back(source_square, target_move_square, WPawn, WQueen, false, false, false, false);
                    moves.emplace_back(source_square, target_move_square, WPawn, WRook, false, false, false, false);
                    moves.emplace_back(source_square, target_move_square, WPawn, WKnight, false, false, false, false);
                    moves.emplace_back(source_square, target_move_square, WPawn, WBishop, false, false, false, false);
                } else {
                    // single push
                    moves.emplace_back(source_square, target_move_square, WPawn, NullPiece, false, false, false, false);
                    // double push
                    if(rank_of(source_square) == doublePushRank(state.side) && bits::empty(state.occupancies[Both], Square(target_move_square + relPawnOffset(state.side)))) {
                        moves.emplace_back(source_square, Square(target_move_square + relPawnOffset(state.side)), WPawn, NullPiece, false, true, false, false);
                    }
                }
            }
            Bitboard attack_bb{ getPawnAttacks(state.side, source_square) & state.occupancies[Color(state.side^1)] };
            // exhaust every attack
            while(attack_bb) {
                const Square to_attack_square {bits::bitScanForward(attack_bb)};
                // promotion capture
                if(rank_of(source_square) == promotionRank(state.side)) {
                    moves.emplace_back(source_square, target_move_square, WPawn, WQueen, true, false, false, false);
                    moves.emplace_back(source_square, target_move_square, WPawn, WRook, true, false, false, false);
                    moves.emplace_back(source_square, target_move_square, WPawn, WKnight, true, false, false, false);
                    moves.emplace_back(source_square, target_move_square, WPawn, WBishop, true, false, false, false);
                } else {
                    moves.emplace_back(source_square, to_attack_square, WPawn, NullPiece, true, false, false, false);
                } 
                bits::pop(attack_bb, to_attack_square);
            }
            // croissssssant
            if(state.croissant != NullSquare) {
                Bitboard croissant_attacks {getPawnAttacks(state.side, source_square) & bits::oneBitMask(state.croissant)};
                if(croissant_attacks) {
                    const Square croissant_square{ bits::bitScanForward(croissant_attacks) };
                    moves.emplace_back(source_square, croissant_square, WPawn, NullPiece, true, false, true, false);
                }
            }
            bits::pop(pawns, source_square);
        }
        return moves;
    }

    [[nodiscard]] std::vector<Move> generatePseudoLegalSliderMoves(const Board::BoardState& state, Piece piece) {
        std::vector<Move> moves(256);
        const auto getSliderAttacks = [&](Square source_square) -> Bitboard {
            switch(piece) {
                case WKnight:
                case BKnight: return Bitboard{getKnightAttacks(source_square)};
                case WBishop:
                case BBishop: return Bitboard{getBishopAttacks(state.occupancies[Both], source_square)};
                case WRook:
                case BRook: return Bitboard{getRookAttacks(state.occupancies[Both], source_square)}; 
                case WQueen:
                case BQueen: return Bitboard{getQueenAttacks(state.occupancies[Both], source_square)};
                default: return Bitboard{bits::u64Zero};
            }
        };
        Bitboard pieces {state.pieces[piece]};
        while(pieces) {
            const Square source_square {bits::bitScanForward(pieces)};
            Bitboard attacks{ getSliderAttacks(source_square) & ~state.occupancies[state.side] };
            while(attacks) {
                const Square target_square {bits::bitScanForward(attacks)};
                if(bits::empty(state.occupancies[Color(state.side^1)], target_square)) {
                    // quiet
                    moves.emplace_back(source_square, target_square, piece, NullPiece, false, false, false, false);
                } else {
                    // capture
                    moves.emplace_back(source_square, target_square, piece, NullPiece, true, false, false, false);
                }
                bits::pop(attacks, target_square);
            }
            bits::pop(pieces, source_square);
        }
        return moves;
    }

    [[nodiscard]] std::vector<Move> generatePseudoLegalKingMoves(const Board::BoardState& state) {
            std::vector<Move> moves(256);
            const Piece king {(state.side == White) ? WKing : BKing};
            Bitboard kings {state.pieces[king]};
            while(kings) {
                const Square source_square {bits::bitScanForward(kings)};
                Bitboard attacks {getKingAttacks(source_square) & ~state.occupancies[state.side]};
                while(attacks) {
                    const Square target_square {bits::bitScanForward(attacks)};
                    if(bits::empty(state.occupancies[Color(state.side^1)], target_square)) {
                        // quiet
                        moves.emplace_back(source_square, target_square, king, NullPiece, false, false, false, false);
                    } else {
                        // capture
                        moves.emplace_back(source_square, target_square, king, NullPiece, true, false, false, false);
                    }
                    bits::pop(attacks, target_square);
                }
                if(state.side == White) {
                    if(state.castling & tables::castling::wk) {
                        if(bits::empty(state.occupancies[Both], F1) && bits::empty(state.occupancies[Both], G1)) {
                            if(!isAttacked(state, E1) && !isAttacked(state, F1)) {
                                moves.emplace_back(E1, G1, king, NullPiece, false, false, false, true);
                            }
                        }
                    }
                    if(state.castling & tables::castling::wq) {
                        if(bits::empty(state.occupancies[Both], D1) && bits::empty(state.occupancies[Both], C1) && bits::empty(state.occupancies[Both], B1)) {
                            if(!isAttacked(state, E1) && !isAttacked(state, D1)) {
                                moves.emplace_back(E1, C1, king, NullPiece, false, false, false, true);
                            }
                        }
                    }
                } else {
                    if(state.castling & tables::castling::bk) {
                        if(bits::empty(state.occupancies[Both], F8) && bits::empty(state.occupancies[Both], G8)) {
                            if(!isAttacked(state, E8) && !isAttacked(state, F8)) {
                                moves.emplace_back(E8, G8, king, NullPiece, false, false, false, true);
                            }
                        }
                    }
                    if(state.castling & tables::castling::bq) {
                        if(bits::empty(state.occupancies[Both], D8) && bits::empty(state.occupancies[Both], C8) && bits::empty(state.occupancies[Both], B8)) {
                            if(!isAttacked(state, E8) && !isAttacked(state, D8)) {
                                moves.emplace_back(E8, C8, king, NullPiece, false, false, false, true);
                            }
                        }
                    }
                }
                bits::pop(kings, source_square);
            }
            return moves;
    }

    [[nodiscard]] std::vector<Move> generateAllPseudoLegalMoves(const Board::BoardState& state) {
        std::vector<Move> moves;
        moves.reserve(256);
        std::vector<Move> pawn_moves {generatePseudoLegalPawnMoves(state)};
        moves.insert(std::end(moves), std::begin(pawn_moves), std::end(pawn_moves));
        std::vector<Move> knight_moves {generatePseudoLegalSliderMoves(state, (state.side == White) ? WKnight : BKnight)};
        moves.insert(std::end(moves), std::begin(knight_moves), std::end(knight_moves));
        std::vector<Move> bishop_moves {generatePseudoLegalSliderMoves(state, (state.side == White) ? WBishop : BBishop)};
        moves.insert(std::end(moves), std::begin(bishop_moves), std::end(bishop_moves));
        std::vector<Move> rook_moves {generatePseudoLegalSliderMoves(state, (state.side == White) ? WRook : BRook)};
        moves.insert(std::end(moves), std::begin(rook_moves), std::end(rook_moves));
        std::vector<Move> queen_moves {generatePseudoLegalSliderMoves(state, (state.side == White) ? WBishop : BQueen)};
        moves.insert(std::end(moves), std::begin(queen_moves), std::end(queen_moves));
        std::vector<Move> king_moves {generatePseudoLegalKingMoves(state)};
        moves.insert(std::end(moves), std::begin(king_moves), std::end(king_moves));
        return moves;
    }

    Bitboard getPawnAttacks(Color side, Square source) {
        return tables::moves::pawns[side][source];
    }
    Bitboard getKnightAttacks(Square source) {
        return tables::moves::knights[source];
    }
    Bitboard getKingAttacks(Square source) {
        return tables::moves::kings[source];
    }

    Bitboard getBishopAttacks(Bitboard occupancy_bb, Square source) {
        occupancy_bb &= tables::moves::bishops_unblocked[source];
        occupancy_bb *= tables::magics::bishops[source];
        occupancy_bb >>= (64 - tables::relevant_bits::bishops[source]);
        return tables::moves::bishops[source][occupancy_bb];
    }

    Bitboard getRookAttacks(Bitboard occupancy_bb, Square source) {
        occupancy_bb &= tables::moves::rooks_unblocked[source];
        occupancy_bb *= tables::magics::rooks[source];
        occupancy_bb >>= (64 - tables::relevant_bits::rooks[source]);
        return tables::moves::rooks[source][occupancy_bb];
    }

    Bitboard getQueenAttacks(Bitboard occupancy_bb, Square source) {    
        return getRookAttacks(occupancy_bb, source) | getBishopAttacks(occupancy_bb, source);
    }

    void initBishopAttacks() {
        for(size_t square = 0; square < NSquares; ++square) {
            const Bitboard attack_bb {tables::moves::bishops_unblocked[square]};
            const int relevant_bits {bits::popCount(attack_bb)};
            const int num_permutations {1 << relevant_bits};
            for(int p_idx = 0; p_idx < num_permutations; ++p_idx) {
                const Bitboard permutation_bb {generateOccupancyPermutation(attack_bb, p_idx, relevant_bits)};
                const int magic_index {static_cast<int>((permutation_bb * tables::magics::bishops[square]) >> (64 - tables::relevant_bits::bishops[square]))};
                tables::moves::bishops[square][magic_index] = generateBishopAttacksWithBlockers(permutation_bb, Square(square));
            }
        }
    }

    void initRookAttacks() {
        for(size_t square = 0; square < NSquares; ++square) {
            const Bitboard attack_bb {tables::moves::rooks_unblocked[square]};
            const int relevant_bits {bits::popCount(attack_bb)};
            const int num_permutations {1 << relevant_bits};
            for(int p_idx = 0; p_idx < num_permutations; ++p_idx) {
                const Bitboard permutation_bb {generateOccupancyPermutation(attack_bb, p_idx, relevant_bits)};
                const size_t magic_index {(permutation_bb * tables::magics::rooks[square]) >> (64 - tables::relevant_bits::rooks[square])};
                tables::moves::rooks[square][magic_index] = generateRookAttacksWithBlockers(permutation_bb, Square(square));
            }
        }   
    }

    bool isAttacked(const Board::BoardState& state, Square source) {
        if(source == NullSquare) return false;
        // cast ray from source square using every piece type
        const Piece opp_pawns {(state.side == White) ?  BPawn : WPawn};
        const Piece opp_knights {(state.side == White) ?  BKnight : WKnight};
        const Piece opp_bishops {(state.side == White) ?  BBishop : WBishop};
        const Piece opp_rooks {(state.side == White) ?  BRook : WRook};
        const Piece opp_queens {(state.side == White) ?  BQueen : WQueen};
        const Piece opp_kings {(state.side == White) ?  BKing : WKing};

        if(getPawnAttacks(state.side, source) & state.pieces[opp_pawns]) return true;
        if(getKnightAttacks(source) & state.pieces[opp_knights]) return true;
        if(getBishopAttacks(state.occupancies[Both], source) & state.pieces[opp_bishops]) return true;
        if(getRookAttacks(state.occupancies[Both], source) & state.pieces[opp_rooks]) return true;
        if(getKingAttacks(source) & state.pieces[opp_kings]) return true;
        if(getQueenAttacks(state.occupancies[Both], source) & state.pieces[opp_queens]) return true;
        return false;
    }
}