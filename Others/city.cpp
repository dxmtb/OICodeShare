#include <iostream>
#include <fstream>
#include <stdio.h>

using namespace std;

const int MAXN=100;
const int MAX=10000;

ifstream fin ("city.in");
ofstream fout ("city.out");

int n,m,v,e;

bool gra[MAXN+1][MAXN+1];
int d[MAXN];

int main()
{
	fin>>n>>m>>v>>e;
	for(int i=0;i<=MAXN+1;i++)
		d[i]=MAX;
	memset(gra,false,sizeof(gra));
	for(int i=1;i<=m;i++)
	{
		int x,y;
		fin>>x>>y;
		gra[x][y]=1;
		gra[y][x]=1;
	}
	d[v]=0;
	bool visit[MAXN+1];
	memset(visit,false,sizeof(visit));
	for(int i=1;i<n;i++)
	{
		int p,max=MAX;
		for(int j=1;j<=n;j++)
			if ((d[j]<max)&&(! visit[j]))
			{
				max=d[j];
				p=j;
			}
		visit[p]=true;
		for(int j=1;j<=n;j++)
			if ((! visit[j])&&(gra[p][j])&&(d[p]+1<d[j]))
				d[j]=d[p]+1;
	}
	fout<<d[e]+1<<endl;
	return 0;
}
