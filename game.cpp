#include "game.h"
#include <mutex>
#include <chrono>
#include <utility>
#include <algorithm>

int Game::go()
{
    GetLogger() << "go\n";
    std::unique_lock<std::mutex> lock(m_lock);
    m_cv.wait_for(lock, std::chrono::milliseconds(1), [&](){ return m_thinking == false;});
    
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
    srand(static_cast<unsigned int>(time(0)));

    position(fen);
    m_startPosition = m_currentPosition;

    return 0;
}

std::string Game::bestmove()
{    
    std::vector<Move> moves = GetAllMoves(m_currentPosition.m_sideToMove);
    GetLogger() << "size = " << (int)moves.size() << std::endl;    
    int rn = getRandomNumber(0, moves.size()-1);
    Move m = moves[rn];

    m_currentPosition.ApplyMove(std::move(m));   
    m_currentPosition.SwitchSide();
    
    return m.to_string();
}

int Game::position(const std::string& fen)
{
    m_currentPosition.Set(fen);
    
    return 0;
}

Bitboard Game::GetAttacks(Position& pos, Color side)
{
    Bitboard attacks{0};
    for (Square sq = SQ_A1; sq != SQ_MAX; sq = static_cast<Square>(sq+1))
    {
        Piece p = pos.GetPiece(sq);
        PieceType type = GetPieceType(p);
        
        if (side == GetColor(p))
        {
            switch (type)
            {
            case PAWN:
                attacks |= PawnAttacks(sq, pos);
                break;
            case ROOK:
                attacks |= RookAttacks(sq, pos);
                break;
            case BISHOP:
                attacks |= BishopAttacks(sq, pos);
                break;
            case QUEEN:
                attacks |= QueenAttacks(sq, pos);
                break;
            case KNIGHT:
                attacks |= KnightAttacks(sq, pos);
                break;
            case KING:
                attacks |= KingAttacks(sq, pos);
                break;
            default:
                break;
            }
        }
    }

    return attacks;
}

std::vector<Move> Game::GetAllMoves(Color side)
{    
    std::vector<Move> m;
    std::vector<Move> moves;

    m_currentPosition.m_attacks = GetAttacks(m_currentPosition, side);
    m_currentPosition.m_underAttack = GetAttacks(m_currentPosition, SwitchColor(side));

    for (Square sq = SQ_A1; sq != SQ_MAX; sq = static_cast<Square>(sq+1))
    {
        Piece p = m_currentPosition.GetPiece(sq);
        PieceType type = GetPieceType(p);
        
        if (side == GetColor(p))
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

    m = CastleMoves(side, m_currentPosition);
    moves.insert(moves.end(), m.begin(), m.end());

    moves.erase(std::remove_if(
        moves.begin(),
        moves.end(),
        [&](Move& m){
                Position test = m_currentPosition;
                
                test.ApplyMove(Move(m));
                Square kingSq = test.FindKing(side);
                test.SwitchSide();

                Bitboard attacks = GetAttacks(test, SwitchColor(side));
                return isSquareSet(attacks, kingSq);                
        }),
        moves.end()
        );

    return moves;        
}
          
