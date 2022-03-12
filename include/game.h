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
#include "node.h"

namespace gee
{

class Game
{
public:    

// UCI command handlers
    int     go();
    int     stop();    
    int     position(const std::string& cmd);    
    int     uci();
    int     isready();
    int     ucinewgame();
    int     register_(const std::string& cmd); // register is a reserved token

// Additional
    int     newgame(const std::string& fen);
    std::string bestmove();    
    std::unique_ptr<Position> m_startPosition;
    std::shared_ptr<Position> m_currentPosition;

private:

    int m_threadCount;
    int m_searchDepth;
    int m_searchNodes;
    int m_searchMateIn;    
    int m_moveTime; // msec
    
    std::condition_variable m_cv;
    std::mutex m_lock;
    std::atomic<bool> m_thinking;    

    void UCIReply(const std::string& answer);
};

} // gee