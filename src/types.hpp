#pragma once

#include <unordered_map>
#include <iostream>

namespace dunsparce {
    using Bitboard = uint64_t;

    enum Square : int {
        A8, B8, C8, D8, E8, F8, G8, H8,
        A7, B7, C7, D7, E7, F7, G7, H7,
        A6, B6, C6, D6, E6, F6, G6, H6,
        A5, B5, C5, D5, E5, F5, G5, H5,
        A4, B4, C4, D4, E4, F4, G4, H4,
        A3, B3, C3, D3, E3, F3, G3, H3,
        A2, B2, C2, D2, E2, F2, G2, H2,
        A1, B1, C1, D1, E1, F1, G1, H1,
        NSquares = 64, NullSquare = 65
    };
    constexpr int rank_of(Square square) { return (square / 8); }
    constexpr int file_of(Square square) { return (square % 8); }
    constexpr int index_of(int rank, int file) { return (rank * 8 + file); }

    enum Direction : int {
        North = 8,
        South = 8,
        West = 1,
        East = 1,
        NorthWest = North - West,
        NorthEast = North + East,
        SouthWest = South - West,
        SouthEast = South + East,
    };

    enum Color : int {
        Black = 0,
        White = 1,
        Both = 2,
        NColors = 2
    };

    enum BasePiece : int {
        BasePawn = 0,
        BaseKnight = 1,
        BaseBishop = 2,
        BaseRook = 3,
        BaseQueen = 4,
        BaseKing = 5
    };

    enum Piece : int {
        BPawn = 0,
        BKnight = 1,
        BBishop = 2,
        BRook = 3,
        BQueen = 4,
        BKing = 5,
        WPawn = 6,
        WKnight = 7,
        WBishop = 8,
        WRook = 9,
        WQueen = 10,
        WKing = 11,
        NPieces = 12,
        NullPiece = 12,
    };
    constexpr Color color_of(Piece piece) { return Color(piece < NPieces/2 ? Black : White); }
    static inline const std::unordered_map<Piece, char, std::hash<int>> piece_char_map {
        {WPawn, 'P'},
        {WKnight, 'K'},
        {WBishop, 'B'},
        {WRook, 'R'},
        {WQueen, 'Q'},
        {WKing, 'K'},
        {BPawn, 'p'},
        {BKnight, 'n'},
        {BBishop, 'b'},
        {BRook, 'r'},
        {BQueen, 'q'},
        {BKing, 'k'},
        {NullPiece, '?'}
    };
    static inline const std::unordered_map<char, Piece> char_piece_map {
        {'P', WPawn},
        {'K', WKnight},
        {'B', WBishop},
        {'R', WRook},
        {'W', WQueen},
        {'K', WKing},
        {'p', BPawn},
        {'k', BKnight},
        {'b', BBishop},
        {'r', BRook},
        {'q', BQueen},
        {'k', BKing},
        {'?', NullPiece}
    };
    static inline const std::unordered_map<Piece, std::string, std::hash<int>> piece_unicode_map {
        {WPawn, "♙"},
        {WKnight, "♘"},
        {WBishop, "♗"},
        {WRook, "♖"},
        {WQueen, "♕"},
        {WKing, "♔"},
        {BPawn, "♟︎"},
        {BKnight, "♞"},
        {BBishop, "♝"},
        {BRook, "♜"},
        {BQueen, "♛"},
        {BKing, "♚"},
        {NullPiece, "?"}
    };

    static inline int promotionRank(Color color) {
        if(color == White) {
            return 1;
        } else {
            return 6;
        }
    }

    static inline int doublePushRank(Color color) {
        if(color == White) {
            return 6;
        } else {
            return 1;
        }
    }

    static inline int relPawnOffset(Color color) {
        if(color == White) {
            return -8;
        } else {
            return 8;
        }
    }

    static inline char pieceToChar(Piece piece) {
        return piece_char_map.at(piece);
    }

    static inline Piece charToPiece(char ch) {
        return char_piece_map.at(ch);
    }

    static inline std::string pieceToUnicode(Piece piece) {
        return piece_unicode_map.at(piece);
    }

    static inline std::string squareToCoordinates(Square square) {
        static const std::array<std::string, NSquares+1> notations {
            "a8", "b8", "c8", "d8", "e8", "f8", "g8", "h8",
            "a7", "b7", "c7", "d7", "e7", "f7", "g7", "h7",
            "a6", "b6", "c6", "d6", "e6", "f6", "g6", "h6",
            "a5", "b5", "c5", "d5", "e5", "f5", "g5", "h5",
            "a4", "b4", "c4", "d4", "e4", "f4", "g4", "h4",
            "a3", "b3", "c3", "d3", "e3", "f3", "g3", "h3",
            "a2", "b2", "c2", "d2", "e2", "f2", "g2", "h2",
            "a1", "b1", "c1", "d1", "e1", "f1", "g1", "h1",
            "-"
        };
        return notations[square];
    }
}