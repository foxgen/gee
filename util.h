#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "types.h"

std::vector<std::string> 
split(const std::string& str, const std::string& delim);

std::ostream& GetLogger();

std::string SquareToString(const Square sq);
Square StringToSquare(const std::string& s);