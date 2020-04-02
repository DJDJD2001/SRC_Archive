#define INF 1000000
#define N 100

#include<iostream>

using namespace std;

int map[N][N];
int dist[N];
int from[N];
int i,j,m,n,a,b,c;

void __init__()
{
	cin>>m>>n;
	for(i=0;i<m;i++)
		for(j=0;j<m;j++)
			map[i][j]=INF;
	for(i=0;i<m;i++)
		map[i][i]=0;
	for(i=0;i<n;i++)
	{
		cin>>a>>b>>c;
		map[a][b]=map[b][a]=c;
	}
	for(i=0;i<m;i++)
		dist[i]=map[0][i];
	for(i=0;i<m;i++)
		from[i]=0;
}

void Prt()
{
	for(i=1;i<m;i++)
		cout<<i<<' '<<from[i]<<endl;
}

int main()
{
	__init__();
	for(i=0;i<m-1;i++)
	{
		a=INF;
		b=INF;
		for(j=0;j<m;j++)
			if(dist[j]>0&&dist[j]<b)
			{
				a=j;b=dist[j];
			}
		dist[a]=0;
		j=0;
		while(j<m)
		{
			if(dist[j]>0&&map[a][j]<=dist[j])
			{
				dist[j]=map[a][j];
				from[j]=a;
			}
			j++;
		}
	}
	Prt();
	system("pause");
	return 0;
}
