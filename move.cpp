#include "move.h"

std::string Move::to_string()
{
    switch (m_type)
    {
    case PROMOTION:
        {    
            std::string figure = 
                    (m_newFigure == QUEEN) ? "q" :
                    (m_newFigure == BISHOP) ? "b" :
                    (m_newFigure == ROOK) ? "r" :
                    (m_newFigure == KNIGHT) ? "n" : "-";

            return SquareToString(m_from) + SquareToString(m_to) + figure;
        }
        break;    
    case CASTLING:
        if (m_castlingSide == KING_SIDE)
            return SquareToString(m_from) + SquareToString(SQ_RIGHT(SQ_RIGHT(m_from)));
        if (m_castlingSide == QUEEN_SIDE)
            return SquareToString(m_from) + SquareToString(SQ_LEFT(SQ_LEFT(m_from)));    
        break;
    case ENPASSANT:
    case NORMAL:
    default:
        return SquareToString(m_from) + SquareToString(m_to);
        break;
    } 

    return "0000";   
}

void Move::from_string(const std::string &movestr, const Position& pos)
{
    // By default the move is NORMAL
    m_from = StringToSquare(movestr);
    m_to = StringToSquare(movestr.substr(2));
    m_type = NORMAL;

    // e7e8q : size==5 -> PROMOTION
    if (movestr.size() == 5)
    {
        m_type = PROMOTION;
        switch (movestr.back())
        {
        case 'q':
            m_newFigure = QUEEN;
            break;
        case 'b':
            m_newFigure = BISHOP;
            break;
        case 'r':
            m_newFigure = ROOK;
            break;
        case 'n':
            m_newFigure = KNIGHT;
            break;
        default:
            m_newFigure = NO_PIECE_TYPE;
            break;
        }
    }
    
    // KING jump -> CASTLING
    if (GetPieceType(pos.GetPiece(m_from)) == KING)
    if (m_from == SQ_E1 && m_to == SQ_G1 ||
        m_from == SQ_E8 && m_to == SQ_G8 ||
        m_from == SQ_E1 && m_to == SQ_C1 ||
        m_from == SQ_E8 && m_to == SQ_C8)
    {
        m_type = CASTLING;
        if ((m_to == SQ_G1) || (m_to == SQ_G8))
            m_castlingSide = KING_SIDE;
        if ((m_to == SQ_C1) || (m_to == SQ_C8))
            m_castlingSide = QUEEN_SIDE;
    }

    // PAWN go to passantSQ -> ENPASSANT
    if (GetPieceType(pos.GetPiece(m_from)) == PAWN)
    {
        if (m_to == pos.m_passantSQ)
            m_type = ENPASSANT;
    }
}

