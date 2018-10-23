#ifndef _MAIN_CPP
#define _MAIN_CPP
#include <stdio.h>

#include <string>

const int DEPTH_OF_LOOK_AHEAD = 8;
const int N = 4;

#include "game.cpp"
#include "alphabeta.cpp"

using namespace std;

void header() 
{
	cout << N << "x" << N << " Tic Tac Toe"<<endl;
	cout << "---------------"<<endl;
	cout<<endl;
}

char menu() 
{
	char c;
	cout << "Options:"<<endl;
	cout << "\t[P]lay"<<endl;
	cout << "\t[A]bout"<<endl;
	cout << "\t[E]xit"<<endl;
	do 
	{
		cout << "Enter choice: ";
		cin >> c;
	} 
	while (c != 'p' && c != 'a' && c != 'e');
	return c;
}

void clearscreen() 
{
	system("clear");
}

void pausescreen() 
{
	int c = getchar();
}

void playComputer();

void about() 
{
	header();
	cout << "\tMade by Nguyễn Bá Dũng & Lê Anh Hòa" << endl;
	cout << "\tCopyright 2014 Jay Hitesh Bosamiya, Palash Agrawal\n";
}

int main() 
{
	clearscreen();
	header();
	char choice = menu();
	clearscreen();
	switch (choice)
	{
		case 'p':
			playComputer();
			break;
		case 'a':
			about();
			break;
		case 'e':
			header();
			cout << "Bye Bye!"<<endl;
	}
}

Board board;

Move prevMove;

int displayCount = 0;

void displayBoard() 
{
	clearscreen();
	header();
	cout << board.toString() << endl;
}

void displayResult() 
{
	int x = 0, o = 0;
	for (int i = 0; i < N; i++) 
	{
		x = max(x, board.countRow(i, board.X));
		x = max(x, board.countColumn(i, board.X));
		o = max(o, board.countRow(i, board.O));
		o = max(o, board.countColumn(i, board.O));
	}
	x = max(x, board.countDiag1(board.X));
	x = max(x, board.countDiag2(board.X));
	o = max(o, board.countDiag1(board.O));
	o = max(o, board.countDiag2(board.O));
	if (x == N) 
	{
		cout << "\tyou win"<<endl;
	}
	else if (o == N)
	{
		cout << "\tComputer played better... you fucking lose"<<endl;
	}
	else 
	{
		cout << "\tHòa cmnr :)"<<endl;
	}
}

void humanTurn() 
{
	int r, c; //hàng rồi cột
	Move move;
	do 
	{
		bool isMoveInRange;
		do 
		{
			cout << "Enter location to play: ";
			cin >> r >> c;
			isMoveInRange = move.set(r, c);
		} 
		while (!isMoveInRange);
	}
	while (!board.isLegal(move));
	board = board.doMove(move);
	prevMove = move;
}

void computerTurn() 
{
	Move move;
	if (displayCount == 2) 
	{
		move.set(3, 3);
	}
	else
	{
		alpha_beta(DEPTH_OF_LOOK_AHEAD, MAX, board, -INF, INF, move);
	}
	board = board.doMove(move);
	prevMove = move;
}

void playComputer() 
{
	displayBoard();
	char c;
	bool flag;
	do 
	{
		cout << "Do you want to start? [Y/N] ";
		cin >> c;
		clearscreen();
	} 
	while (c != 'y' && c != 'n');
	if (c == 'y') {
		flag = true;
		MAX = false; MIN = true;
	}
	else 
	{
		main();
	}
	while (!board.isGameOver() && !board.isDrawn()) 
	{
		displayBoard();
		if (flag) humanTurn();
		else computerTurn();
		flag = !flag;
	}
	displayBoard();
	displayResult();
}

#endif
