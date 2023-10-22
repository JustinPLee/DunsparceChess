
#include <vector>
#include <array>
#include <string>
#include <sstream>
#include <bit>
#include <iostream>

#include "utils.hpp"

#include "types.hpp"
#include "constants.hpp"

namespace dunsparce::utils {

    Square getSquare(Rank rank, File file) {
        return Square(rank + 8 * file);
    }

    Square getSquare(File file, Rank rank) {
        return Square(rank + 8 * file);
    }

    Rank getRank(Square square) {
        return Rank(square/8+1);
    }

    File getFile(Square square) {
        return File(square%8+1);
    }

    int getRankShift(Square square) {
        return int{getFile(square)}*8+1;
    }
    
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

    void printBits(uint64_t bits) {
        if(bits == 0) {
            std::cout << 0;
            return;
        }
        std::string bit_s{};
        for(int i = 0; i < 64; ++i) {
            bit_s = std::to_string(bits&1) + bit_s;
            bits >>= 1;
        }
        std::cout << bit_s;
    }

    int popcount(uint64_t b) {
        int count = 0;
        while(b) {
            ++count;
            b &= b - 1;
        }
        return count;
    }

    bool getBit(const uint64_t& b, Square square) {
        return b & (uint64_t{1} << square);
    }
    void setBit(uint64_t& b, Square square) {
        b |= (uint64_t{1} << square);
    }
    // lsb
    // returns 64 if bitboard is empty
    int getLSBIndex(const Bitboard& b) {
        return std::countr_zero(b);
    }

    Bitboard squareToBB(Square square) {
        return Bitboard(uint64_t{1} << square);
    }

    void popBit(uint64_t& b, int square) {
        b &= ~(uint64_t{1} << square);
    }

    void printBB(const uint64_t& b) {
        std::cout << '\n';
        for(int rank = RANK1; rank < N_RANKS; ++rank) {
            for(int file = FILEA; file < N_FILES; ++file) {
                if(file == FILEA) std::cout << "  " << 8-rank << "  ";
                std::cout << (getBit(b, Square(rank * N_FILES + file)) ? " x " : " . ");
            }
            std::cout << '\n';
        }
        // print files
        std::cout << "\n      a  b  c  d  e  f  g  h\n\n"; 

        std::cout << "      Integer representation: " << b << "\n\n";
    }
}