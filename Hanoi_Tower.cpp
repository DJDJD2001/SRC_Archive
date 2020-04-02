#include <fstream.h>
ifstream fin("ta.in");
ofstream fout("ta.out");
int k=0;
void ta(int n,char a,char c,char b)
{if (n==0)
    return;
 ta(n-1,a,b,c);
 k++;
 fout<<k<<":"<<a<<"------------------->"<<c<<'\n';   
 ta(n-1,b,c,a);   
    }
int main()
{int n;
 char x='A',y='B',z='C';   
 fin>>n;
 ta(n,x,z,y);
 return 0;   
    }    
