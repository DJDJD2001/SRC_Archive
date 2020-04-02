#define M 100
#define INF 0x7fffffff

#include <fstream>
using namespace std;

int m, n, mat[M][M], d[M], from[M];
bool sel[M];
ifstream fin("data.txt");
ofstream fout("dijkstra.txt");

int main(int argc, char *argv[])
{
	int i, a, b, r, j, t;
	fin>>m>>n;
	for(i=1; i<=m; i++)
		for(j=1; j<=m; j++)
			mat[i][j]=INF;
	for(i=0; i<n; i++)
	{
		fin>>a>>b>>r;
		mat[a][b]=r;
		mat[b][a]=r;
	}
	sel[1]=true;
	for(j=1; j<=m; j++)
	{
		d[j]=mat[1][j];
		from[j]=1;
	}
	from[1]=-1;
	for(i=1; i<m; i++)
	{
		t=INF;
		for(j=1; j<=m; j++)
			if(sel[j]==false && d[j]<t)
			{
				t=d[j];
				r=j;
			}
		sel[r]=true;
		for(j=1; j<=m; j++)
			if(sel[j]==false && mat[r][j]!=INF && d[r]+mat[r][j]<d[j])
			{
				d[j]=d[r]+mat[r][j];
				from[j]=r;
			}
	}
	for(i=1; i<=m; i++)
		fout<<from[i]<<"->"<<i<<endl;
	return 0;
}
