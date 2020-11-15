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

int fenTest()
{
    std::string fen1 = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
    std::string fen2 = "rnbqkbnr/pppppppp/8/8/P7/8/1PPPPPPP/RNBQKBNR b KQkq - 0 1";
    std::string fen3 = "r2qkb1r/ppp1pppp/2n2n2/3p1b2/P7/4PN2/1PPPBPPP/RNBQ1RK1 b kq - 4 5";
    std::string fen4 = "3r1rk1/1p3ppp/p7/4bN2/1n2P3/2P3P1/1P4BP/1K1RR3 w - - 2 25";

    std::string f = fen4;

    Position p;

    p.Set(f);

    printf("%s\n",p.fen().c_str());

    if (p.fen() != f)
    {
        //__asm int 3
    }

    return 0;
}

int TestMoves()
{
    std::cout << "UP tests" << std::endl;

    std::cout << SquareToString(SQ_UP(StringToSquare("a1"))) << std::endl;
    std::cout << SquareToString(SQ_UP(StringToSquare("b2"))) << std::endl;
    std::cout << SquareToString(SQ_UP(StringToSquare("c3"))) << std::endl;
    std::cout << SquareToString(SQ_UP(StringToSquare("d4"))) << std::endl;
    std::cout << SquareToString(SQ_UP(StringToSquare("e5"))) << std::endl;
    std::cout << SquareToString(SQ_UP(StringToSquare("f6"))) << std::endl;
    std::cout << SquareToString(SQ_UP(StringToSquare("g7"))) << std::endl;
    std::cout << SquareToString(SQ_UP(StringToSquare("h8"))) << std::endl;

    std::cout << "DOWN tests" << std::endl;

    std::cout << SquareToString(SQ_DOWN(StringToSquare("a1"))) << std::endl;
    std::cout << SquareToString(SQ_DOWN(StringToSquare("b2"))) << std::endl;
    std::cout << SquareToString(SQ_DOWN(StringToSquare("c3"))) << std::endl;
    std::cout << SquareToString(SQ_DOWN(StringToSquare("d4"))) << std::endl;
    std::cout << SquareToString(SQ_DOWN(StringToSquare("e5"))) << std::endl;
    std::cout << SquareToString(SQ_DOWN(StringToSquare("f6"))) << std::endl;
    std::cout << SquareToString(SQ_DOWN(StringToSquare("g7"))) << std::endl;
    std::cout << SquareToString(SQ_DOWN(StringToSquare("h8"))) << std::endl;

    std::cout << "LEFT tests" << std::endl;

    std::cout << SquareToString(SQ_LEFT(StringToSquare("a1"))) << std::endl;
    std::cout << SquareToString(SQ_LEFT(StringToSquare("b2"))) << std::endl;
    std::cout << SquareToString(SQ_LEFT(StringToSquare("c3"))) << std::endl;
    std::cout << SquareToString(SQ_LEFT(StringToSquare("d4"))) << std::endl;
    std::cout << SquareToString(SQ_LEFT(StringToSquare("e5"))) << std::endl;
    std::cout << SquareToString(SQ_LEFT(StringToSquare("f6"))) << std::endl;
    std::cout << SquareToString(SQ_LEFT(StringToSquare("g7"))) << std::endl;
    std::cout << SquareToString(SQ_LEFT(StringToSquare("h8"))) << std::endl;

    std::cout << "RIGHT tests" << std::endl;

    std::cout << SquareToString(SQ_RIGHT(StringToSquare("a1"))) << std::endl;
    std::cout << SquareToString(SQ_RIGHT(StringToSquare("b2"))) << std::endl;
    std::cout << SquareToString(SQ_RIGHT(StringToSquare("c3"))) << std::endl;
    std::cout << SquareToString(SQ_RIGHT(StringToSquare("d4"))) << std::endl;
    std::cout << SquareToString(SQ_RIGHT(StringToSquare("e5"))) << std::endl;
    std::cout << SquareToString(SQ_RIGHT(StringToSquare("f6"))) << std::endl;
    std::cout << SquareToString(SQ_RIGHT(StringToSquare("g7"))) << std::endl;
    std::cout << SquareToString(SQ_RIGHT(StringToSquare("h8"))) << std::endl;



    return 0;
}

int TestRook(const Position& pos, const std::string& square)
{    
    std::vector<Move> moves = RookMoves(StringToSquare(square), pos);

    for ( auto m : moves)
        std::cout << SquareToString(m.m_to) << " ";
    std::cout << std::endl;

    return 0;
}

int TestBishop(const Position& pos, const std::string& square)
{
    std::vector<Move> moves = BishopMoves(StringToSquare(square), pos);

    for ( auto m : moves)
        std::cout << SquareToString(m.m_to) << " ";
    std::cout << std::endl;

    return 0;
}

int TestKnight(const Position& pos, const std::string& square)
{
    std::vector<Move> moves = KnightMoves(StringToSquare(square), pos);

    for ( auto m : moves)
        std::cout << m << std::endl;
    std::cout << std::endl;

    return 0;
}

int TestQueen(const Position& pos, const std::string& square)
{
    std::vector<Move> moves = QueenMoves(StringToSquare(square), pos);

    for ( auto m : moves)
        std::cout << SquareToString(m.m_to) << " ";
    std::cout << std::endl;

    return 0;
}

int TestKing(const Position& pos, const std::string& square)
{
    std::vector<Move> moves = KingMoves(StringToSquare(square), pos);

    for ( auto m : moves)
        std::cout << m << std::endl;
    std::cout << std::endl;

    return 0;
}

int TestPawn(const Position& pos, const std::string& square)
{
    Square sq = StringToSquare(square);
    Piece p = pos.GetPiece(sq);

    std::vector<Move> moves = PawnMoves(sq, pos);

    for ( auto m : moves)
        std::cout << m << std::endl;
    std::cout << std::endl;

    return 0;
}

int main(int argc, char *argv[])
{
    //return TestMoves();
    Position pos;
    pos.Set("r1b1k2r/P4pbp/1p1qpnp1/2n5/2QP4/2N1PP1N/2PB2PP/R3K2R b Qk - 0 17");
    return TestKing(pos, "e8");

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
