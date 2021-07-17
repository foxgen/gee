#include <string>
#include <iostream>
#include <sstream>
#include "position.h"
#include "move.h"
#include "game.h"
#include "util.h"

void UCIReply(const std::string& answer)
{
    std::cout << answer << std::endl;
    GetLogger() << "<-" << answer << std::endl;
}


int main(int argc, char *argv[])
{
    Game game;    

    GetLogger() << "This is main\n";

    while (true)
    {
        std::string input;
        std::getline(std::cin, input);

        GetLogger() << "->" << input << std::endl;

        std::istringstream iss(input);

        std::string cmd;
        iss >> cmd;
        GetLogger() << "cmd = " << cmd << std::endl;
        
        //__asm int 3    

        if (cmd == "uci")
        {
            UCIReply("id name genchess");
            UCIReply("id author Evgeny Roschin");
            UCIReply("uciok");
        }

        if (cmd == "debug")
        {
        }

        if (cmd == "isready")
        {
            UCIReply("readyok");
        }

        if (cmd == "register")
        {
            iss >> cmd;
            // __asm int 3
        }

        if (cmd == "ucinewgame")
        {
            iss >> cmd;
            game.newgame("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
        }

        if (cmd == "position")
        {
            // position startpos moves e2e4 e7e5 g1f3
            // position 
            //__asm int 3
            std::string cmd1;
            iss >> cmd1;

            std::string fen;

            if (cmd1 == "startpos")
                fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
                
            if (cmd1 == "fen")
            {
                iss >> fen;                                
            }
            // todo add moves
            iss >> cmd;
            GetLogger() << cmd << std::endl;

            GetLogger() << "fen = " << fen << std::endl;
            game.position(fen);

            while (!iss.eof())
            {
                std::string movestr;
                iss >> movestr;
                GetLogger() << movestr << std::endl;
                Move m;
                m.from_string(movestr);
                game.m_currentPosition.ApplyMove(std::move(m));
                game.m_currentPosition.m_sideToMove = SwitchColor(game.m_currentPosition.m_sideToMove);
            }                        
            
            GetLogger() << game.m_currentPosition.fen() << std::endl;
        }

        if (cmd == "go")
        {
            game.go();

            UCIReply(std::string("bestmove ") + game.bestmove());
        }

        if (cmd == "stop")
        {
            game.stop();
        }

        if (cmd == "ponderhit")
        {
        }

        if (cmd == "quit")
        {
            std::exit(1);
        }
    }

    return 0;
}
