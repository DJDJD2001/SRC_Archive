/*
Coded by DJDJD2001
	2020.3.22
Using MiniMax search with alphabeta

Original Question:
√Ë ˆ
4x4 tic-tac-toe is played on a board with four rows (numbered 0 to 3 from top to bottom) and four columns (numbered 0 to 3 from left to right). There are two players, x and o, who move alternately with x always going first. The game is won by the first player to get four of his or her pieces on the same row, column, or diagonal. If the board is full and neither player has won then the game is a draw.
Assuming that it is x's turn to move, x is said to have a forced win if x can make a move such that no matter what moves o makes for the rest of the game, x can win. This does not necessarily mean that x will win on the very next move, although that is a possibility. It means that x has a winning strategy that will guarantee an eventual victory regardless of what o does.

Your job is to write a program that, given a partially-completed game with x to move next, will determine whether x has a forced win. You can assume that each player has made at least two moves, that the game has not already been won by either player, and that the board is not full.
 ‰»Î
The input contains one or more test cases, followed by a line beginning with a dollar sign that signals the end of the file. Each test case begins with a line containing a question mark and is followed by four lines representing the board; formatting is exactly as shown in the example. The characters used in a board description are the period (representing an empty space), lowercase x, and lowercase o. For each test case, output a line containing the (row, column) position of the first forced win for x, or '#####' if there is no forced win. Format the output exactly as shown in the example.
 ‰≥ˆ
For this problem, the first forced win is determined by board position, not the number of moves required for victory. Search for a forced win by examining positions (0, 0), (0, 1), (0, 2), (0, 3), (1, 0), (1, 1), ..., (3, 2), (3, 3), in that order, and output the first forced win you find. In the second test case below, note that x could win immediately by playing at (0, 3) or (2, 0), but playing at (0, 1) will still ensure victory (although it unnecessarily delays it), and position (0, 1) comes first.
*/
#define DEBUG 0
#define DEBUG_WAIT 1
#define DEBUG_TERMINAL_MARK 0

#define P pair<int, int>
#define x first
#define y second
#define SIZE 4
#define INF 10000000
#include <iostream>
#include <vector>

using namespace std;

char map[SIZE][SIZE];

ostream& operator<<(ostream& os, const P p)
{
	return os << '(' << p.x << ',' << p.y << ')';
}

void debug_printmap()
{
	if (DEBUG_WAIT)
		cin.get();
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
			cerr << map[i][j];
		cerr << endl;
	}
}

vector<P> ACTIONS()
{
	vector<P> result;
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			if (map[i][j] == '.')
				result.push_back({ i, j });
		}
	}
	return result;
}

int UTILITY();

bool TERMINAL_TEST()
{
	if (ACTIONS().size() == 0)
		return true;
	if (UTILITY() != 0)
		return true;
	return false;
}

int UTILITY()
{
	for (int i = 0; i < SIZE; i++)
	{
		char __tempc = map[i][0];
		if (__tempc == '.')continue;
		bool __tempb = true;
		for (int j = 1; j < SIZE; j++)
		{
			if (map[i][j] != __tempc)
			{
				__tempb = false;
				break;
			}
		}
		if (__tempb)
		{
			if (__tempc == 'x')
				return 1;
			else if (__tempc == 'o')
				return -1;
			else
			{
				cerr << "Wrong Map!\n";
				return 0;
			}
		}
	}
	for (int i = 0; i < SIZE; i++)
	{
		char __tempc = map[0][i];
		if (__tempc == '.')continue;
		bool __tempb = true;
		for (int j = 1; j < SIZE; j++)
		{
			if (map[j][i] != __tempc)
			{
				__tempb = false;
				break;
			}
		}
		if (__tempb)
		{
			if (__tempc == 'x')
				return 1;
			else if (__tempc == 'o')
				return -1;
			else
			{
				cerr << "Wrong Map!\n";
				return 0;
			}
		}
	}
	{
		char _tempc = map[0][0];
		bool _tempb = true;
		if (_tempc != '.')
		{
			for (int i = 1; i < SIZE; i++)
			{
				if (map[i][i] != _tempc)
				{
					_tempb = false;
					break;
				}
			}
			if (_tempb)
			{
				if (_tempc == 'x')
					return 1;
				else if (_tempc == 'o')
					return -1;
				else
				{
					cerr << "Wrong Map!\n";
					return 0;
				}
			}
		}
	}
	{
		char _tempc = map[0][SIZE - 1];
		bool _tempb = true;
		if (_tempc != '.')
		{
			for (int i = 1; i < SIZE; i++)
			{
				if (map[i][SIZE - 1 - i] != _tempc)
				{
					_tempb = false;
					break;
				}
			}
			if (_tempb)
			{
				if (_tempc == 'x')
					return 1;
				else if (_tempc == 'o')
					return -1;
				else
				{
					cerr << "Wrong Map!\n";
					return 0;
				}
			}
		}
	}
	return 0;
}

int MAX_VALUE(int, int);
int MIN_VALUE(int, int);

int MAX_VALUE(int alpha, int beta)
{
	if (DEBUG)
		debug_printmap();
	if (TERMINAL_TEST())
	{
		if (DEBUG && DEBUG_TERMINAL_MARK)
			cerr << "ended!\n";
		return UTILITY();
	}
	int val = -INF;
	for (P i : ACTIONS())
	{
		map[i.x][i.y] = 'x';
		int temp = MIN_VALUE(alpha, beta);
		map[i.x][i.y] = '.';
		val = val > temp ? val : temp;
		if (val >= beta)
			return val;
		alpha = alpha > val ? alpha : val;
	}
	return val;
}

int MIN_VALUE(int alpha, int beta)
{
	if (DEBUG)
		debug_printmap();
	if (TERMINAL_TEST())
	{
		if (DEBUG && DEBUG_TERMINAL_MARK)
			cerr << "ended!\n";
		return UTILITY();
	}
	int val = INF;
	for (P i : ACTIONS())
	{
		map[i.x][i.y] = 'o';
		int temp = MAX_VALUE(alpha, beta);
		map[i.x][i.y] = '.';
		val = val < temp ? val : temp;
		if (val <= alpha)
			return val;
		beta = beta < val ? beta : val;
	}
	return val;
}

int ALPHA_BETA_SEARCH()
{
	return MIN_VALUE(-INF, INF);
}

int main()
{
	char temp;
	while (1)
	{
		temp = cin.get();
		if (temp == '?')
		{
			for (int i = 0; i < SIZE; i++)
			{
				temp = cin.get();//'\n'
				for (int j = 0; j < SIZE; j++)
				{
					map[i][j] = cin.get();
				}
			}
			temp = cin.get();//'\n'

			if (ACTIONS().size() >= SIZE * SIZE - 4)
			{
				cout << "#####\n";
				continue;
			}

			bool tempb = true;
			for (P i : ACTIONS())
			{
				map[i.x][i.y] = 'x';
				int Result = ALPHA_BETA_SEARCH();
				map[i.x][i.y] = '.';
				if (Result == 1)
				{
					tempb = false;
					cout << i << endl;
					break;
				}
			}
			if (tempb)
				cout << "#####\n";
		}
		else if (temp == '$')
			break;
		else
		{
			cerr << "Bad Token!\n";
		}
	}
	return 0;
}