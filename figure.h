#pragma once
#include "types.h"
#include "bitboard.h"
#include "move.h"
#include "position.h"

namespace gee {

class Figure
{
public:    
    virtual Bitboard GetAttacks(Square s, const Position& pos) = 0;
    virtual std::vector<Move> GetMoves(Square s, const Position& Pos);    
};

} // gee