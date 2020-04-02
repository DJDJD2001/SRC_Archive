#define M 100
#define INF 0x7fffffff

#include <fstream>
using namespace std;

int m, n, mat[M][M];
ifstream fin("data.txt");
ofstream fout("floyd.txt");

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
	return 0;
}
