#include "pawn.h"

namespace gee {

Bitboard PawnFigure::GetAttacks(Square s, const Position& pos)
{
    Color c = GetColor(pos.GetPiece(s));
    Bitboard bb{0};
    auto AdvanceMove = (c == WHITE) ? SQ_UP : SQ_DOWN;

    BBSet(bb,AdvanceMove(SQ_LEFT(s)));
    BBSet(bb,AdvanceMove(SQ_RIGHT(s)));

    return bb;
}

std::vector<Move> PawnFigure::GetMoves(Square s, const Position& pos)
{
    Square sq;
    Piece p = pos.GetPiece(s);
    Color baseColor = GetColor(p);

    std::vector<Move> moves;

    auto AdvanceMove = (baseColor == WHITE) ? SQ_UP : SQ_DOWN;
    bool isStartPosition = ((baseColor == WHITE) && (GetY(s) == 1)) ||
                           ((baseColor == BLACK) && (GetY(s) == 6));

    bool isPreLastLine = ((baseColor == WHITE) && (GetY(s) == 6)) ||
                           ((baseColor == BLACK) && (GetY(s) == 1));
    
    // small step
    sq = AdvanceMove(s);
    if (pos.GetPiece(sq) == NO_PIECE)
    {
        if (isPreLastLine)
        {
            // PROMOTION
            for (auto figure : { KNIGHT, BISHOP, ROOK, QUEEN })            
                moves.push_back(Move(PROMOTION, s, sq, figure));
        }
        else
        {
            moves.push_back(Move(s, sq));
        }
    }
    
    // long step
    if (isStartPosition)
    {
        sq = AdvanceMove(AdvanceMove(s));
        
        // nearest empty + jumpto empty
        if (moves.size() > 0 && pos.GetPiece(sq) == NO_PIECE)
        {
            moves.push_back(Move(s, sq));
        }
    }

    // take
    sq = AdvanceMove(SQ_LEFT(s));

    if (sq != SQ_MAX )
    {
        p = pos.GetPiece(sq);
        if (GetColor(p) == SwitchColor(baseColor))
        {
            if (isPreLastLine)
            {
                // PROMOTION
                for (auto figure : { KNIGHT, BISHOP, ROOK, QUEEN })            
                    moves.push_back(Move(PROMOTION, s, sq, figure));                    
            }
            else
            {
                moves.push_back(Move(s, sq));
            }
        }

        if (sq == pos.m_passantSQ)
        {
            moves.push_back(Move(ENPASSANT, s, sq));
        }
    }        

    sq = AdvanceMove(SQ_RIGHT(s));
    
    if (sq != SQ_MAX )
    {
        p = pos.GetPiece(sq);
        if (GetColor(p) == SwitchColor(baseColor))
        {
            if (isPreLastLine)
            {
                // PROMOTION
                for (auto figure : { KNIGHT, BISHOP, ROOK, QUEEN })            
                    moves.push_back(Move(PROMOTION, s, sq, figure));            
            }
            else
            {
                moves.push_back(Move(s, sq));
            }
        }

        if (sq == pos.m_passantSQ)
        {
            moves.push_back(Move(ENPASSANT, s, sq));
        }
    }
    
    
    return moves;
}


} // gee