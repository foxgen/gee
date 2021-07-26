#pragma once

#include "types.h"
#include "position.h"
#include "move.h"
#include <vector>
#include <condition_variable>
#include <mutex>
#include <atomic>

class Game
{
public:
    Position m_startPosition;
    Position m_currentPosition;

    int m_threadCount;
    int m_searchDepth;
    int m_searchNodes;

    int m_searchMateIn;
    int m_moveTime; // msec

    int     go();
    int     stop();
    int     newgame(const std::string& fen);
    int     position(const std::string& fen);
    std::string bestmove();    
    int     uci();

public:
    // currect context

public:
    std::condition_variable m_cv;
    std::mutex m_lock;
    std::atomic<bool> m_thinking;
    std::vector<Move> m_gameMoves;
};