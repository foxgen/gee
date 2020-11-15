#pragma once

#include "types.h"
#include "position.h"
#include "move.h"
#include <vector>

std::vector<Move> GetMoves(const Position& position)
{
    return std::vector<Move>();
}

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
    int     position(const std::string& fen);
    int     uci();
};