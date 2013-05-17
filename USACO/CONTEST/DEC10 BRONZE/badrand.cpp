/*
ID: dxmtb1
PROG: badrand
LANG: C++
*/
#include <cstdio>

const int MAXN=10000;

bool flag[MAXN];
int re,N;

int main()
{
	freopen("badrand.in","r",stdin);
	freopen("badrand.out","w",stdout);
	scanf("%d",&N);
	do
	{
		flag[N]=true;
		re++;
		N=N/10%100;
		N*=N;
	}while(!flag[N]);
	printf("%d\n",re);
	return 0;
}
