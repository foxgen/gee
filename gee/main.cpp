#include "game.h"
#include <map>

using namespace gee;

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

        if (cmd == "uci")        
            game.uci();       

        if (cmd == "isready")
            game.isready();        

        if (cmd == "register")
            game.register_(input);

        if (cmd == "ucinewgame")
            game.ucinewgame();        

        if (cmd == "position")
            game.position(input);

        if (cmd == "go")        
            game.go();

        if (cmd == "stop")        
            game.stop();        

        if (cmd == "quit")
        {
            std::exit(1);
        }
    }

    return 0;
}
