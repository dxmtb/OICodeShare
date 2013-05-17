/*
 * Problem: [BeijingWc2008]雷涛的小猫
 * Time: 2011.04.06
 * Author: dxmtb
 * State: Solved
 * Memo: dp
*/
 #include <cstdio>
#include <algorithm>
using namespace std;

const int MAXN=5005;

int N,H,D;
short w[MAXN][MAXN];
int d[MAXN][MAXN];

int main()
{
	freopen("1270.in","r",stdin);
	scanf("%d%d%d",&N,&H,&D);
	for(int i=0;i<N;i++)
	{
		int t;
		scanf("%d",&t);
		while(t--)
		{
			int h;
			scanf("%d",&h);
			w[i][h]++;
		}
	}
	for(int i=H;i>=0;i--)
	{
		int ma=0;
		if (i+D<=H)
			for(int j=0;j<N;j++)
				if (d[i+D][j]>ma)
					ma=d[i+D][j];
		for(int j=0;j<N;j++)
			d[i][j]=max(d[i+1][j],ma)+w[j][i];
	}
	int re=0;
	for(int j=0;j<N;j++)
		if (d[0][j]>re)
			re=d[0][j];
	printf("%d\n",re);
	return 0;
}
