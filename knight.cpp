#include "knight.h"

namespace gee {

Bitboard KnightFigure::GetAttacks(Square s, const Position& pos)
{
    Bitboard bb{0};

    BBSet(bb,SQ_LEFT(SQ_UP(SQ_UP(s))));    
    BBSet(bb,SQ_RIGHT(SQ_UP(SQ_UP(s))));
    BBSet(bb,SQ_LEFT(SQ_LEFT(SQ_UP(s))));
    BBSet(bb,SQ_LEFT(SQ_LEFT(SQ_DOWN(s))));
    BBSet(bb,SQ_RIGHT(SQ_RIGHT(SQ_UP(s))));
    BBSet(bb,SQ_RIGHT(SQ_RIGHT(SQ_DOWN(s))));
    BBSet(bb,SQ_LEFT(SQ_DOWN(SQ_DOWN(s))));
    BBSet(bb,SQ_RIGHT(SQ_DOWN(SQ_DOWN(s))));

    return bb;
}

} // gee