#include <iostream>
#include <string.h>

using namespace std;

string inp;

void swap(char* a, char* b)
{
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

void A(int count)
{
	if (count >= inp.length())
		cout << inp << endl;
	else
	{
		for (int i = count; i < inp.length(); i++)
		{
			swap(&inp[count], &inp[i]);
			A(count + 1);
		}
		for (int i = inp.length() - 1; i >= count; i--)
		{
			swap(&inp[count], &inp[i]);
		}
	}
}

int main()
{
	cin >> inp;
	A(0);
	return 0;
}