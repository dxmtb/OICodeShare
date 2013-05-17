/*
ID: dxmtb
PROG: 寻找MM
TIME: 2010.11.9
STATE: Solved
MEMO: dfs
*/
#include <cstdio>
#include <iostream>
#include <string>
using namespace std;
const int MAXN=25;
const int way[4][2]={{1,0},{-1,0},{0,1},{0,-1}};

bool vis[MAXN][MAXN];
int re,n,m;
string str[MAXN];

void dfs(int x,int y)
{
	vis[x][y]=true,re++;
	for(int i=0;i<4;i++)
	{
		int nx=x+way[i][0],ny=y+way[i][1];
		if (nx>=0&&nx<n&&ny>=0&&ny<m&&str[nx][ny]=='.'&&!vis[nx][ny])
			dfs(nx,ny);
	}
}

int main()
{
	cin>>n>>m;
	for(int i=0;i<n;i++)
		cin>>str[i];
	for(int i=0;i<n;i++)
		for(int j=0;j<m;j++)
			if (str[i][j]=='@')
			{
				dfs(i,j);
				break;
			}
	cout<<re-1<<endl;
	return 0;
}
