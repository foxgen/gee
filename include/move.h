#pragma once
#include "types.h"
#include "position.h"
#include <iostream>
#include <vector>

namespace gee
{

class Move
{
public:
    Move() {};
    Move(Square from, Square to)
        : m_from(from), m_to(to) {};
    Move(MoveType t, Square from, Square to)
        : m_type(t), m_from(from), m_to(to) {};
    Move(MoveType t, Square from, Square to, PieceType pt)
        : m_type(t), m_from(from), m_to(to), m_newFigure(pt) {};        

    Move(Square from, CastlingSide side)
        : m_type(CASTLING), m_from(from), m_castlingSide(side) {};

    MoveType    m_type{NORMAL};
    Square      m_from{SQ_MAX};
    Square      m_to{SQ_MAX};

    PieceType   m_newFigure{NO_PIECE_TYPE};
    CastlingSide m_castlingSide{KING_SIDE};

    bool operator == (const Move& that)
    {
        return m_type == that.m_type &&
                m_from == that.m_from &&
                m_to == that.m_to &&
                m_newFigure == that.m_newFigure &&
                m_castlingSide == that.m_castlingSide;
    }

    std::string to_string();
    Move& from_string(const std::string& movestr, const Position& pos);

    int m_score;
};

static std::ostream& operator << (std::ostream& os, Move& move)
{
    os << MoveTypeStr(move.m_type) << "->" << move.to_string();

    return os;
}


//--------------------------------------------------------------------------------



} // gee