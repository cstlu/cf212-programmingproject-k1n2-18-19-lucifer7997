#ifndef _alphabeta_cpp
#define _alphabeta_cpp

#include <iostream>
#include <algorithm>
#include <vector>
#include <sstream>

#include "game.cpp"

using namespace std;

const int WINNER = 1 << 30;
const int LOSER = -WINNER;
const int INF = 100000000;

bool MAX = false;
bool MIN = true;

const int SCORER[] = { 1,10,100,1000,10000,100000 };

int scoreIt(int x, int o) 
{
	int score = 0;
	if (o == 0) score += SCORER[x];
	if (x == 0) score -= SCORER[o];
	return score;
}

int getScore(const Board &board) 
{
	int score = 0;
	for (int i = 0; i < N; i++) 
	{
		score += scoreIt(board.countRow(i, MAX), board.countRow(i, MIN));
		score += scoreIt(board.countColumn(i, MAX), board.countColumn(i, MIN));
	}
	score += scoreIt(board.countDiag1(MAX), board.countDiag1(MIN));
	score += scoreIt(board.countDiag2(MAX), board.countDiag2(MIN));
	return score;
}

Board tempBoard;

bool movesorter(Move a, Move b) 
{
	int scoreA = getScore(tempBoard.doMove(a));
	int scoreB = getScore(tempBoard.doMove(b));
	if (scoreA < 0) scoreA = -scoreA;
	if (scoreB < 0) scoreB = -scoreB;
	return (scoreA < scoreB);
}

void permutator(vector<Move>::iterator l, vector<Move>::iterator r)
{
	vector<Move> positive, negative, zero;
	for (vector<Move>::iterator it = l; it != r; it++) 
	{
		int score = getScore(tempBoard.doMove(*it));
		if (score < 0) negative.push_back(*it);
		else if (score == 0) zero.push_back(*it);
		else positive.push_back(*it);
	}
	random_shuffle(zero.begin(), zero.end());
	sort(positive.begin(), positive.end(), movesorter);
	sort(negative.begin(), negative.end(), movesorter);

	vector<Move>::iterator i = l;

	while (!positive.empty() || !zero.empty() || !negative.empty())
	{
		if (!positive.empty()) 
		{
			*(i++) = *(positive.rbegin());
			positive.pop_back();
		}
		if (!zero.empty()) 
		{
			*(i++) = *(zero.rbegin());
			zero.pop_back();
		}
		if (!negative.empty()) 
		{
			*(i++) = *(negative.rbegin());
			negative.pop_back();
		}
	}
}

int alpha_beta(const int level, const bool player, const Board &board, int alpha, int beta, Move &move)
{
	if (board.isGameOver() || level == 0)
	{
		if (!board.isGameOver()) move = (board.legalMoves())[0];
		return (getScore(board));
	}

	vector<Move> children = board.legalMoves();

	tempBoard = board;
	permutator(children.begin(), children.end());

	if (player == MAX) 
	{
		for (vector<Move>::iterator it = children.begin(); it != children.end(); it++) 
		{
			Board child = board.doMove(*it);
			Move temp;
			int score = alpha_beta(level - 1, !player, child, alpha, beta, temp);
			if (score > alpha) 
			{
				alpha = score; // We have found a better best move
				move = *it;
			}
			if (alpha >= beta) 
			{
				move = *it;
				return alpha; // Beta Cut Off
			}
		}
		return alpha; // This is our best move
	}
	else 
	{
		for (vector<Move>::iterator it = children.begin(); it != children.end(); it++)
		{
			Board child = board.doMove(*it);
			Move temp;
			int score = alpha_beta(level - 1, !player, child, alpha, beta, temp);
			if (score < beta)
			{
				beta = score; // Opponent has found a better worse move
				move = *it;
			}
			if (alpha >= beta) 
			{
				move = *it;
				return beta; // Alpha Cut Off
			}
		}
		return beta; // This is the opponent's best move
	}
}

#endif
