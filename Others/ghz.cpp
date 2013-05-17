#include <iostream>
#include <fstream>
using namespace std;

ifstream fin("ghz.in");
ofstream fout("ghz.out");

const int MAXN=21;
const int way[][2]={{2,1},{1,2},{-1,2},{-2,1},{-2,-1},{-1,-2},{1,-2},{2,-1}};

int main()
{
	int n,m,x,y;
	fin>>n>>m>>x>>y;
	long long d[MAXN][MAXN];
	memset(d,0,sizeof(d));
	d[0][0]=1;
	bool b[MAXN][MAXN];
	memset(b,true,sizeof(b));
	b[x][y]=false;
	for(int i=0;i<8;i++)
	{
		b[x+way[i][0]][y+way[i][1]]=false;
		d[x+way[i][0]][y+way[i][1]]=0;
	}
	d[x][y]=0;
	for(int i=0;i<=n;i++)
		for(int j=0;j<=m;j++)
			if (b[i][j])
			{
				if (i-1>=0)d[i][j]+=d[i-1][j];
				if (j-1>=0)d[i][j]+=d[i][j-1];
			}
	fout<<d[n][m]<<endl;
	return 0;
}
