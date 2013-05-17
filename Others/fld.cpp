#include <iostream>
#include <fstream>
using namespace std;

const int MAXN=50,MAXINT=100000;

ifstream fin ("fld.in");
ofstream fout ("fld.out");

int n,m,v,u;
int d[MAXN][MAXN],w[MAXN][MAXN],path[MAXN][MAXN];

int main()
{
	fin>>n>>m>>v>>u;
	for(int i=0;i<MAXN;i++)
		for(int j=0;j<MAXN;j++)
		{
			d[i][j]=MAXINT;
			w[i][j]=MAXINT;
			path[i][j]=MAXINT;
		}
	for(int i=0;i<n;i++)	
	{
		d[i][i]=0;
		w[i][i]=0;
	}
	for(int i=0;i<m;i++)
	{
		int x,y,z;
		fin>>x>>y>>z;
		w[x][y]=z;
		d[x][y]=z;
		path[x][y]=x;
		w[y][x]=z;
		d[y][x]=z;
		path[y][x]=y;
	}
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
			if (i!=j)
				for(int k=0;k<n;k++)
					if((i!=k)&&(j!=k)&&(d[i][k]+d[k][j]<d[i][j]))
					{
						d[i][j]=d[i][k]+d[k][j];
						path[i][j]=k;
					}
	void print(int,int);
	if (path[v][u]!=MAXINT)
	{
		print(v,u);
		fout<<endl;
		fout<<d[v][u]<<endl;
	}
	else fout<<"no"<<endl;
	return 0;
}

void print(int a,int b)
{
	if (a==b) fout<<a;
	else 
	{
		print(a,path[a][b]);
		fout<<b;
	}
}
