#pragma once
#include "types.h"
#include "figure.h"

namespace gee {

class PawnFigure : public Figure
{
public:
    virtual Bitboard GetAttacks(Square s, const Position& pos);    
    virtual std::vector<Move> GetMoves(Square s, const Position& pos);
};

} // gee