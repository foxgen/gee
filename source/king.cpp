#include "king.h"

namespace gee {

Bitboard KingFigure::GetAttacks(Square s, const Position& pos)
{
    Bitboard bb{0};

    BBSet(bb,SQ_LEFT(SQ_UP(s)));
    BBSet(bb,SQ_LEFT(SQ_DOWN(s)));
    BBSet(bb,SQ_RIGHT(SQ_UP(s)));    
    BBSet(bb,SQ_RIGHT(SQ_DOWN(s)));
    
    BBSet(bb,SQ_UP(s));
    BBSet(bb,SQ_DOWN(s));
    BBSet(bb,SQ_LEFT(s));
    BBSet(bb,SQ_RIGHT(s));

    return bb;
}

std::vector<Move> KingFigure::GetCastleMoves(Color side, const Position& pos)
{
    std::vector<Move> moves;
    
    Square kingRookSq = (side == WHITE) ? SQ_H1 : SQ_H8;
    Square queenRookSq = (side == WHITE) ? SQ_A1 : SQ_A8;
    Square kingSq = (side == WHITE) ? SQ_E1 : SQ_E8;
    
    // no castling under attack
    if (BBisSet(pos.m_underAttack, kingSq))
        return {};

    // Castling    
    if ( (side == WHITE && pos.m_whiteCastleKing) ||
         (side == BLACK && pos.m_blackCastleKing) )  
    {
        Square sq_r = SQ_RIGHT(kingSq);
        Square sq_rr = SQ_RIGHT(sq_r);

        if ( (pos.GetPiece(sq_r)  == NO_PIECE) &&
             (pos.GetPiece(sq_rr) == NO_PIECE) &&
              !BBisSet(pos.m_underAttack, sq_r) &&
              !BBisSet(pos.m_underAttack, sq_rr) )
        {
            moves.push_back(Move(kingSq, KING_SIDE));
        }
    }
    if ((side == WHITE && pos.m_whiteCastleQueen) ||
        (side == BLACK && pos.m_blackCastleQueen) )
    {
        Square sq_l = SQ_LEFT(kingSq);
        Square sq_ll = SQ_LEFT(sq_l);
        Square sq_lll = SQ_LEFT(sq_ll);

        if ( (pos.GetPiece(sq_l)  == NO_PIECE) &&
             (pos.GetPiece(sq_ll) == NO_PIECE) &&
             (pos.GetPiece(sq_lll) == NO_PIECE) &&
              !BBisSet(pos.m_underAttack, sq_l) &&
              !BBisSet(pos.m_underAttack, sq_l))
        {
            moves.push_back(Move(kingSq, QUEEN_SIDE));
        }
    }    

    return moves;
}

std::vector<Move> KingFigure::GetMoves(Square s, const Position& pos)
{
    Color side = GetColor(pos.GetPiece(s));
    std::vector<Move> moves = Figure::GetMoves(s, pos);
    std::vector<Move> castleMoves = GetCastleMoves(side, pos);

    moves.insert(moves.end(), castleMoves.begin(), castleMoves.end());    

    return moves;        
}

} // gee