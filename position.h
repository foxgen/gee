#pragma once
#include "types.h"
#include <string>

class Move;

std::string SquareToString(const Square sq);
Square StringToSquare(const std::string& s);

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

    Piece m_board[SQ_MAX];
    Color m_sideToMove;

    bool  m_blackCastleKing;
    bool  m_blackCastleQueen;
    bool  m_whiteCastleKing;
    bool  m_whiteCastleQueen;

    Square m_passantSQ;

    int     m_halfMoveClock;
    int     m_fullMoveNumber;
};


