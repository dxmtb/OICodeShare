/*
ID: dxmtb
PROG: 守望者的逃离
TIME: 2010.10.19
STATE: Solved
MEMO: dp
*/
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;

const int MAXN=300000,MAXM=25;

int N,S,M;
int d[2][MAXM+20];

int main()
{
	freopen("escape.in","r",stdin);
	freopen("escape.out","w",stdout);
	scanf("%d%d%d",&M,&S,&N);
	for(int i=0;i<2;i++)
		for(int j=0;j<=MAXM;j++)
			d[i][j]=-0x7fffffff;
	int add=0;
	if (min(M/10,N)*60>=S)
	{
		printf("Yes\n%d\n",int(ceil(S/60.0)));
		return 0;
	}
	add=min(M/10,N);	
	M-=add*10;
	S-=add*60;
	d[0][M]=0;
	for(int i=1;i<=N-add;i++)
	{
		for(int j=0;j<=MAXM;j++)
		{
			int &p=d[i&1][j];
			int *f=d[(i&1)^1];
			if (j>=4) p=f[j-4];
			p=max(p,f[j]+17);
			if (j+10<=MAXM) p=max(p,f[j+10]+60);
			if (p>=S)
			{
				printf("Yes\n%d\n",i+add);
				return 0;
			}
		}
	}
	int re=0;
	for(int i=0;i<=MAXM;i++)
		if (d[(N-add)&1][i]>re)
			re=d[(N-add)&1][i];
	printf("No\n%d\n",re+add*60);
	return 0;
}	
