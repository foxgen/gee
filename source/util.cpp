#include "util.h"

namespace gee
{

int getRandomNumber(int min, int max)
{
    static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0); 
    // Равномерно распределяем рандомное число в нашем диапазоне
    return static_cast<int>(rand() * fraction * (max - min + 1) + min);
}

std::vector<std::string> 
split(const std::string& str, const std::string& delim){
    std::vector<std::string> result;
    if (str.empty())
        throw std::runtime_error("Can not tokenize an empty string!");
    std::string::const_iterator begin, str_it;
    begin = str_it = str.begin(); 
    do {
        while (str_it != str.end() && delim.find(*str_it) == std::string::npos)
            str_it++; // find the position of the first delimiter in str

        std::string token = std::string(begin, str_it); // grab the token

        if (!token.empty()) // empty token only when str starts with a delimiter
            result.push_back(token); // push the token into a vector<string>

        while (str_it != str.end() && delim.find(*str_it) != std::string::npos)
            str_it++; // ignore the additional consecutive delimiters

        begin = str_it; // process the remaining tokens
    } while (str_it != str.end());

    return result;
}


std::ostream&
GetLogger()
{
    static std::ofstream ofs("./log.txt");   
    return ofs.is_open() ? ofs : std::cout;

    //return std::cout;
}


Square StringToSquare(const std::string& s)
{
    int r = s[1] - '1';
    int pos = toupper(s[0]) - 'A';

    return (Square)(r * 8 + pos);
}

std::string SquareToString(const Square sq)
{
    if (sq == SQ_MAX)
        return "--";

    int r, pos;
    char s[3];

    r = sq / 8;
    pos = sq % 8;

    s[0] = 'a' + pos;
    s[1] = '1' + r;
    s[2] = 0;

    return  s;
}

bool isCharPiece(const char c)
{
    const std::string figures = "rnbqkRNBQKpP";
    return std::string::npos != figures.find(c);
}

Piece CharToPiece(const char c)
{
    Piece p = NO_PIECE;
    switch (c)
    {
    case 'r': p = B_ROOK; break;
    case 'n': p = B_KNIGHT; break;
    case 'b': p = B_BISHOP; break;
    case 'k': p = B_KING; break;
    case 'q': p = B_QUEEN; break;
    case 'p': p = B_PAWN; break;
    case 'R': p = W_ROOK; break;
    case 'N': p = W_KNIGHT; break;
    case 'B': p = W_BISHOP; break;
    case 'K': p = W_KING; break;
    case 'Q': p = W_QUEEN; break;
    case 'P': p = W_PAWN; break;
    default:
        break;
    }

    return p;
}

char PieceToChar(const Piece p)
{
    char c = ' ';
    switch (p)
    {
    case B_ROOK: c = 'r'; break;
    case B_KNIGHT: c = 'n'; break;
    case B_BISHOP: c = 'b'; break;
    case B_KING: c = 'k'; break;
    case B_QUEEN: c = 'q'; break;
    case B_PAWN: c = 'p'; break;
    case W_ROOK: c = 'R'; break;
    case W_KNIGHT: c = 'N'; break;
    case W_BISHOP: c = 'B'; break;
    case W_KING: c = 'K'; break;
    case W_QUEEN: c = 'Q'; break;
    case W_PAWN: c = 'P'; break;

        //case NO_PIECE: break;
    default:        
        break;
    }

    return c;
}

} // gee