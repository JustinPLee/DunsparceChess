#pragma once

#include <string_view>

#include "types.hpp"
#include "bitboard.hpp"
namespace Dunsparce {

    enum class Move { // ???
        Black = 0,
        White = 1
    };

    enum class BasePiece : uint8_t { // 7
        Pawn = 0,
        Knight,
        Bishop,
        Rook,
        Queen,
        King,
        None
    };

    enum class Piece { // 12
		BlackPawn = 0,
		WhitePawn,
		BlackKnight,
		WhiteKnight,
		BlackBishop,
		WhiteBishop,
		BlackRook,
		WhiteRook,
		BlackQueen,
		WhiteQueen,
		BlackKing,
		WhiteKing,
		None
    };

    enum class Color {
        Black = 0,
        White,
        None
    };

    // ranks? files?
    // constexpr U64 File1 = ...
    // files[8] { File1, File2, ... };

    enum class Square {
        A1, B1, C1, D1, E1, F1, G1, H1,
        A2, B2, C2, D2, E2, F2, G2, H2,
        A3, B3, C3, D3, E3, F3, G3, H3,
        A4, B4, C4, D4, E4, F4, G4, H4,
        A5, B5, C5, D5, E5, F5, G5, H5,
        A6, B6, C6, D6, E6, F6, G6, H6,
        A7, B7, C7, D7, E7, F7, G7, H7,
        A8, B8, C8, D8, E8, F8, G8, H8
    };


    // public
    struct Board {
        Bitboard pieces[12]; // pieces of both colors + none
        Bitboard colors[2];  // black, white

        bool castlingRightsShort[2]; // black, white
        bool castlingRightsLong[2];  // black, white

        Move nextMove = Move::White;
        int fiftyMove;
        int material;

        void init();
        void initFromFen(std::string_view fen);
        void display();
    };

    constexpr int PAWN_VALUE = 100;
    constexpr int KNIGHT_VALUE = 300;
    constexpr int BISHOP_VALUE = 300;
    constexpr int ROOK_VALUE = 500;
    constexpr int QUEEN_VALUE = 900;
    constexpr int KING_VALUE = 9999;
}
// IMPLEMENTATION
namespace Dunsparce {

    char basePieceToChar(BasePiece piece) {
        using enum Dunsparce::BasePiece;
        switch(piece) {
            case Pawn: return 'p'; break;
            case Knight: return 'n'; break;
            case Bishop: return 'b'; break;
            case Rook: return 'r'; break;
            case Queen: return 'q'; break;
            case King: return 'k'; break;
            case None: return ' '; break;
            default: throw "should never throw";
        }
    }

    char pieceToChar(Piece piece) {
        using enum Dunsparce::Piece;
        switch(piece) {
            case BlackPawn: return 'p'; break;
            case BlackKnight: return 'n'; break;
            case BlackBishop: return 'b'; break;
            case BlackRook: return 'r'; break;
            case BlackQueen: return 'q'; break;
            case BlackKing: return 'k'; break;

            case WhitePawn: return 'P'; break;
            case WhiteKnight: return 'N'; break;
            case WhiteBishop: return 'B'; break;
            case WhiteRook: return 'R'; break;
            case WhiteQueen: return 'Q'; break;
            case WhiteKing: return 'K'; break;

            case None: return ' '; break;
            default: throw "should never throw";
        }
    }

    bool otherMove(Move move) {
        return !static_cast<int>(move);
    }
    bool otherColor(Color color) {
        return !static_cast<int>(color);
    }
    int indexFrom(Square square) {
        return static_cast<int>(square);
    }
    Square squareFrom(int index) {
        return static_cast<Square>(index);
    }
}