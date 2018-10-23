#ifndef _GAME_CPP
#define _GAME_CPP

#include <iostream>
#include <algorithm>
#include <vector>
#include <sstream>

using namespace std;

class Board;

class Move 
{
	friend class Board;
	int row, col;
public:
	Move() 
	{
		row = 0; col = 0;
	}
	bool set(int p, int q) 
		{
		if (p >= N || q >= N || p < 0 || q < 0) {
			return false;
		}
		else 
		{
			row = p;
			col = q;
			return true;
		}
	}

	string toString() const 
	{
		stringstream ss;
		ss << row << " " << col;
		return ss.str();
	}
};

class Board 
{
public:
	static const bool X = true;
	static const bool O = false;
	static const int EMPTY = -1;
private:
	int mark[N][N];
	int movesfinished;
	static char markToChar(int m) 
	{
		if (m == EMPTY) return ' ';
		if (m == X) return 'X';
		return 'O';
	}
public:
	Board() 
	{
		movesfinished = 0;
		for (int i = 0; i < N; i++) 
		{
			for (int j = 0; j < N; j++) 
			{
				mark[i][j] = EMPTY;
			}
		}
	}
	int countRow(int row, bool player) const 
	{
		int counter = 0;
		for (int j = 0; j < N; j++) 
		{
			if (mark[row][j] == player) 
			{
				counter++;
			}
		}
		return counter;
	}
	int countColumn(int column, bool player) const 
	{
		int counter = 0;
		for (int i = 0; i<N; i++) 
		{
			if (mark[i][column] == player) 
			{
				counter++;
			}
		}
		return counter;
	}
	int countDiag1(bool player) const
	{
		int counter = 0;
		for (int i = 0; i < N; i++) 
		{
			if (mark[i][i] == player) 
			{
				counter++;
			}
		}
		return counter;
	}
	int countDiag2(bool player) const 
	{
		int counter = 0;
		for (int i = 0; i < N; i++) 
		{
			if (mark[i][N - 1 - i] == player) 
			{
				counter++;
			}
		}
		return counter;
	}

	bool isGameOver() const 
	{
		int temp = 0;
		for (int i = 0; i < N; i++) 
		{
			temp = max(countRow(i, X), temp);
			temp = max(countRow(i, O), temp);
			temp = max(countColumn(i, X), temp);
			temp = max(countColumn(i, O), temp);
		}
		temp = max(temp, countDiag1(X));
		temp = max(temp, countDiag1(O));
		temp = max(temp, countDiag2(X));
		temp = max(temp, countDiag2(O));
		return ((temp == N) || (movesfinished == N*N));
	}

	bool isDrawn() const 
	{
		int temp = N;
		for (int i = 0; i < N; i++) 
		{
			temp = min(countRow(i, X), temp);
			temp = min(countRow(i, O), temp);
			temp = min(countColumn(i, X), temp);
			temp = min(countColumn(i, O), temp);
		}
		temp = min(temp, countDiag1(X));
		temp = min(temp, countDiag1(O));
		temp = min(temp, countDiag2(X));
		temp = min(temp, countDiag2(O));
		return ((temp != 0) || (movesfinished == N*N));
	}

	bool isLegal(const Move &move) const 
	{
		return (mark[move.row][move.col] == EMPTY);
	}

	Board doMove(const Move &move) const 
	{
		if (!isLegal(move)) return *this;
		Board temp;
		for (int i = 0; i < N; i++) 
		{
			for (int j = 0; j < N; j++) 
			{
				if (i == move.row && j == move.col) 
				{
					if (movesfinished % 2 == 0) 
					{
						temp.mark[i][j] = X;
					}
					else 
					{
						temp.mark[i][j] = O;
					}
					temp.movesfinished = movesfinished + 1;
				}
				else
				{
					temp.mark[i][j] = mark[i][j];
				}
			}
		}
		return temp;
	}

	vector<Move> legalMoves() const 
	{
		vector<Move> movesList;
		Move temp;
		for (int i = 0; i < N; i++) 
		{
			for (int j = 0; j < N; j++)
			{
				if (mark[i][j] == EMPTY) 
				{
					temp.row = i;
					temp.col = j;
					movesList.push_back(temp);
				}
			}
		}
		return movesList;
	}

	string toString() const 
	{
		stringstream ss;
		for (int i = 0; i < N; i++) 
		{
			for (int j = 0; j < N; j++) 
			{
				ss << markToChar(mark[i][j]);
				if (j != N - 1) ss << '|';
			}
			ss << endl;
			if (i != N - 1) 
			{
				for (int j = 0; j < N; j++) 
				{
					ss << '-';
					if (j != N - 1) ss << '+';
				}
			}
			ss << endl;
		}
		return ss.str();
	}
};

#endif
