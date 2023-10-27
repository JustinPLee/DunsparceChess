#pragma once

#include "../../types.hpp"
#include "../../constants.hpp"

/***
 * 
 * Magic numbers are essentially a hash used for calculating rook and bishop and by extension queen pieces.
 * They greatly speed up move evaluation. 
 * 
*/
namespace dunsparce::magic {

/**
 * Randomizes seed
 * @return new seed
*/
uint32_t reseed();

/**
 * Combines multiple 32 bit unsigned ints into a unsigned 64 bit bitboard aka a magic number
 * @return `Bitboard`
*/
Bitboard generateRandomBB();

/**
 * Generates an occupancy bitboard with bits set of the specific permutation indexed by `index` of the specified attack bitboard
 * and its corresponding relevant_bits that is stored in a precomputed lookup table
 * @note `relevant_bits == popcount(attack_bb)`
 * @return `Bitboard` 
*/
Bitboard generateOccupancyBBPermutation(int index, int relevant_bits, Bitboard attack_bb);

/**
 * Computes the magic hash of either a bishop or rook
*/
Bitboard generateMagicNumber(Square source, int relevant_bits, BasePiece base_piece);

// Called once in the creation process of the engine.
// Currently not meant to be called during runtime.
void initMagic();

// proven (?) good magic number seed
inline uint32_t seed{ 1804289383 };

} // namespace dunsparce::magic