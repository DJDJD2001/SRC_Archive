#define N 100 
#include <iostream>

using namespace std;

struct NODE
{
	int x,y,step;
};

NODE queue[N*N];
char map[N][N];
int n,a,b;
NODE s,e;

void __init__()
{
	int i,j;
	a=b=0;
	cin>>n;
	for(i=1;i<=n;i++)
        cin>>map[i]+1;
    for(i=0;i<=n+1;i++)
        map[i][0]=map[0][i]=map[n+1][i]=map[i][n+1]='#';
    s.x=s.y=1;
    e.x=e.y=n;
	s.step=0;
}

bool f(int X,int Y)
{
	if(map[X][Y]=='_')return true;
	else return false;
}

void test()
{
	int i,j;
	queue[b]=s;
	b++;
	map[s.x][s.y]='*';
	
	while(queue[a].x!=e.x||queue[a].y!=e.y)
	{
		if(f(queue[a].x-1,queue[a].y))
		{
			map[queue[a].x-1][queue[a].y]='*';
			queue[b].x=queue[a].x-1;
			queue[b].y=queue[a].y;
			queue[b].step=queue[a].step+1;
			b++;
		}
		if(f(queue[a].x+1,queue[a].y))
		{
			map[queue[a].x+1][queue[a].y]='*';
			queue[b].x=queue[a].x+1;
			queue[b].y=queue[a].y;
			queue[b].step=queue[a].step+1;
			b++;
		}
		if(f(queue[a].x,queue[a].y-1))
		{
			map[queue[a].x][queue[a].y-1]='*';
			queue[b].x=queue[a].x;
			queue[b].y=queue[a].y-1;
			queue[b].step=queue[a].step+1;
			b++;
		}
		if(f(queue[a].x,queue[a].y+1))
		{
			map[queue[a].x][queue[a].y+1]='*';
			queue[b].x=queue[a].x;
			queue[b].y=queue[a].y+1;
			queue[b].step=queue[a].step+1;
			b++;
		}
		a++;
	}
	
	cout<<queue[a].step<<endl; 
}


int main(int argc, char *argv[])
{
	__init__();
	test();
	/*for(int i=0;i<=n+1;i++)
	{
		for(int j=0;j<=n+1;j++)
		    cout<<map[i][j];
        cout<<endl;
	}*/
	system("pause");
	return 0;
}
