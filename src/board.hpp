#pragma once

#include <array>
#include <string_view>

#include "types.hpp"
#include "constants.hpp"
#include "bitboard.hpp"

class Board {
    public:
        Board();
        struct BoardState {
            std::array<Piece, 64> squares;
            Color nextMove;
            int fiftyMoves;
            bool castlingRightsWhiteShort;
            bool castlingRightsWhiteLong;
            bool castlingRightsBlackShort;
            bool castlingRightsBlackLong;
            int croissant;
        };

        void init();
        void initFromFen(std::string_view fen);
        int evalPieceMaterial();
        Color oppColor(Color color);
        char pieceToChar(Piece piece);

    private:
        void initState(const BoardState& state);

        Bitboard whitePawnsBB;
        Bitboard whiteKnightsBB;
        Bitboard whiteBishopsBB;
        Bitboard whiteRooksBB;
        Bitboard whiteQueensBB;
        Bitboard whiteKingBB;
        
        Bitboard blackPawnsBB;
        Bitboard blackKnightsBB;
        Bitboard blackBishopsBB;
        Bitboard blackRooksBB;
        Bitboard blackQueensBB;
        Bitboard blackKingBB;

        Bitboard whitePiecesBB;
        Bitboard blackPiecesBB;
        Bitboard occupiedBB;

        int pieceMaterial;
        BoardState state;
};
