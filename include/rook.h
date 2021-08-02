#pragma once
#include "types.h"
#include "figure.h"

namespace gee {

class RookFigure : public Figure
{
public:
    virtual Bitboard GetAttacks(Square s, const Position& pos);    
};

} // gee