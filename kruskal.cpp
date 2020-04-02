#define M 100
#define N 100
#include <fstream>
using namespace std;

ifstream fin("data.txt");
ofstream fout("kruscal.txt");

struct ARC
{
	int i, j, d;
};
ARC arc[N];
int m, n;
int set[M];

int getroot(int i)
{
	while(set[i]!=-1)
		i=set[i];
	return i;
}

int main(int argc, char *argv[])
{
	int i, j;
	ARC temp;
	fin>>m>>n;
	for(i=0; i<n; i++)
		fin>>arc[i].i>>arc[i].j>>arc[i].d;
	for(i=0; i<n-1; i++)
		for(j=i+1; j<n; j++)
			if(arc[i].d>arc[j].d)
			{
				temp=arc[i];
				arc[i]=arc[j];
				arc[j]=temp;
			}
	for(i=0; i<M; i++)
		set[i]=-1;
	for(i=0; i<n; i++)
		if(getroot(arc[i].i)!=getroot(arc[i].j))
		{
			fout<<arc[i].i<<"->"<<arc[i].j<<endl;
			set[getroot(arc[i].i)]=arc[i].j;
		}
	return 0;
}
