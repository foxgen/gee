#include "game.h"

#include <gtest/gtest.h>

using namespace gee;

TEST(BBTest, testSet)
{
	Bitboard bb{0};
	BBSet(bb, SQ_E4);
	BBSet(bb, SQ_A4);
	BBSet(bb, SQ_B7);

	EXPECT_TRUE(BBisSet(bb, SQ_E4));
	EXPECT_TRUE(BBisSet(bb, SQ_A4));
	EXPECT_TRUE(BBisSet(bb, SQ_B7));

	BBClear(bb, SQ_A4);	
	EXPECT_FALSE(BBisSet(bb, SQ_A4));
}

TEST(FenTest, MovesPiecesTest)
{	
	Position p;

    p.Set("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
	EXPECT_EQ(p.fen(), "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");

	p.MovePiece(p.GetPiece(SQ_E2), SQ_E2, SQ_E4);
	EXPECT_EQ(p.fen(), "rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR w KQkq - 0 1");

	p.MovePiece(p.GetPiece(SQ_D2), SQ_D2, SQ_D4);
	EXPECT_EQ(p.fen(), "rnbqkbnr/pppppppp/8/8/3PP3/8/PPP2PPP/RNBQKBNR w KQkq - 0 1");

	p.MovePiece(p.GetPiece(SQ_G1), SQ_G1, SQ_F3);
	EXPECT_EQ(p.fen(), "rnbqkbnr/pppppppp/8/8/3PP3/5N2/PPP2PPP/RNBQKB1R w KQkq - 0 1");	

	p.MovePiece(p.GetPiece(SQ_F1), SQ_F1, SQ_C4);
	EXPECT_EQ(p.fen(), "rnbqkbnr/pppppppp/8/8/2BPP3/5N2/PPP2PPP/RNBQK2R w KQkq - 0 1");		
}

TEST(FenTest, MovesTest)
{	
	Position p;

    p.Set("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
	EXPECT_EQ(p.fen(), "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");

	p.ApplyMove(Move(SQ_E2, SQ_E4));
	EXPECT_EQ(p.fen(), "rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR w KQkq - 0 1");	

	p.ApplyMove(Move(SQ_D2, SQ_D4));
	EXPECT_EQ(p.fen(), "rnbqkbnr/pppppppp/8/8/3PP3/8/PPP2PPP/RNBQKBNR w KQkq - 0 1");

	p.ApplyMove(Move(SQ_G1, SQ_F3));
	EXPECT_EQ(p.fen(), "rnbqkbnr/pppppppp/8/8/3PP3/5N2/PPP2PPP/RNBQKB1R w KQkq - 0 1");		

	p.ApplyMove(Move(SQ_F1, SQ_C4));
	EXPECT_EQ(p.fen(), "rnbqkbnr/pppppppp/8/8/2BPP3/5N2/PPP2PPP/RNBQK2R w KQkq - 0 1");		

	p.ApplyMove(Move(SQ_E1, KING_SIDE));	
	EXPECT_EQ(p.fen(), "rnbqkbnr/pppppppp/8/8/2BPP3/5N2/PPP2PPP/RNBQ1RK1 w kq - 0 1");
}

TEST(FenTest, FenTest)
{	
	std::string fen1 = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
    std::string fen2 = "rnbqkbnr/pppppppp/8/8/P7/8/1PPPPPPP/RNBQKBNR b KQkq - 0 1";
    std::string fen3 = "r2qkb1r/ppp1pppp/2n2n2/3p1b2/P7/4PN2/1PPPBPPP/RNBQ1RK1 b kq - 4 5";
    std::string fen4 = "3r1rk1/1p3ppp/p7/4bN2/1n2P3/2P3P1/1P4BP/1K1RR3 w - - 2 25";

	Position p;

	p.Set(fen1);
	EXPECT_EQ(p.fen(), fen1);

	p.Set(fen2);
	EXPECT_EQ(p.fen(), fen2);

	p.Set(fen3);
	EXPECT_EQ(p.fen(), fen3);

	p.Set(fen4);
	EXPECT_EQ(p.fen(), fen4);
}

TEST(MovesTest, UpTests)
{
    EXPECT_EQ(SquareToString(SQ_UP(StringToSquare("a1"))), "a2");	
    EXPECT_EQ(SquareToString(SQ_UP(StringToSquare("b2"))), "b3");
    EXPECT_EQ(SquareToString(SQ_UP(StringToSquare("c3"))), "c4");
	EXPECT_EQ(SquareToString(SQ_UP(StringToSquare("d4"))), "d5");
	EXPECT_EQ(SquareToString(SQ_UP(StringToSquare("e5"))), "e6");
	EXPECT_EQ(SquareToString(SQ_UP(StringToSquare("f6"))), "f7");
	EXPECT_EQ(SquareToString(SQ_UP(StringToSquare("g7"))), "g8");
	EXPECT_EQ(SquareToString(SQ_UP(StringToSquare("h8"))), "--");
}

TEST(MovesTest, DownTests)
{
    EXPECT_EQ(SquareToString(SQ_DOWN(StringToSquare("a1"))), "--");	
    EXPECT_EQ(SquareToString(SQ_DOWN(StringToSquare("b2"))), "b1");
    EXPECT_EQ(SquareToString(SQ_DOWN(StringToSquare("c3"))), "c2");
	EXPECT_EQ(SquareToString(SQ_DOWN(StringToSquare("d4"))), "d3");
	EXPECT_EQ(SquareToString(SQ_DOWN(StringToSquare("e5"))), "e4");
	EXPECT_EQ(SquareToString(SQ_DOWN(StringToSquare("f6"))), "f5");
	EXPECT_EQ(SquareToString(SQ_DOWN(StringToSquare("g7"))), "g6");
	EXPECT_EQ(SquareToString(SQ_DOWN(StringToSquare("h8"))), "h7");
}

TEST(MovesTest, LeftTests)
{
    EXPECT_EQ(SquareToString(SQ_LEFT(StringToSquare("a1"))), "--");	
    EXPECT_EQ(SquareToString(SQ_LEFT(StringToSquare("b2"))), "a2");
    EXPECT_EQ(SquareToString(SQ_LEFT(StringToSquare("c3"))), "b3");
	EXPECT_EQ(SquareToString(SQ_LEFT(StringToSquare("d4"))), "c4");
	EXPECT_EQ(SquareToString(SQ_LEFT(StringToSquare("e5"))), "d5");
	EXPECT_EQ(SquareToString(SQ_LEFT(StringToSquare("f6"))), "e6");
	EXPECT_EQ(SquareToString(SQ_LEFT(StringToSquare("g7"))), "f7");
	EXPECT_EQ(SquareToString(SQ_LEFT(StringToSquare("h8"))), "g8");
}

TEST(MovesTest, RightTests)
{
    EXPECT_EQ(SquareToString(SQ_RIGHT(StringToSquare("a1"))), "b1");	
    EXPECT_EQ(SquareToString(SQ_RIGHT(StringToSquare("b2"))), "c2");
    EXPECT_EQ(SquareToString(SQ_RIGHT(StringToSquare("c3"))), "d3");
	EXPECT_EQ(SquareToString(SQ_RIGHT(StringToSquare("d4"))), "e4");
	EXPECT_EQ(SquareToString(SQ_RIGHT(StringToSquare("e5"))), "f5");
	EXPECT_EQ(SquareToString(SQ_RIGHT(StringToSquare("f6"))), "g6");
	EXPECT_EQ(SquareToString(SQ_RIGHT(StringToSquare("g7"))), "h7");
	EXPECT_EQ(SquareToString(SQ_RIGHT(StringToSquare("h8"))), "--");
}

TEST(RookMoves, testE2)
{
	Position pos;

	// Rook on E2
	pos.Set("8/8/8/8/8/8/4R3/8 w - - 0 1");
	
	std::vector<Move> moves = RookFigure().GetMoves(SQ_E2, pos);	
	std::vector<Square> m1, m2;	

	for (auto m:moves)
	{
		EXPECT_EQ(m.m_from, SQ_E2);
		EXPECT_EQ(m.m_type,	NORMAL);
		m1.push_back(m.m_to);
	}

	for (auto m : {"e1", "e3", "e4", "e5", "e6", "e7", "e8", 
					"a2", "b2", "c2", "d2", "f2", "g2", "h2"})	
		m2.push_back(StringToSquare(m));

	std::sort(m1.begin(), m1.end());
	std::sort(m2.begin(), m2.end());

	EXPECT_EQ(m1, m2);
}

TEST(BishopMoves, testE2)
{
	Position pos;

	// Bishop on E2
	pos.Set("8/8/8/8/8/8/4B3/8 w - - 0 1");

	std::vector<Move> moves = BishopFigure().GetMoves(SQ_E2, pos);
	std::vector<Square> m1, m2;	

	for (auto m:moves)
	{
		EXPECT_EQ(m.m_from, SQ_E2);
		EXPECT_EQ(m.m_type,	NORMAL);
		m1.push_back(m.m_to);
	}

	for (auto m : {"d1", "f1", "d3", "f3", "c4", "g4", "b5", "h5", "a6"})	
		m2.push_back(StringToSquare(m));

	std::sort(m1.begin(), m1.end());
	std::sort(m2.begin(), m2.end());

	EXPECT_EQ(m1, m2);
}

TEST(KnightMoves, testE2)
{
	Position pos;

	// Knight on E2
	pos.Set("8/8/8/8/8/8/4N3/8 w - - 0 1");

	std::vector<Move> moves = KnightFigure().GetMoves(SQ_E2, pos);
	std::vector<Square> m1, m2;	

	for (auto m:moves)
	{
		EXPECT_EQ(m.m_from, SQ_E2);
		EXPECT_EQ(m.m_type,	NORMAL);
		m1.push_back(m.m_to);
	}

	for (auto m : {"c1", "g1", "c3", "g3", "d4", "f4"})	
		m2.push_back(StringToSquare(m));

	std::sort(m1.begin(), m1.end());
	std::sort(m2.begin(), m2.end());

	EXPECT_EQ(m1, m2);
}

TEST(QueenMoves, testE2)
{
	Position pos;

	// Queen on E2
	pos.Set("8/8/8/8/8/8/4Q3/8 w - - 0 1");

	std::vector<Move> moves = QueenFigure().GetMoves(SQ_E2, pos);
	std::vector<Square> m1, m2;	

	for (auto m:moves)
	{
		EXPECT_EQ(m.m_from, SQ_E2);
		EXPECT_EQ(m.m_type,	NORMAL);
		m1.push_back(m.m_to);
	}

	for (auto m : {"e1", "e3", "e4", "e5", "e6", "e7", "e8", 
					"a2", "b2", "c2", "d2", "f2", "g2", "h2",
					"d1", "f1", "d3", "f3", "c4", "g4", "b5", "h5", "a6"})	
		m2.push_back(StringToSquare(m));

	std::sort(m1.begin(), m1.end());
	std::sort(m2.begin(), m2.end());

	EXPECT_EQ(m1, m2);
}

TEST(KingMoves, testE2)
{
	Position pos;

	// King on E2
	pos.Set("8/8/8/8/8/8/4K3/8 w - - 0 1");

	std::vector<Move> moves = KingFigure().GetMoves(SQ_E2, pos);
	std::vector<Square> m1, m2;	

	for (auto m:moves)
	{
		EXPECT_EQ(m.m_from, SQ_E2);
		EXPECT_EQ(m.m_type,	NORMAL);
		m1.push_back(m.m_to);
	}

	for (auto m : {"d1", "e1", "f1", "d2", "f2", "d3", "e3", "f3"})
		m2.push_back(StringToSquare(m));

	std::sort(m1.begin(), m1.end());
	std::sort(m2.begin(), m2.end());

	EXPECT_EQ(m1, m2);
}

TEST(KingMoves, IllegalMove_to_attacked)
{
	Game g;
	g.position("r3k3/8/8/8/2b5/8/8/4K2R w K - 0 1");
	
	std::vector<Move> moves = g.m_currentPosition.GetAllMoves();
	EXPECT_EQ(moves.size(), 12);
}

TEST(KingMoves, IllegalMoves_underAttack1)
{
	Game g;
	g.position("5k2/8/8/1b6/8/8/2N1K3/8 w - - 0 1");

	std::vector<Move> moves = g.m_currentPosition.GetAllMoves();
	EXPECT_EQ(moves.size(), 6);
}

TEST(KingMoves, IllegalMoves_underAttack2)
{
	Game g;
	g.position("r3k3/8/8/8/8/2b5/8/4K2R w K - 0 1");

	std::vector<Move> moves = g.m_currentPosition.GetAllMoves();
	EXPECT_EQ(moves.size(), 4);
}

TEST(PawnMoves, testE2)
{
	Position pos;

	// Pawn on E2
	pos.Set("8/8/8/8/8/8/4P3/8 w - - 0 1");

	std::vector<Move> moves = PawnFigure().GetMoves(SQ_E2, pos);	
	std::vector<Square> m1, m2;	

	for (auto m:moves)
	{
		EXPECT_EQ(m.m_from, SQ_E2);
		EXPECT_EQ(m.m_type,	NORMAL);
		m1.push_back(m.m_to);
	}

	for (auto m : {"e3", "e4"})	
		m2.push_back(StringToSquare(m));

	std::sort(m1.begin(), m1.end());
	std::sort(m2.begin(), m2.end());

	EXPECT_EQ(m1, m2);
}

TEST(AllMoves, test1)
{
	Game g;	
	
	g.position("rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR w KQkq - 0 1");

	std::vector<Move> moves = g.m_currentPosition.GetAllMoves();
	
	EXPECT_EQ(moves.size(), 30);
}

TEST(AllMoves, test2)
{
	Game g;	
	g.position("r3k2r/ppp1n1pp/2n2p2/4p3/P1Q2P1P/6q1/RB1Nb1B1/4K1NR w KQkq - 0 1");
	std::vector<Move> moves = g.m_currentPosition.GetAllMoves();
	EXPECT_EQ(moves.size(), 1);
}

TEST(AllMoves, test3)
{
	Game g;	
	g.position("7R/1p6/2PN2p1/p1PNk1N1/8/n7/PP4P1/4R1K1 b - - 0 1");
	std::vector<Move> moves = g.m_currentPosition.GetAllMoves();
	EXPECT_EQ(moves.size(), 2);
}

TEST(MovesConversion, MovesConversion)
{
	EXPECT_EQ(Move(NORMAL, SQ_E2, SQ_E4).to_string(), "e2e4");

	Position pos;
	pos.Set("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");

	Move m;
	m.from_string("e2e4", pos);
	EXPECT_TRUE(m == Move(NORMAL, SQ_E2, SQ_E4));	
	
	m.from_string("a7a8q", pos);
	EXPECT_TRUE(m == Move(PROMOTION, SQ_A7, SQ_A8, QUEEN));	
	m.from_string("a7a8r", pos);
	EXPECT_TRUE(m == Move(PROMOTION, SQ_A7, SQ_A8, ROOK));
	m.from_string("a7a8n", pos);
	EXPECT_TRUE(m == Move(PROMOTION, SQ_A7, SQ_A8, KNIGHT));
	m.from_string("a7a8b", pos);
	EXPECT_TRUE(m == Move(PROMOTION, SQ_A7, SQ_A8, BISHOP));

	EXPECT_EQ(Move(SQ_E1, KING_SIDE).to_string(),"e1g1");
	EXPECT_EQ(Move(SQ_E8, KING_SIDE).to_string(),"e8g8");
	EXPECT_EQ(Move(SQ_E1, QUEEN_SIDE).to_string(),"e1c1");
	EXPECT_EQ(Move(SQ_E8, QUEEN_SIDE).to_string(),"e8c8");
}	

TEST(PlayTheGame, test1)
{	
	Game game;
	game.position("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");

	std::string input = "h2h4 h7h6 c2c4 f7f5 e2e3 c7c5 f1d3 f5f4 d3e4 a7a6 d1c2 d7d6 e4f3 b7b5 b2b4 c8h3 b1a3 e7e6 d2d3 d8a5 f3e4 b5c4 c2e2 e8d8 e4h7 a8a7 h7g8 h3g4 g2g3 d8e7 e2d2 a5a3 h1h2 a3b3 h2h3 g4d1 a1b1 d1e2 d2e2 g7g5 g8e6 f4e3 b4b5 a7b7 e6c4 b8d7 f2f3 b7b6 b1b3 e7e8 e2d1 d7e5 d3d4 b6c6 d4d5 e8d7 g1e2 e5d3 e1f1 g5h4 d1c2 d7d8 c2d3 f8g7 f1e1 d8e7 d3c2 h8e8 a2a4 g7c3 b3c3 e8c8 b5c6 e7f6 c4d3";
	std::istringstream iss(input);

	while (!iss.eof())
	{
		std::string movestr;
		iss >> movestr;
		GetLogger() << movestr << std::endl;
		Move m;
		m.from_string(movestr, game.m_currentPosition);
		game.m_currentPosition.ApplyMove(std::move(m));
		game.m_currentPosition.SwitchSide();
	}

	std::vector<Move> moves = game.m_currentPosition.GetAllMoves();
}

TEST(PlayTheGame, test2)
{	
	Game game;
	game.position("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");

	std::string input = "b1a3 f7f5 b2b3 b8c6 f2f4 d7d5 c2c4 e8f7 a3b5 a8b8 e1f2 d8d7 b3b4 d7e8 a2a3 d5d4 c1b2 e7e6 d1c1 c6e7 e2e4 d4e3 f2e2 e3d2 c1d1";
	std::istringstream iss(input);

	while (!iss.eof())
	{
		std::string movestr;
		iss >> movestr;
		GetLogger() << movestr << std::endl;
		Move m;
		m.from_string(movestr, game.m_currentPosition);
		game.m_currentPosition.ApplyMove(m);
		game.m_currentPosition.SwitchSide();
	}

	std::vector<Move> moves = game.m_currentPosition.GetAllMoves();

	EXPECT_EQ(game.m_currentPosition.GetPiece(SQ_E4), NO_PIECE);
}