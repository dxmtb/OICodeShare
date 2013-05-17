#include <iostream>
#include <fstream>
#include <stdio.h>

using namespace std;

const int MAXN=100;
const int MAX=10000;


ifstream fin ("djs.in");
ofstream fout ("djs.out");

int n,m,v;

long gra[MAXN+1][MAXN+1],d[MAXN],pre[MAXN];

int main()
{
	fin>>n>>m>>v;
	for(int i=0;i<=MAXN+1;i++)
	{
		d[i]=MAX;
		pre[i]=MAX;
		for(int j=0;j<=MAXN+1;j++)
			gra[i][j]=MAX;
	}
	for(int i=1;i<=m;i++)
	{
		int x,y,w;
		fin>>x>>y>>w;
		gra[x][y]=w;
	}
	d[v]=0;
	bool visit[MAXN+1];
	memset(visit,false,sizeof(visit));
	for(int i=1;i<n;i++)
	{
		int p,max=MAX;
		for(int j=0;j<n;j++)
			if ((d[j]<max)&&(! visit[j]))
			{
				max=d[j];
				p=j;
			}
		visit[p]=true;
		for(int j=0;j<n;j++)
			if ((! visit[j])&&(gra[p][j]<MAX)&&(d[p]+gra[p][j]<d[j]))
			{
				d[j]=d[p]+gra[p][j];
				pre[j]=p;
			}
	}
	void print(int);
 	for(int i=0;i<n;i++)
	{
		fout<<i<<':'<<endl;
		if (pre[i]!=MAX) {
		fout<<"path:";
		print(i);
		fout<<endl;
		fout<<"cost:"<<d[i]<<endl;}
		else fout<<"no"<<endl;
	}
	return 0;
}

void print(int x)
{
	if (x==v) fout<<x;
	else 
	{
		print(pre[x]);
		fout<<' '<<x;
	}
}
