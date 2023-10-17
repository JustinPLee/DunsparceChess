#pragma once

#include <vector>
#include <string>
#include <sstream>
#include <iostream>

#include "types.hpp"

namespace utils {

    inline Square getSquare(Rank rank, File file) {
        return Square(rank + 8 * file);
    }

    inline Rank getRank(Square square) {
        return Rank(1);
    }

    inline File getFile(Square square) {
        return File(1);
    }

    inline char pieceToChar(Piece piece) {
        bool is_black = (piece.color == BLACK);
        switch(piece.type) {
            case PAWN:   return is_black ? 'p' : 'P';
            case KNIGHT: return is_black ? 'n' : 'N';
            case BISHOP: return is_black ? 'b' : 'B';
            case ROOK:   return is_black ? 'r' : 'R';
            case QUEEN:  return is_black ? 'q' : 'Q';
            case KING:   return is_black ? 'k' : 'K';
            case NONE:   return ' ';
            default: throw std::invalid_argument("invalid piece");
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
            default: throw std::invalid_argument("invalid character");
        }
    }

    inline std::string pieceToUnicode(Piece piece) {
        bool is_black = (piece.color == BLACK);
        switch(piece.type) {
            case PAWN:   return is_black ? "♟︎" : "♙";
            case KNIGHT: return is_black ? "♞" : "♘";
            case BISHOP: return is_black ? "♝" : "♗";
            case ROOK:   return is_black ? "♜" : "♖";
            case QUEEN:  return is_black ? "♛" : "♕";
            case KING:   return is_black ? "♚" : "♔";
            case NONE:   return " ";
            default: throw std::invalid_argument("invalid piece");
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

    inline void printBits(uint64_t bits) {
        std::string s = "";
        while(bits > 0) {
            s = std::to_string(bits & 1) + s;
            bits >>= 1;
        }
        std::cout << (s == "" ? 0 : s);
    }
}