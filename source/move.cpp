#include "move.h"
#include "figure.h"
#include "bishop.h"
#include "rook.h"
#include "knight.h"
#include "pawn.h"
#include "queen.h"
#include "king.h"

namespace gee
{

std::array<std::unique_ptr<Figure>, 6> fig = {
    std::make_unique<PawnFigure>(),
    std::make_unique<KnightFigure>(),
    std::make_unique<BishopFigure>(),
    std::make_unique<RookFigure>(),
    std::make_unique<QueenFigure>(),
    std::make_unique<KingFigure>()
};


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



Bitboard GetAttacks(Position& pos, Color side)
{
    Bitboard attacks{0};
    for (Square sq = SQ_A1; sq != SQ_MAX; sq = static_cast<Square>(sq+1))
    {
        Piece p = pos.GetPiece(sq);
        PieceType type = GetPieceType(p);
        
        if (side == GetColor(p))
            attacks |= fig[type-1]->GetAttacks(sq, pos);
    }

    return attacks;
}

Bitboard GetAttacks(Position& pos)
{
    return GetAttacks(pos, pos.m_sideToMove);
}

std::vector<Move> GetAllMoves(Position& pos, Color side)
{    
    std::vector<Move> m;
    std::vector<Move> moves;
    
    pos.m_attacks = GetAttacks(pos, side);
    pos.m_underAttack = GetAttacks(pos, SwitchColor(side));

    for (Square sq = SQ_A1; sq != SQ_MAX; sq = static_cast<Square>(sq+1))
    {
        Piece p = pos.GetPiece(sq);
        PieceType type = GetPieceType(p);
        

        if (side == GetColor(p))
        {
            m = fig[type-1]->GetMoves(sq, pos);
            
            moves.insert(moves.end(), m.begin(), m.end());
        }
    }

    moves.erase(std::remove_if(
        moves.begin(),
        moves.end(),
        [&](Move& m){
                Position testPos = pos;
                
                testPos.ApplyMove(Move(m));
                Square kingSq = testPos.FindKing(side);
                testPos.SwitchSide();

                Bitboard attacks = GetAttacks(testPos, SwitchColor(side));
                return BBisSet(attacks, kingSq);                
        }),
        moves.end()
        );

    return moves;        
}

std::vector<Move> GetAllMoves(Position& pos)
{
    return GetAllMoves(pos, pos.m_sideToMove);
}
//------------------------------------------------------------------------------------



} // gee