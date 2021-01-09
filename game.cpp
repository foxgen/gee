#include "game.h"

std::vector<Move> Game::GetAllMoves()
{
    std::vector<Move> moves;
    std::vector<Move> m;

    for (Square sq = SQ_A1; sq != SQ_MAX; sq = static_cast<Square>(sq+1))
    {
        Piece p = m_currentPosition.GetPiece(sq);
        PieceType type = GetPieceType(p);
        
        if (m_currentPosition.m_sideToMove == GetColor(p))
        {
            switch (type)
            {
            case PAWN:
                m = PawnMoves(sq, m_currentPosition);
                break;
            case ROOK:
                m = RookMoves(sq, m_currentPosition);
                break;
            case BISHOP:
                m = BishopMoves(sq, m_currentPosition);
                break;
            case QUEEN:
                m = QueenMoves(sq, m_currentPosition);
                break;
            case KNIGHT:
                m = KnightMoves(sq, m_currentPosition);
                break;
            case KING:
                m = KingMoves(sq, m_currentPosition);
                break;
            default:
                break;
            }

            moves.insert(moves.end(), m.begin(), m.end());
        }
    }

    return moves;
}