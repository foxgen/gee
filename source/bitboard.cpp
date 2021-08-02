#include "bitboard.h"

namespace gee
{

void BBSet(Bitboard& bb, Square sq)
{
    if (sq != SQ_MAX)
      bb |= ((Bitboard)1 << sq);      
}

void BBClear(Bitboard& bb, Square sq)
{
    if (sq != SQ_MAX)
      bb &= ~((Bitboard)1 << sq);      
}

bool BBisSet(Bitboard bb, Square sq)
{
  if (sq != SQ_MAX)
      return (bb & ((Bitboard)1<<sq));
  return false;
}


std::vector<Square> BBGetSquares(Bitboard bb)
{
    std::vector<Square> squares;
    for (Square sq = SQ_A1; sq != SQ_MAX; sq = static_cast<Square>(sq+1))
    {
        if (BBisSet(bb, sq))
            squares.push_back(sq);
    }
    return squares;
}

Bitboard BBGetFromSquares(std::vector<Square> squares)
{
    Bitboard bb{0};
    for (auto sq : squares)
        BBSet(bb, sq);
    return bb;
}

void BBPrint(Bitboard bb)
{
  std::cout << std::hex << bb << std::endl;
  for (Square sq = SQ_A1; sq != SQ_MAX; sq = static_cast<Square>(sq+1))
  {
      std::cout << BBisSet(bb, sq);
      if (GetX(sq) == 7)
         std::cout << std::endl;
  }
  std::cout << std::endl;
}

} // gee