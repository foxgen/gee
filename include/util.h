#pragma once

#include <vector>
#include <string>
#include <condition_variable>
#include <mutex>
#include <atomic>
#include <iostream>
#include <fstream>
#include <chrono>
#include <utility>
#include <algorithm>
#include <stdexcept>
#include <sstream>

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

inline Color SwitchColor(Color c)
{
    switch(c)
    {
        case WHITE: return BLACK;
        case BLACK: return WHITE;
        default: break;
    }
    return c;  
};

inline const char* MoveTypeStr(MoveType mt)
{
  switch(mt)
  {
    case NORMAL : return "NORMAL";
    case PROMOTION : return "PROMOTION";
    case ENPASSANT : return "ENPASSANT";
    case CASTLING : return "CASTLING";    
  }
  return "----";
}

inline int GetX(Square s) {
  return s % 8;
}

inline int GetY(Square s) {
  return s / 8;
}

// #define SQ_UP(s)    ( (s != SQ_MAX) && (s < SQ_A8) ? static_cast<Square>(s + 8) : SQ_MAX )
inline Square SQ_UP(Square s) { 
  return ( (s != SQ_MAX) && (s < SQ_A8) ? static_cast<Square>(s + 8) : SQ_MAX );
}

inline Square SQ_DOWN(Square s)  {
  return ( (s != SQ_MAX) && (s > SQ_H1) ? static_cast<Square>(s - 8) : SQ_MAX );
};

inline Square SQ_LEFT(Square s)  {
  return ( (s != SQ_MAX) && (s % SQ_A2) ? static_cast<Square>(s - 1) : SQ_MAX );
}

inline Square SQ_RIGHT(Square s)  {
  return ( (s != SQ_MAX) && ((s+1) % 8) ? static_cast<Square>(s + 1) : SQ_MAX );
}

inline PieceType GetPieceType(Piece p)
{
  return static_cast<PieceType>(p & ~8);
}

inline Piece MakePiece(PieceType t, Color c)
{
  int applyCol = (c == BLACK) ? 8 : 0;
  return static_cast<Piece>(t | applyCol);
}

inline Color GetColor(Piece p)
{
    if ((p >= W_PAWN) && (p <= W_KING))
      return WHITE;
    if ((p >= B_PAWN) && (p <= B_KING))
      return BLACK; 

    return NO_COLOR;  
}

} // gee