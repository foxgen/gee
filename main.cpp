#include <string>
#include <iostream>
#include <sstream>
#include "position.h"
#include "move.h"

#include <vector>
#include <string>

class Game
{
public:

    Position m_position;
};


int main(int argc, char *argv[])
{   

    while (true)
    {
        std::string input;
        std::getline(std::cin, input);

        std::istringstream iss(input);

        std::string cmd;
        iss >> cmd;

        //__asm int 3

        if (cmd == "uci")
        {
            std::cout << "id name genchess" << std::endl;
            std::cout << "id author Evgeny Roschin" << std::endl;

            std::cout << "uciok" << std::endl;
        }

        if (cmd == "debug")
        {
        }

        if (cmd == "isready")
        {
            std::cout << "readyok" << std::endl;
        }

        if (cmd == "register")
        {
            iss >> cmd;
            // __asm int 3
        }

        if (cmd == "ucinewgame")
        {
            iss >> cmd;
            //__asm int 3
        }

        if (cmd == "position")
        {
            //__asm int 3
            Position p;



        }

        if (cmd == "go")
        {
        }

        if (cmd == "stop")
        {
        }

        if (cmd == "ponderhit")
        {
        }

        if (cmd == "quit")
        {
        }
    }

    return 0;
}
