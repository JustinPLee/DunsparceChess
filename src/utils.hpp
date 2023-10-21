#pragma once

#include <vector>
#include <array>
#include <string>
#include <sstream>
#include <iostream>

#include "types.hpp"

namespace dunsparce::utils {

    inline Square getSquare(Rank rank, File file) {
        return Square(rank + 8 * file);
    }

    inline Rank getRank(Square square) {
        return Rank(square/8+1);
    }

    inline File getFile(Square square) {
        return File(square%8+1);
    }

    inline int getRankShift(Square square) {
        return int{getFile(square)}*8+1;
    }
    
    inline char pieceToChar(const Piece& piece) {
        const bool is_black = (piece.color == BLACK);
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
        const bool is_black = (piece.color == BLACK);
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
        std::string s{};
        while(bits > 0) {
            s = std::to_string(bits & 1) + s;
            bits >>= 1;
        }
        std::cout << (s.empty() ? 0 : s);
    }

    inline int popcount(Bitboard b) {
        int count = 0;
        while(b) {
            ++count;
            b >>= 1;
        }
        return count;
    }

    inline Square bitScan(const Bitboard& b) {
        if (b != 0) {
            return Square( popcount(b & -b)-1 );
        }
        return Square{ NULL_SQUARE };
    }
    // lsb
    inline Square bitScanForward(const Bitboard& b) {
        // cool algo
        static const std::array<int, 64> index64 = {
            0, 47, 1, 56, 48, 27, 2, 60,
            57, 49, 41, 37, 28, 16, 3, 61,
            54, 58, 35, 52, 50, 42, 21, 44,
            38, 32, 29, 23, 17, 11, 4, 62,
            46, 55, 26, 59, 40, 36, 15, 53,
            34, 51, 20, 43, 31, 22, 10, 45,
            25, 39, 14, 33, 19, 30, 9, 24,
            13, 18, 8, 12, 7, 6, 5, 63
        };
        static constexpr StaticBB debruijn64 = 0x03f79d71b4cb0a89;
        return Square(index64[((b ^ (b - 1)) * debruijn64) >> 58]);
    }

    inline void clearBit(Bitboard& b, Square square) {
        b ^= (uint64_t{1} << (N_SQUARES - int{square}));
    }

    inline void printBB(const Bitboard& b) {
        for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++) {
            const int n = 63-8*i-j;
            std::cout << ((b >> n) & 1 ? 'x' : '.');
        }
        std::cout << '\n';
        }
    }
}