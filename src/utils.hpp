#pragma once

#include <vector>
#include <string>
#include <sstream>
#include "types.hpp"

namespace utils {
    inline Square getSquare(Rank rank, File file) {
        return (Square)(rank + 8 * file);
    }
    inline Rank getRank(Square square) {
        return (Rank)(1);
    }
    inline File getFile(Square square) {
        return (File)(1);
    }

    inline char pieceToChar(Piece piece) {
        bool isBlack = (piece.color == BLACK);
        switch(piece.type) {
            case PAWN:   return isBlack ? 'p' : 'P';
            case KNIGHT: return isBlack ? 'n' : 'N';
            case BISHOP: return isBlack ? 'b' : 'B';
            case ROOK:   return isBlack ? 'r' : 'R';
            case QUEEN:  return isBlack ? 'q' : 'Q';
            case KING:   return isBlack ? 'k' : 'K';
            case NONE:   return ' ';
            default: throw std::invalid_argument("invalid piece type");
        }
    }

    inline Piece charToPiece(char c) {
        switch(c) {
            case 'p': return { PAWN, BLACK };
            case 'n': return { KNIGHT, BLACK };
            case 'b': return { BISHOP, BLACK };
            case 'r': return { ROOK, BLACK };
            case 'q': return { QUEEN, BLACK };
            case 'k': return { KING, BLACK };
            case 'P': return { PAWN, WHITE };
            case 'N': return { KNIGHT, WHITE };
            case 'B': return { BISHOP, WHITE };
            case 'R': return { ROOK, WHITE };
            case 'Q': return { QUEEN, WHITE };
            case 'K': return { KING, WHITE };
            case ' ': return { NONE, NULL_COLOR };
            default: throw std::invalid_argument("invalid piece character");
        }
    }
    inline std::string pieceToUnicode(Piece piece) {
        bool isBlack = (piece.color == BLACK);
        switch(piece.type) {
            case PAWN:   return isBlack ? "♟︎" : "♙";
            case KNIGHT: return isBlack ? "♞" : "♘";
            case BISHOP: return isBlack ? "♝" : "♗";
            case ROOK:   return isBlack ? "♜" : "♖";
            case QUEEN:  return isBlack ? "♛" : "♕";
            case KING:   return isBlack ? "♚" : "♔";
            case NONE:   return " ";
            default: throw std::invalid_argument("invalid piece type");
        }
    }

    inline std::vector<std::string> tokenize(const std::string& str) {
        std::vector<std::string> tokens;
        std::istringstream ss(str);
        std::string value;
        while(ss >> value) {
            tokens.push_back(value);
        }
        return tokens;
    }
}