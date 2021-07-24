#include "bitboard.h"
#include <iostream>

void SetSquare(Bitboard& bb, Square sq)
{
    if (sq != SQ_MAX)
      bb |= ((Bitboard)1 << sq);      
}

void ClearSquare(Bitboard& bb, Square sq)
{
    if (sq != SQ_MAX)
      bb &= ~((Bitboard)1 << sq);      
}

bool isSquareSet(Bitboard& bb, Square sq)
{
  if (sq != SQ_MAX)
      return (bb & ((Bitboard)1<<sq));
  return false;
}


std::vector<Square> GetSquaresFromBB(Bitboard& bb)
{
    std::vector<Square> squares;
    for (Square sq = SQ_A1; sq != SQ_MAX; sq = static_cast<Square>(sq+1))
    {
        if (isSquareSet(bb, sq))
            squares.push_back(sq);
    }
    return squares;
}

Bitboard GetBBFromSquares(std::vector<Square> squares)
{
    Bitboard bb{0};
    for (auto sq : squares)
        SetSquare(bb, sq);
    return bb;
}

void PrintBB(Bitboard bb)
{
  std::cout << std::hex << bb << std::endl;
  for (Square sq = SQ_A1; sq != SQ_MAX; sq = static_cast<Square>(sq+1))
  {
      std::cout << isSquareSet(bb, sq);
      if (GetX(sq) == 7)
         std::cout << std::endl;
  }
  std::cout << std::endl;
}