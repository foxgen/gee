#pragma once
#include "types.h"
#include <vector>

typedef uint64_t Bitboard;

void SetSquare(Bitboard& bb, Square sq);
void ClearSquare(Bitboard& bb, Square sq);
bool isSquareSet(Bitboard& bb, Square sq);

std::vector<Square> GetSquaresFromBB(Bitboard& bb);

void PrintBB(Bitboard bb);