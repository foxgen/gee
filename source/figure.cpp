#include "figure.h"
#include "bishop.h"
#include "rook.h"
#include "queen.h"
#include "knight.h"
#include "king.h"
#include "pawn.h"

namespace gee {

std::vector<Move> Figure::GetMoves(Square s, const Position& pos)
{
    std::vector<Move> moves;

    Color c = GetColor(pos.GetPiece(s));    
    Bitboard bb = GetAttacks(s, pos);
    std::vector<Square> squares = BBGetSquares(bb);
    
    for (auto sq : squares)
    {
        Piece p = pos.GetPiece(sq);
        if (GetColor(p) != c)
            moves.push_back(Move(s, sq));           
    }

    return moves;
}

} // gee