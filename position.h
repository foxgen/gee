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

public:
    std::string fen() const;
    void Set(const std::string& fen);

public:
    Piece GetPiece(Square s) const;    
    void PutPiece(Piece pc, Square s);
    void ClearSquare(Square s);
    void RemovePiece(Piece pc, Square s);
    void MovePiece(Piece pc, Square from, Square to);
    bool ApplyMove(Move&& move);
    void SwitchSide();
    
    Square FindKing(Color c);
    std::vector<Move> GetAllMoves(Color side);

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


} // gee