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

Move& Move::from_string(const std::string &movestr, const Position& pos)
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

    return *this;
}

} // gee