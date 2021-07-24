#pragma once
#include "types.h"
#include <string>
#include "util.h"
#include "bitboard.h"

class Move;

class Position
{
public:
    Position() = default; 

    std::string fen() const;
    void Set(const std::string& fen);
    Piece GetPiece(Square s) const;

    bool ApplyMove(Move&& move);

    void PutPiece(Piece pc, Square s);
    void ClearSquare(Square s);
    void RemovePiece(Piece pc, Square s);
    void MovePiece(Piece pc, Square from, Square to);
    void PrintBoard();
    void SwitchSide();
    Square FindKing(Color c);

    Piece m_board[SQ_MAX];
    Color m_sideToMove;

    // Possible castling
    bool  m_blackCastleKing;
    bool  m_blackCastleQueen;
    bool  m_whiteCastleKing;
    bool  m_whiteCastleQueen;

    Square m_passantSQ;

    int     m_halfMoveClock;
    int     m_fullMoveNumber;

    mutable Bitboard m_attacks{0};
    mutable Bitboard m_underAttack{0};
};


