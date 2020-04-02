#define N 5

#include <iostream>

using namespace std;

int d[N];

void Write()
{
	int i;
	for(i=0;i<N;i++)
		cout<<d[i]<<' ';
	cout<<endl;
}

void f(int k)
{
	int i,temp;
	if(k==N-1)
		Write();
	else
		for(i=0;i<N;i++)
		{
			temp=d[k];
			d[k]=d[i];
			d[i]=temp;
			f(k+1);
			temp=d[k];
			d[k]=d[i];
			d[i]=temp;
		}
}

int main(int argc, char *argv[])
{
	int i;
	//__init__
	for(i=0;i<N;i++)
		d[i]=i;
	f(0);
	return 0;
}
