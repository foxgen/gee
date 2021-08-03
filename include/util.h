#pragma once

#include <vector>
#include <string>
#include <condition_variable>
#include <mutex>
#include <atomic>
#include <iostream>
#include <fstream>
#include "types.h"

namespace gee
{

std::vector<std::string> 
split(const std::string& str, const std::string& delim);

std::ostream& GetLogger();

std::string SquareToString(const Square sq);
Square StringToSquare(const std::string& s);

bool isCharPiece(const char c);
Piece CharToPiece(const char c);
char PieceToChar(const Piece p);

int getRandomNumber(int min, int max);

} // gee