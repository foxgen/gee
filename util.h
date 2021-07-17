#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <fstream>

std::vector<std::string> 
split(const std::string& str, const std::string& delim);

std::ostream& GetLogger();