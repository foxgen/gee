#pragma once
#include "types.h"
#include "util.h"
#include "bitboard.h"

namespace gee
{

class Move;

class Position
{
public:
    Position() = default; 
    Position(const std::string& fen);

public:
    std::string fen() const;
    Position& Set(const std::string& fen);

public:
    Piece GetPiece(Square s) const;    
    void PutPiece(Piece pc, Square s);
    void ClearSquare(Square s);
    void RemovePiece(Piece pc, Square s);
    void MovePiece(Piece pc, Square from, Square to);
    bool ApplyMove(const Move& move);
    void SwitchSide();

public:    
    Square FindKing(Color c);
    std::vector<Move> GetAllMoves(Color side);
    std::vector<Move> GetAllMoves();
    Bitboard GetAttacks(Color side);    
    Bitboard GetAttacks();


public:
    Piece m_board[SQ_MAX];
    Color m_sideToMove;
    Square m_passantSQ;

    // Possible castling
    bool  m_blackCastleKing;
    bool  m_blackCastleQueen;
    bool  m_whiteCastleKing;
    bool  m_whiteCastleQueen;

    int     m_halfMoveClock;
    int     m_fullMoveNumber;

    Bitboard m_attacks{0};
    Bitboard m_underAttack{0};
};


class PositionFactory
{
public:
    PositionFactory() = default;

    std::unique_ptr<Position> GreatePosition();
};

} // gee