Bitboard RookAttacks(Square s, const Position& pos)
{
    Bitboard bb{0};

    auto ProcessMove = [&](Square sq) {       
        SetSquare(bb, sq);
        // stop if square is occupied
        return pos.GetPiece(sq) == NO_PIECE;
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

    return bb;
}

std::vector<Move> RookMoves(Square s, const Position& pos)
{
    std::vector<Move> moves;
    Bitboard bb = RookAttacks(s, pos);
    std::vector<Square> squares = GetSquaresFromBB(bb);
    for (auto sq : squares)
    {
        Piece p = pos.GetPiece(sq);
        if (GetColor(p) != pos.m_sideToMove)
            moves.push_back(Move(s, sq));           
    }

    return moves;
}

Bitboard BishopAttacks(Square s, const Position& pos)
{
    Bitboard bb{0};

    auto ProcessMove = [&](Square sq) {       
        SetSquare(bb, sq);
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

std::vector<Move> BishopMoves(Square s, const Position& pos)
{
    std::vector<Move> moves;
    Bitboard bb = BishopAttacks(s, pos);
    std::vector<Square> squares = GetSquaresFromBB(bb);
    for (auto sq : squares)
    {
        Piece p = pos.GetPiece(sq);
        if (GetColor(p) != pos.m_sideToMove)
            moves.push_back(Move(s, sq));           
    }

    return moves;
}

Bitboard KnightAttacks(Square s, const Position& pos)
{
    Bitboard bb{0};

    SetSquare(bb,SQ_LEFT(SQ_UP(SQ_UP(s))));    
    SetSquare(bb,SQ_RIGHT(SQ_UP(SQ_UP(s))));
    SetSquare(bb,SQ_LEFT(SQ_LEFT(SQ_UP(s))));
    SetSquare(bb,SQ_LEFT(SQ_LEFT(SQ_DOWN(s))));
    SetSquare(bb,SQ_RIGHT(SQ_RIGHT(SQ_UP(s))));
    SetSquare(bb,SQ_RIGHT(SQ_RIGHT(SQ_DOWN(s))));
    SetSquare(bb,SQ_LEFT(SQ_DOWN(SQ_DOWN(s))));
    SetSquare(bb,SQ_RIGHT(SQ_DOWN(SQ_DOWN(s))));

    return bb;
}

std::vector<Move> KnightMoves(Square s, const Position& pos)
{
    std::vector<Move> moves;
    Bitboard bb = KnightAttacks(s, pos);
    std::vector<Square> squares = GetSquaresFromBB(bb);
    for (auto sq : squares)
    {
        Piece p = pos.GetPiece(sq);
        if (GetColor(p) != pos.m_sideToMove)
            moves.push_back(Move(s, sq));           
    }

    return moves;
}

Bitboard QueenAttacks(Square s, const Position& pos)
{
    Bitboard bb{0};

    bb |= BishopAttacks(s, pos);
    bb |= RookAttacks(s, pos);

    return bb;
}

std::vector<Move> QueenMoves(Square s, const Position& pos)
{
    std::vector<Move> moves;
    std::vector<Move> qm = BishopMoves(s, pos);

    moves = RookMoves(s, pos);
    moves.insert(moves.end(), qm.begin(), qm.end());

    return moves;    
}

Bitboard KingAttacks(Square s, const Position& pos)
{
    Bitboard bb{0};

    SetSquare(bb,SQ_LEFT(SQ_UP(s)));
    SetSquare(bb,SQ_LEFT(SQ_DOWN(s)));
    SetSquare(bb,SQ_RIGHT(SQ_UP(s)));    
    SetSquare(bb,SQ_RIGHT(SQ_DOWN(s)));
    
    SetSquare(bb,SQ_UP(s));
    SetSquare(bb,SQ_DOWN(s));
    SetSquare(bb,SQ_LEFT(s));
    SetSquare(bb,SQ_RIGHT(s));

    return bb;
}

std::vector<Move> KingMoves(Square s, const Position& pos)
{
    std::vector<Move> moves;
    Bitboard bb = KingAttacks(s, pos);
    std::vector<Square> squares = GetSquaresFromBB(bb);
    for (auto sq : squares)
    {
        Piece p = pos.GetPiece(sq);
        if (GetColor(p) != pos.m_sideToMove && !isSquareSet(pos.m_underAttack, sq))
            moves.push_back(Move(s, sq));           
    }

    return moves;    
}

std::vector<Move> CastleMoves(Color side, const Position& pos)
{
    std::vector<Move> moves;
    
    Square kingRookSq = (side == WHITE) ? SQ_H1 : SQ_H8;
    Square queenRookSq = (side == WHITE) ? SQ_A1 : SQ_A8;
    Square kingSq = (side == WHITE) ? SQ_E1 : SQ_E8;
    
    // no castling under attack
    if (isSquareSet(pos.m_underAttack, kingSq))
        return {};

    // Castling    
    if ( (side == WHITE && pos.m_whiteCastleKing) ||
         (side == BLACK && pos.m_blackCastleKing) )  
    {
        Square sq_r = SQ_RIGHT(kingSq);
        Square sq_rr = SQ_RIGHT(sq_r);

        if ( (pos.GetPiece(sq_r)  == NO_PIECE) &&
             (pos.GetPiece(sq_rr) == NO_PIECE) &&
              !isSquareSet(pos.m_underAttack, sq_r) &&
              !isSquareSet(pos.m_underAttack, sq_rr) )
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
              !isSquareSet(pos.m_underAttack, sq_l) &&
              !isSquareSet(pos.m_underAttack, sq_l))
        {
            moves.push_back(Move(kingSq, QUEEN_SIDE));
        }
    }    

    return moves;    
}

Bitboard PawnAttacks(Square s, const Position& pos)
{
    Bitboard bb{0};
    auto AdvanceMove = (pos.m_sideToMove == WHITE) ? SQ_UP : SQ_DOWN;

    SetSquare(bb,AdvanceMove(SQ_LEFT(s)));
    SetSquare(bb,AdvanceMove(SQ_RIGHT(s)));

    return bb;
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

std::vector<Move> GenerateMoves(Square s, const Position& pos)
{
    std::vector<Move> moves;
    Piece p = pos.GetPiece(s);

    if (p == NO_PIECE)
        return moves;
    

    return moves;    
}
