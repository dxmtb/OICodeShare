/*
ID: dxmtb1
PROG: bookclub
LANG: C++
*/
#include <cstdio>
const int MAXN=50005;
const int MAXM=55;

int N,NQ,P;
int ans[MAXN][MAXM];
bool flag[MAXN];

int main()
{
	freopen("bookclub.in","r",stdin);
	freopen("bookclub.out","w",stdout);
	scanf("%d%d%d",&N,&NQ,&P);
	for(int i=1;i<=N;i++)
		for(int j=1;j<=NQ;j++)
			scanf("%d",ans[i]+j);
	for(int i=1;i<=N;i++)
		flag[i]=true;
	while(P--)
	{
		int Q,A;
		scanf("%d%d",&Q,&A);
		for(int i=1;i<=N;i++)
			flag[i]=flag[i]&(ans[i][Q]==A);
	}
	int re=0;
	for(int i=1;i<=N;i++)
		re+=flag[i];
	printf("%d\n",re);
	return 0;
}
