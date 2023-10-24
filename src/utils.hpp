#pragma once

#include <vector>
#include <array>
#include <string>
#include <sstream>
#include <bit>
#include <iostream>

#include "types.hpp"
#include "constants.hpp"
namespace dunsparce::utils {

char pieceToChar(Piece piece);
Piece charToPiece(char c);
std::string pieceToUnicode(Piece piece);
std::string_view squareToCoordinates(Square square);

std::vector<std::string> tokenize(const std::string& str);

void printBits(Bitboard bits);

int popcount(Bitboard b);

// lsb
// returns 64 if bitboard is empty
Square getFirstSquare(const Bitboard& bb);

void popSquare(Bitboard& bb, int square);

void printBB(const Bitboard& bb);

Color oppSide(Color color);

bool isSquareEmpty(const Bitboard& bb, Square square);

Piece createPiece(Color color, BasePiece base_piece);

} // namespace dunsparce::utils