#include "bishop.h"
#include "rook.h"
#include "queen.h"

namespace gee {

Bitboard QueenFigure::GetAttacks(Square s, const Position& pos)
{
    Bitboard bb{0};

    bb |= BishopFigure().GetAttacks(s, pos);
    bb |= RookFigure().GetAttacks(s, pos);

    return bb;
}

} // gee