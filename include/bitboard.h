#pragma once

#include "util.h"

namespace gee
{

void BBSet(Bitboard& bb, Square sq);
void BBClear(Bitboard& bb, Square sq);
bool BBisSet(Bitboard bb, Square sq);

std::vector<Square> BBGetSquares(Bitboard bb);
Bitboard BBGetFromSquares(std::vector<Square> squares);

void BBPrint(Bitboard bb);

} // gee