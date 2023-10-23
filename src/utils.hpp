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

Square convertToSquare(Rank rank, File file);

Rank getRank(Square square);
File getFile(Square square);

int getRankShift(Square square);

char pieceToChar(const Piece& piece);
Piece charToPiece(char c);
std::string pieceToUnicode(Piece piece);
std::string_view squareToCoordinates(Square square);

std::vector<std::string> tokenize(const std::string& str);

void printBits(Bitboard bits);

int popcount(Bitboard b);

bool getSquare(const Bitboard& bb, Square square);
void setSquare(Bitboard& bb, Square square);
// lsb
// returns 64 if bitboard is empty
Square getFirstSquare(const Bitboard& bb);

void popSquare(Bitboard& bb, int square);

Bitboard squareToBB(Square square);

void printBB(const Bitboard& bb);

Bitboard shiftRel(Bitboard bb, int val, Color color);

Color oppSide(Color color);

bool isSquareEmpty(const Bitboard& bb, Square square);

} // namespace dunsparce::utils