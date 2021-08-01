#include "bishop.h"

namespace gee {

Bitboard BishopFigure::GetAttacks(Square s, const Position& pos)
{
    Bitboard bb{0};

    auto ProcessMove = [&](Square sq) {       
        BBSet(bb, sq);
        // stop if square is occupied
        return pos.GetPiece(sq) == NO_PIECE;
    };

    for (Square sq = SQ_UP(SQ_RIGHT(s)); sq != SQ_MAX; sq = SQ_UP(SQ_RIGHT(sq)))
    {
        if (!ProcessMove(sq))
            break;
    }

    for (Square sq = SQ_UP(SQ_LEFT(s)); sq != SQ_MAX; sq = SQ_UP(SQ_LEFT(sq)))
    {
        if (!ProcessMove(sq))
            break;
    }

    for (Square sq = SQ_DOWN(SQ_RIGHT(s)); sq != SQ_MAX; sq = SQ_DOWN(SQ_RIGHT(sq)))
    {
        if (!ProcessMove(sq))
            break;
    }

    for (Square sq = SQ_DOWN(SQ_LEFT(s)); sq != SQ_MAX; sq = SQ_DOWN(SQ_LEFT(sq)))
    {
        if (!ProcessMove(sq))
            break;
    }

    return bb;
}

} // gee