/*
input:
	list[0], list[1]
yueshu:
	alldif(list[0~7])
	alldif(list[i] - i)
	alldif(list[i] + i)
output
	list
*/
#define SIZE 8
#define INIT -1
#define INF 100000
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class ASSIGNMENT {
public:
	ASSIGNMENT()
	{
		for (int i = 0; i < SIZE; i++)
			list[i] = INIT;
		for (int i = 0; i < SIZE; i++)
			for (int j = 0; j < SIZE; j++)
				D[i][j] = 1;
	}
	ASSIGNMENT(bool fail)/*only for the initation for "fail"*/
	{
		if (fail == 0)
		{
			for (int i = 0; i < SIZE; i++)
				for (int j = 0; j < SIZE; j++)
					D[i][j] = 0;
		}
	}
	int list[SIZE];
	int size()
	{
		int s = 0;
		for (int i = 0; i < SIZE; i++)
			if (list[i] != INIT)
				s++;
		return s;
	}
	bool D[SIZE][SIZE];
	int Dsize(int x)
	{
		if (x >= SIZE)cerr << "var out of range!\n";
		int _sum = 0;
		for (int i = 0; i < SIZE; i++)
			_sum += int(D[x][i]);
		return _sum;
	}
	int Dsize(int x) const
	{
		if (x >= SIZE)cerr << "var out of range!\n";
		int _sum = 0;
		for (int i = 0; i < SIZE; i++)
			_sum += int(D[x][i]);
		return _sum;
	}
	bool failure()
	{
		for (int i = 0; i < SIZE; i++)
			if (Dsize(i) == 0)
				return true;
		return false;
	}
	bool failure() const
	{
		for (int i = 0; i < SIZE; i++)
			if (Dsize(i) == 0)
				return true;
		return false;
	}
	void print()
	{
		for (int i = 0; i < SIZE; i++)
		{
			cout << list[i] + 1 << ' ';
		}
	}
};

const ASSIGNMENT fail = { 0 };

int SELECT_UNASSIGNED_VARIABLE(const ASSIGNMENT& ass)/*using MRV*/
{
	int minimum, _minimum = INF;
	for (int i = 0; i < SIZE; i++)
	{
		if (ass.list[i] == INIT)
			if (ass.Dsize(i) < _minimum)
			{
				_minimum = ass.Dsize(i);
				minimum = i;
			}
	}
	return minimum;
}

vector<int> ORDER_DOMAIN_VALUES(int var, const ASSIGNMENT& ass)/*not using anything, can be improved by LCV*/
{
	vector<int> result;
	for (int i = 0; i < SIZE; i++)
		if (ass.D[var][i])
		{
			result.push_back(i);
		}
	return result;
}

bool IFCONSISTANT(int var, int val, const ASSIGNMENT& ass)
{
	return ass.D[var][val];
}

ASSIGNMENT INFERENCE(const ASSIGNMENT& ass)
{
	ASSIGNMENT result = ass;
	for (int i = 0; i < SIZE; i++)
	{
		if (result.list[i] != INIT)
		{
			for (int j = 0; j < SIZE; j++)
			{
				if (j != i)
				{
					result.D[j][result.list[i]] = 0;
					if (result.list[i] - i + j >= 0 &&
						result.list[i] - i + j < SIZE)
						result.D[j][result.list[i] - i + j] = 0;
					if (result.list[i] + i - j >= 0 &&
						result.list[i] + i - j < SIZE)
						result.D[j][result.list[i] + i - j] = 0;
				}
			}
		}
	}
	return result;
}

ASSIGNMENT BACKTRACK(ASSIGNMENT& assignment)
{
	if (assignment.size() == SIZE)
		return assignment;
	int var = SELECT_UNASSIGNED_VARIABLE(assignment);
	for (int value : ORDER_DOMAIN_VALUES(var, assignment))
	{
		if (IFCONSISTANT(var, value, assignment))
		{
			assignment.list[var] = value;
			ASSIGNMENT inference = INFERENCE(assignment);
			if (!inference.failure())
			{
				ASSIGNMENT result = BACKTRACK(inference);
				if (!result.failure())
					return result;
			}
		}
		assignment.list[var] = INIT;
	}
	return fail;
}

int main()
{
	ASSIGNMENT X;
	cin >> X.list[0] >> X.list[1];
	X.list[0] --;
	X.list[1] --;
	X = BACKTRACK(X);
	X.print();
}
