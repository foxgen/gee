#include "game.h"

namespace gee
{

void Game::UCIReply(const std::string& answer)
{
    std::cout << answer << std::endl;
    GetLogger() << "<-" << answer << std::endl;
}

int Game::uci()
{
    UCIReply("id name genchess");
    UCIReply("id author Evgeny Roschin");
    UCIReply("uciok");

    return 0;
}

int Game::isready()
{
    UCIReply("readyok");

    return 0;
}

int Game::ucinewgame()
{
    newgame("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");

    return 0;
}

int Game::register_(const std::string& input)
{
    std::istringstream iss(input);
    std::string cmd;
    iss >> cmd; // <- register

    iss >> cmd;
    GetLogger() << "register: " << cmd << std::endl;

    return 0;
}

int Game::go()
{
    GetLogger() << "go\n";
    std::unique_lock<std::mutex> lock(m_lock);
    m_cv.wait_for(lock, std::chrono::milliseconds(1), [&](){ return m_thinking == false;});

    UCIReply(std::string("bestmove ") + bestmove());
    
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

    m_currentPosition = std::make_unique<Position>(fen);    
    m_startPosition   = std::make_unique<Position>(*m_currentPosition);

    return 0;
}

std::string Game::bestmove()
{    
    std::vector<Move> moves = m_currentPosition->GetAllMoves();
    GetLogger() << "size = " << (int)moves.size() << std::endl;    
    int rn = getRandomNumber(0, moves.size()-1);
    Move m = moves[rn];

    m_currentPosition->ApplyMove(std::move(m));   
    m_currentPosition->SwitchSide();
    
    return m.to_string();
}

int Game::position(const std::string& input)
{
    std::istringstream iss(input);

    std::string cmd;
    iss >> cmd;

    // position startpos moves e2e4 e7e5 g1f3
    // position 
    std::string cmd1;
    std::string fen;

    iss >> cmd1;

    if (cmd1 == "startpos")
        fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
        
    if (cmd1 == "fen")
    {
        iss >> fen;                                
    }
    
    m_currentPosition->Set(fen);

    // todo add moves
    iss >> cmd;
    GetLogger() << cmd << std::endl;
    GetLogger() << "fen = " << fen << std::endl;

    while (!iss.eof())
    {
        std::string movestr;
        iss >> movestr;
        GetLogger() << movestr << std::endl;

        Move m;
        m.from_string(movestr, *m_currentPosition);

        m_currentPosition->ApplyMove(m);
        m_currentPosition->SwitchSide();
    }
    
    GetLogger() << m_currentPosition->fen() << std::endl;    
    
    return 0;
}

} // gee