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

void printBits(Bitboard bb);

int popcount(Bitboard b);

// lsb
// returns 64 if bitboard is empty
Square findLSB(const Bitboard& bb);

void popSquare(Bitboard& bb, Square square);
void setSquare(Bitboard& bb, Square square);

void printBB(const Bitboard& bb);

bool isSquareEmpty(const Bitboard& bb, Square square);
bool isSquareSet(const Bitboard& bb, Square square);

Piece createPiece(Color color, BasePiece base_piece);

} // namespace dunsparce::utils