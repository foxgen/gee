#include "game.h"
#include <mutex>
#include <chrono>
#include <utility>

int getRandomNumber(int min, int max)
{
    static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0); 
    // Равномерно распределяем рандомное число в нашем диапазоне
    return static_cast<int>(rand() * fraction * (max - min + 1) + min);
}

int Game::go()
{
    GetLogger() << "go\n";
    std::unique_lock<std::mutex> lock(m_lock);
    m_cv.wait_for(lock, std::chrono::seconds(1), [&](){ return m_thinking == false;});
    
    return 0;
}

int Game::stop()
{
    GetLogger() << "stop\n";
    m_thinking = true;
    m_cv.notify_one();

    return 0;
}

int Game::newgame(const std::string& fen)
{
    m_startPosition.Set(fen);
    m_currentPosition = m_startPosition;

    return 0;
}

std::string Game::bestmove()
{
    std::vector<Move> moves = GetAllMoves(m_underAttack);
    int rn = getRandomNumber(0, moves.size()); 
    Move m = moves[rn];

    m_currentPosition.ApplyMove(std::move(m));
    m_currentPosition.m_sideToMove = SwitchColor(m_currentPosition.m_sideToMove);
    
    return m.to_string();
}

int Game::position(const std::string& fen)
{
    m_currentPosition.Set(fen);
    
    return 0;
}

std::vector<Move> Game::GetAllMoves(Bitboard& underAttack)
{
    std::vector<Move> moves;
    std::vector<Move> m;
    underAttack = 0;

    for (Square sq = SQ_A1; sq != SQ_MAX; sq = static_cast<Square>(sq+1))
    {
        Piece p = m_currentPosition.GetPiece(sq);
        PieceType type = GetPieceType(p);
        
        if (m_currentPosition.m_sideToMove == GetColor(p))
        {
            switch (type)
            {
            case PAWN:
                m = PawnMoves(sq, m_currentPosition, underAttack);
                break;
            case ROOK:
                m = RookMoves(sq, m_currentPosition, underAttack);
                break;
            case BISHOP:
                m = BishopMoves(sq, m_currentPosition, underAttack);
                break;
            case QUEEN:
                m = QueenMoves(sq, m_currentPosition, underAttack);
                break;
            case KNIGHT:
                m = KnightMoves(sq, m_currentPosition, underAttack);
                break;
            case KING:
                m = KingMoves(sq, m_currentPosition, underAttack);
                break;
            default:
                break;
            }

            moves.insert(moves.end(), m.begin(), m.end());
        }
    }

    GetLogger() << "Got " << moves.size() << " moves\n";

    return moves;
}