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
    Square      m_from;
    Square      m_to;

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
    void from_string(const std::string& movestr);

    int m_score;
};

static std::ostream& operator << (std::ostream& os, const Move& move)
{
    std::string moveType = move.m_type == NORMAL ? "NORMAL" : 
                            move.m_type == PROMOTION ? "PROMOTION" :
                            move.m_type == ENPASSANT ? "ENPASSANT" :
                            move.m_type == CASTLING ? "CASTLE" : "unknown";
    os << "(";
    if (move.m_type == CASTLING )
    {
        os << ((move.m_castlingSide == QUEEN_SIDE) ? "0-0-0" : "0-0");
    }
    else
    {
        os << SquareToString(move.m_from) << " " << moveType << " " << SquareToString(move.m_to);        
    }

    os << ")";
    
    if ( move.m_type == PROMOTION )
        os << " " << move.m_newFigure;        

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
std::vector<Move> KingCastleMoves(Square s, const Position& pos);
std::vector<Move> PawnMoves(Square s, const Position& pos);