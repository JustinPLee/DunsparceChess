
#include <vector>
#include <array>
#include <string>
#include <sstream>
#include <bit>
#include <iostream>
#include "assert.h"

#include "utils.hpp"

#include "types.hpp"
#include "constants.hpp"

namespace dunsparce::utils {

    char pieceToChar(const Piece& piece) {
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

    Piece charToPiece(char c) {
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

    std::string pieceToUnicode(Piece piece) {
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

    std::string_view squareToCoordinates(Square square) {
        return SQUARE_NAMES[square];
    }

    std::vector<std::string> tokenize(const std::string& str) {
        std::vector<std::string> tokens;
        std::istringstream ss(str);
        std::string value;
        while(ss >> value) {
            tokens.push_back(value);
        }
        return tokens;
    }

    void printBits(Bitboard bb) {
        if(bb == 0) {
            std::cout << 0;
            return;
        }
        std::string bit_s{};
        for(int i = 0; i < 64; ++i) {
            bit_s = std::to_string(bb & 1) + bit_s;
            bb >>= 1;
        }
        std::cout << bit_s;
    }

    int popcount(Bitboard bb) {
        int count = 0;
        while(bb) {
            ++count;
            bb &= bb - 1;
        }
        return count;
    }

    bool getSquare(const Bitboard& bb, Square square) {
        return bb & squareToBB(square);
    }
    void setSquare(Bitboard& bb, Square square) {
        bb |= squareToBB(square);
    }

    // lsb (from topleft)
    Square getFirstSquare(const Bitboard& bb) {
        if (bb) {
            return Square(popcount((bb & -bb) - 1));
        } else {
            return NULL_SQUARE;
        }
    }

    Bitboard squareToBB(Square square) {
        return Bitboard(ONE << square);
    }

    void popSquare(Bitboard& bb, int square) {
        bb &= ~(Bitboard{1} << square);
    }

    void printBB(const Bitboard& bb) {
        std::cout << '\n';
        for(Rank rank = 0; rank < 8; ++rank) {
            for(File file = 0; file < 8; ++file) {
                if(file == 0) std::cout << "  " << 8-rank << "  ";
                std::cout << (getSquare(bb, convertToSquare(rank, file)) ? " x " : " . ");
            }
            std::cout << '\n';
        }
        // print files
        std::cout << "\n      a  b  c  d  e  f  g  h\n\n"; 

        std::cout << "      Integer representation: " << bb << "\n\n";
    }

    Square convertToSquare(Rank rank, File file) {
        return Square(rank * 8 + file);
    }

    Rank getRank(Square square) {
        return Rank(square/8);
    }

    File getFile(Square square) {
        return File(square%8);
    }

    int getRankShift(Square square) {
        return getFile(square)*8+1;
    }

}