#include "move.h"


std::vector<Move> RookMoves(Square s, const Position& pos)
{
    std::vector<Move> moves;
    Piece p = pos.GetPiece(s);
    Color baseColor = GetColor(p);

    if (baseColor == NO_COLOR)
        return moves;
    
    auto ProcessMove = [&](Square sq) {       

        Piece p = pos.GetPiece(sq);
        if (p != NO_PIECE)
        {
            if (baseColor == GetColor(p))
                return false;
            moves.emplace_back(Move(s, sq));
            return false;
        }            
        moves.push_back(Move(s, sq));
        return true;
    };

    for (Square sq = SQ_UP(s); sq != SQ_MAX; sq = SQ_UP(sq))
    {
        if (!ProcessMove(sq))
            break;
    }

    for (Square sq = SQ_DOWN(s); sq != SQ_MAX; sq = SQ_DOWN(sq))
    {        
        if (!ProcessMove(sq))
            break;
    }

    for (Square sq = SQ_LEFT(s); sq != SQ_MAX; sq = SQ_LEFT(sq))
    {        
        if (!ProcessMove(sq))
            break;
    }

    for (Square sq = SQ_RIGHT(s); sq != SQ_MAX; sq = SQ_RIGHT(sq))
    {        
        if (!ProcessMove(sq))
            break;
    }
    
    return moves;
}

std::vector<Move> BishopMoves(Square s, const Position& pos)
{
    std::vector<Move> moves;
    Piece p = pos.GetPiece(s);
    Color baseColor = GetColor(p);

    if (baseColor == NO_COLOR)
        return moves;
    
    auto ProcessMove = [&](Square sq) {       

        Piece p = pos.GetPiece(sq);
        if (p != NO_PIECE)
        {
            if (baseColor == GetColor(p))
                return false;
            moves.emplace_back(Move(s, sq));
            return false;
        }            
        moves.push_back(Move(s, sq));
        return true;
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

    return moves;
}

std::vector<Move> KnightMoves(Square s, const Position& pos)
{
    std::vector<Move> moves;    
    Piece p = pos.GetPiece(s);
    Color baseColor = GetColor(p);

    auto ProcessMove = [&](Square sq){
        if (sq != SQ_MAX)
        {
            p = pos.GetPiece(sq);
            if (p != NO_PIECE)
            {
                if (baseColor != GetColor(p))                
                    moves.push_back(Move(s, sq));
            }
            else
            {
                moves.push_back(Move(s, sq));
            }
        }
    };
    
    ProcessMove(SQ_LEFT(SQ_UP(SQ_UP(s))));    
    ProcessMove(SQ_RIGHT(SQ_UP(SQ_UP(s))));
    ProcessMove(SQ_LEFT(SQ_LEFT(SQ_UP(s))));
    ProcessMove(SQ_LEFT(SQ_LEFT(SQ_DOWN(s))));
    ProcessMove(SQ_RIGHT(SQ_RIGHT(SQ_UP(s))));
    ProcessMove(SQ_RIGHT(SQ_RIGHT(SQ_DOWN(s))));
    ProcessMove(SQ_LEFT(SQ_DOWN(SQ_DOWN(s))));
    ProcessMove(SQ_RIGHT(SQ_DOWN(SQ_DOWN(s))));

    return moves;
}

std::vector<Move> QueenMoves(Square s, const Position& pos)
{
    std::vector<Move> moves;
    std::vector<Move> qm = BishopMoves(s, pos);

    moves = RookMoves(s, pos);
    moves.insert(moves.end(), qm.begin(), qm.end());

    return moves;    
}

std::vector<Move> KingMoves(Square s, const Position& pos)
{
    std::vector<Move> moves;
    Piece p = pos.GetPiece(s);
    Color baseColor = GetColor(p);

    auto ProcessMove = [&](Square sq){        
        if (sq != SQ_MAX)
        {
            p = pos.GetPiece(sq);
            if (p != NO_PIECE)
            {
                if (baseColor != GetColor(p))                
                    moves.push_back(Move(s, sq));
            }
            else
            {
                moves.push_back(Move(s, sq));
            }
        }
    };

    ProcessMove(SQ_LEFT(SQ_UP(s)));
    ProcessMove(SQ_LEFT(SQ_DOWN(s)));
    ProcessMove(SQ_RIGHT(SQ_UP(s)));    
    ProcessMove(SQ_RIGHT(SQ_DOWN(s)));
    
    ProcessMove(SQ_UP(s));
    ProcessMove(SQ_DOWN(s));
    ProcessMove(SQ_LEFT(s));
    ProcessMove(SQ_RIGHT(s));

    Square kingRookSq = (baseColor == WHITE) ? SQ_H1 : SQ_H8;
    Square queenRookSq = (baseColor == WHITE) ? SQ_A1 : SQ_A8;

    // Castling    
    if ( (baseColor == WHITE && pos.m_whiteCastleKing) ||
         (baseColor == BLACK && pos.m_blackCastleKing) )  
    {
        if ( (pos.GetPiece(SQ_RIGHT(s))           == NO_PIECE) &&
             (pos.GetPiece(SQ_RIGHT(SQ_RIGHT(s))) == NO_PIECE) )
        {
            moves.push_back(Move(s, KING_SIDE));
        }
    }
    if ((baseColor == WHITE && pos.m_whiteCastleQueen) ||
        (baseColor == BLACK && pos.m_blackCastleQueen) )
    {
        if ( (pos.GetPiece(SQ_LEFT(s))          == NO_PIECE) &&
             (pos.GetPiece(SQ_LEFT(SQ_LEFT(s))) == NO_PIECE) )
        {
            moves.push_back(Move(s, QUEEN_SIDE));
        }
    }    

    return moves;    
}

std::vector<Move> PawnMoves(Square s, const Position& pos)
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
                moves.push_back(Move(PROMOTION, s, sq, MakePiece(figure, baseColor)));            
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
                    moves.push_back(Move(PROMOTION, s, sq, MakePiece(figure, baseColor)));            
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
                    moves.push_back(Move(PROMOTION, s, sq, MakePiece(figure, baseColor)));            
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

std::vector<Move> GenerateMoves(Square s, const Position& pos)
{
    std::vector<Move> moves;
    Piece p = pos.GetPiece(s);

    if (p == NO_PIECE)
        return moves;
    

    return moves;    
}