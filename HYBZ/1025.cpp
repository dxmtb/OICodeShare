/*
ID: dxmtb
PROG: [SCOI2009]游戏 
TIME: 2011.03.23
STATE: Solved
MEMO: 数学方法
*/
#include <cstdio>
#include <iostream>
using namespace std;

const int MAXN=1005;

bool flag[MAXN];
int prime[MAXN],tot;
int N;
void init()
{
	for(int i=2;i<=N;i++)
		flag[i]=true;
	for(int i=2;i<=N;i++)
	{
		if (flag[i])
			prime[++tot]=i;
		for(int j=i;j<=N;j+=i)
			flag[j]=false;
	}
}

long long d[MAXN][MAXN];
int main()
{
//	freopen("1025.in","r",stdin);
	scanf("%d",&N);
	init();
	d[0][0]=1;
	for(int i=1;i<=tot;i++)
		for(int j=0;j<=N;j++)
		{
			d[i][j]=d[i-1][j];
			for(int k=prime[i];k<=j;k*=prime[i])
				d[i][j]+=d[i-1][j-k];
		}
	long long re=0;
	for(int j=0;j<=N;j++)
		re+=d[tot][j];
	cout<<re<<endl;
	return 0;
}
