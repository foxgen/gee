#pragma once
#include "types.h"
#include "position.h"
#include <iostream>
#include <vector>

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
    void from_string(const std::string& movestr, const Position& pos);

    int m_score;
};

static std::ostream& operator << (std::ostream& os, Move& move)
{
    os << MoveTypeStr(move.m_type) << "->" << move.to_string();

    return os;
}

Bitboard RookAttacks(Square s, const Position& pos);
Bitboard BishopAttacks(Square s, const Position& pos);
Bitboard QueenAttacks(Square s, const Position& pos);
Bitboard KnightAttacks(Square s, const Position& pos);
Bitboard KingAttacks(Square s, const Position& pos);
Bitboard PawnAttacks(Square s, const Position& pos);

std::vector<Move> RookMoves(Square s, const Position& pos);
std::vector<Move> BishopMoves(Square s, const Position& pos);
std::vector<Move> QueenMoves(Square s, const Position& pos);
std::vector<Move> KnightMoves(Square s, const Position& pos);
std::vector<Move> KingMoves(Square s, const Position& pos);
std::vector<Move> CastleMoves(Color side, const Position& pos);
std::vector<Move> PawnMoves(Square s, const Position& pos);

/*
class Figure
{
public:    
    virtual Bitboard GetAttacks();
    virtual std::vector<Move> GetMoves(Square s, const Position& Pos);
}
*/

    std::vector<Move> GetAllMoves(Position& pos, Color side);
    std::vector<Move> GetAllMoves(Position& pos);
    Bitboard GetAttacks(Position& pos, Color side);
    Bitboard GetAttacks(Position& pos);