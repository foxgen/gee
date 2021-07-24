#include "position.h"
#include "move.h"
#include <vector>
#include <stdexcept>
#include <iostream>
#include <sstream>

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



void Position::PrintBoard()
{
    for (int r = 0; r < 8; r++)
    {
        for (int pos = 8; pos; pos--)
        {
            Square sq = (Square)(r * 8 + (pos - 1));

            printf("%c", PieceToChar(m_board[sq]));
        }
        printf("\n");
    }
}

// rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1
void Position::Set(const std::string& fen)
{   
    const std::string figures = "rnbqkRNBQKpP";

    std::vector<std::string> tokens = split(fen, " ");
    std::vector<std::string> raws = split(tokens[0], "/");

    // side to move
    GetLogger() << "side to move " << tokens[1].c_str() << std::endl;
    if (tokens[1] == "w")
        m_sideToMove = WHITE;
    else if( tokens[1] == "b" )
        m_sideToMove = BLACK;
    else 
    {
        GetLogger() << "fen error\n";
        return;
    }
    // Castling    
    m_whiteCastleKing = (std::string::npos != tokens[2].find('K'));        
    m_whiteCastleQueen = (std::string::npos != tokens[2].find('Q'));     
    m_blackCastleKing = (std::string::npos != tokens[2].find('k'));        
    m_blackCastleQueen = (std::string::npos != tokens[2].find('q'));

    // en passant
    m_passantSQ = (tokens[3] == "-") ? SQ_MAX : StringToSquare(tokens[3]);

    // halfMoveClock
    m_halfMoveClock = atoi(tokens[4].c_str());

    // fullMoveNumber
    m_fullMoveNumber = atoi(tokens[5].c_str());

    GetLogger() << "board " << tokens[0].c_str() << std::endl;
    // board
    int vertical = 0;
    int horizontal = 0;

    for (int r = 0; r < 8 ; r++ )
    {
        const std::string& rawStr = raws[7-r];
        int pos = 0;

        for (const char c : rawStr)
        {
            Piece p = NO_PIECE;
            Square s = Square(r * 8 + pos);
            
            int skipCount = 0;

            if (isCharPiece(c))
            {
                p = CharToPiece(c);

                m_board[s] = p;

                pos++;
            }
            else
            {
                skipCount = (c - '0');

                while (skipCount--)
                {
                    m_board[s + skipCount] = p;
                    pos++;
                }
            }
        }
    }
}

std::string Position::fen() const
{
    std::vector<std::string> tokens;    

    std::string board = "";
    std::string sideToMove = (m_sideToMove == WHITE) ? "w" :
                             (m_sideToMove == BLACK) ? "b" : "";

    std::string castling = "";
    if (m_whiteCastleKing)
        castling += "K";
    if (m_whiteCastleQueen)
        castling += "Q";
    if (m_blackCastleKing)
        castling += "k";
    if (m_blackCastleQueen)
        castling += "q";

    if (!m_whiteCastleKing && !m_whiteCastleQueen && !m_blackCastleKing && !m_blackCastleQueen)
        castling = "-";

    std::string passantSQ = "-";
    if (m_passantSQ != SQ_MAX)
        passantSQ = SquareToString(m_passantSQ);

    // board
    for (int r=8; r; r--)
    {
        for (int pos=0; pos<8; pos++)
        {
            Square s = Square((r-1)*8 + pos);

            int skipCount = 0;

            char c = PieceToChar(m_board[s]);

            if (c != ' ')
                board += c;
            else
            {
                char tempBuffer[20];
                skipCount++;
                while (pos + 1 < 8 && PieceToChar(m_board[s + skipCount]) == ' ')
                {
                    skipCount++;                    
                    pos++;
                }
                board += _itoa(skipCount, tempBuffer, 10);
            }
        }

        if (r > 1)
            board += "/";
    }

    return board + " " + 
           sideToMove + " " +
           castling + " " + 
           passantSQ + " " +
           std::to_string(m_halfMoveClock) + " " +
           std::to_string(m_fullMoveNumber);
}

void Position::PutPiece(Piece pc, Square s)
{
    m_board[s] = pc;
}

void Position::RemovePiece(Piece pc, Square s)
{
    m_board[s] = NO_PIECE;
}

void Position::MovePiece(Piece pc, Square from, Square to)
{
    RemovePiece(pc, from);
    PutPiece(pc, to);
}

Piece Position::GetPiece(Square s) const 
{
    return m_board[s];
}

void Position::ClearSquare(Square s) 
{
    m_board[s] = NO_PIECE;
}

void Position::SwitchSide()
{
    m_sideToMove = SwitchColor(m_sideToMove);
    std::swap(m_attacks, m_underAttack);
}

Square Position::FindKing(Color c)
{
    for (int s = Square::SQ_A1; s != Square::SQ_MAX; s++)
    {
        Piece p = m_board[s];
        PieceType pt = GetPieceType(p);
        Color pc = GetColor(p);
        if (pt == KING && pc == c)
        return static_cast<Square>(s);
    }

    return SQ_MAX;
}

bool Position::ApplyMove(Move&& move)
{
    Piece p = m_board[move.m_from];
    Color c = GetColor(p);

    if (p==B_KING)
        m_blackCastleKing = m_blackCastleQueen = false;
    if (p==W_KING)
        m_whiteCastleKing = m_whiteCastleQueen = false;    
    if (move.m_from == SQ_A1)
        m_whiteCastleQueen = false;
    if (move.m_from == SQ_H1)
        m_whiteCastleKing = false;
    if (move.m_from == SQ_A8)
        m_blackCastleQueen = false;
    if (move.m_from == SQ_H8)
        m_blackCastleKing = false;

    switch(move.m_type)
    {
        case NORMAL:
        {            
            MovePiece(p, move.m_from, move.m_to);

            return true;
        }            
        case PROMOTION:
        {
            ClearSquare(move.m_from);
            PutPiece(MakePiece(move.m_newFigure,c), move.m_to);

            return true;
        }
        case ENPASSANT:
        {
            MovePiece(p, move.m_from, move.m_to);
            auto RetreatMove = (GetColor(p) == WHITE) ? SQ_DOWN : SQ_UP;
            ClearSquare(RetreatMove(move.m_to));
            return true;
        }
        case CASTLING:
        {
            Piece rook = (GetColor(p) == WHITE) ? W_ROOK : B_ROOK;
            Square srcRookSq, dstRookSq, dstKingSq;

            if (move.m_castlingSide == KING_SIDE)
            {
                srcRookSq = (GetColor(p) == WHITE) ? SQ_H1 : SQ_H8;
                dstRookSq = (GetColor(p) == WHITE) ? SQ_F1 : SQ_F8;
                dstKingSq = (GetColor(p) == WHITE) ? SQ_G1 : SQ_G8;                
            }
            else // if (move.m_castlingSide == QUEEN_SIDE)
            {                
                srcRookSq = (GetColor(p) == WHITE) ? SQ_A1 : SQ_A8;
                dstRookSq = (GetColor(p) == WHITE) ? SQ_D1 : SQ_D8;
                dstKingSq = (GetColor(p) == WHITE) ? SQ_C1 : SQ_C8;                
            }

            if (GetColor(p) == WHITE)
                m_whiteCastleKing = m_whiteCastleQueen = false;
            else
                m_blackCastleKing = m_blackCastleQueen = false;

            MovePiece(p, move.m_from, dstKingSq);
            MovePiece(rook, srcRookSq, dstRookSq);            
            
            return true;
        }
    }

    return false;
}