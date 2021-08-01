#include "bishop.h"
#include "rook.h"
#include "queen.h"

namespace gee {

Bitboard BishopFigure::GetAttacks(Square s, const Position& pos)
{
    Bitboard bb{0};

    bb |= BishopAttacks(s, pos);
    bb |= RookAttacks(s, pos);

    return bb;
}

} // gee