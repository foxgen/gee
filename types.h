#pragma once
#include <cstdint>

enum Color {
    NO_COLOR, WHITE, BLACK
};

inline Color SwitchColor(Color c)
{
  if (c==WHITE) return BLACK;
  else if (c==BLACK) return WHITE;
  return c;    
};

enum CastlingSide {
  KING_SIDE, QUEEN_SIDE
};

enum PieceType {
  NO_PIECE_TYPE, PAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING
};

enum MoveType {
  NORMAL,
  PROMOTION = 1 << 14,
  ENPASSANT = 2 << 14,
  CASTLING  = 3 << 14
};

enum Square {
  SQ_A1=0, SQ_B1, SQ_C1, SQ_D1, SQ_E1, SQ_F1, SQ_G1, SQ_H1,
  SQ_A2, SQ_B2, SQ_C2, SQ_D2, SQ_E2, SQ_F2, SQ_G2, SQ_H2,
  SQ_A3, SQ_B3, SQ_C3, SQ_D3, SQ_E3, SQ_F3, SQ_G3, SQ_H3,
  SQ_A4, SQ_B4, SQ_C4, SQ_D4, SQ_E4, SQ_F4, SQ_G4, SQ_H4,
  SQ_A5, SQ_B5, SQ_C5, SQ_D5, SQ_E5, SQ_F5, SQ_G5, SQ_H5,
  SQ_A6, SQ_B6, SQ_C6, SQ_D6, SQ_E6, SQ_F6, SQ_G6, SQ_H6,
  SQ_A7, SQ_B7, SQ_C7, SQ_D7, SQ_E7, SQ_F7, SQ_G7, SQ_H7,
  SQ_A8, SQ_B8, SQ_C8, SQ_D8, SQ_E8, SQ_F8, SQ_G8, SQ_H8,

  SQ_MAX
};

static inline int GetX(Square s) {
  return s % 8;
};

static inline int GetY(Square s) {
  return s / 8;
};

// #define SQ_UP(s)    ( (s != SQ_MAX) && (s < SQ_A8) ? static_cast<Square>(s + 8) : SQ_MAX )
static inline Square SQ_UP(Square s) { 
  return ( (s != SQ_MAX) && (s < SQ_A8) ? static_cast<Square>(s + 8) : SQ_MAX );
};

static inline Square SQ_DOWN(Square s)  {
  return ( (s != SQ_MAX) && (s > SQ_H1) ? static_cast<Square>(s - 8) : SQ_MAX );
};
static inline Square SQ_LEFT(Square s)  {
  return ( (s != SQ_MAX) && (s % SQ_A2) ? static_cast<Square>(s - 1) : SQ_MAX );
};

static inline Square SQ_RIGHT(Square s)  {
  return ( (s != SQ_MAX) && ((s+1) % 8) ? static_cast<Square>(s + 1) : SQ_MAX );
};

enum Piece {
  NO_PIECE,
  W_PAWN = 1, W_KNIGHT, W_BISHOP, W_ROOK, W_QUEEN, W_KING,
  B_PAWN = 9, B_KNIGHT, B_BISHOP, B_ROOK, B_QUEEN, B_KING,
  PIECE_NB = 16
};

static inline PieceType GetPieceType(Piece p)
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

typedef uint64_t Bitboard;
inline void SetUnderAttack(Bitboard& bb, Square sq)
{
  bb |= (1 << sq);      
}