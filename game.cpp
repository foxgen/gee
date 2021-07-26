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
    std::vector<Move> moves = GetAllMoves(m_currentPosition);
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

