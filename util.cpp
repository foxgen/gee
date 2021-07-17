#include "util.h"
#include <stdexcept>

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
    static std::ofstream ofs("./example.txt");   
    return ofs.is_open() ? ofs : std::cout;

    //return std::cout;
}