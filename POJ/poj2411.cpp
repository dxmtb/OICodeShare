/*
ID: dxmtb
PROG: pku 2411 Mondriaan's Dream
TIME: 2010.5.14
STATE: Solved
MEMO: ×´Ì¬Ñ¹Ëõ
*/
#include <cstdio>
#include <iostream>
using namespace std;

const int MAXN=11;

long long d[MAXN+1][MAXN+1][1<<MAXN];
int n;

void dfs(int row,int s1,int s2)
{
	if (row>MAXN)return;
	d[n][row][s1]+=d[n-1][row][s2];
	dfs(row+1,s1*2+1,s2*2);
	dfs(row+2,s1*4+3,s2*4+3);	
	dfs(row+1,s1*2,s2*2+1);
}

int main() 
{
	freopen("2411.in","r",stdin);
	for(int i=1;i<=MAXN;i++)
		d[0][i][(1<<i)-1]=1;
	for(n=1;n<=MAXN;n++)
		dfs(0,0,0);
	while (true)
	{
		int a,b;
		scanf("%d%d",&a,&b);
		if (!a)break;
		cout<<d[a][b][(1<<b)-1]<<endl;
	}
	return 0;
}
