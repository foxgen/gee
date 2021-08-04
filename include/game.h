#pragma once

#include "types.h"
#include "position.h"
#include "move.h"
#include "bishop.h"
#include "rook.h"
#include "knight.h"
#include "pawn.h"
#include "queen.h"
#include "king.h"

namespace gee
{

class Game
{
public:    

    int     go();
    int     stop();
    int     newgame(const std::string& fen);
    int     position(const std::string& fen);
    std::string bestmove();    
    int     uci();

public:

    int m_threadCount;
    int m_searchDepth;
    int m_searchNodes;

    int m_searchMateIn;
    int m_moveTime; // msec
    std::condition_variable m_cv;
    std::mutex m_lock;
    std::atomic<bool> m_thinking;

    std::unique_ptr<Position> m_startPosition;
    std::unique_ptr<Position> m_currentPosition;
    std::vector<Move> m_gameMoves;
};

} // gee