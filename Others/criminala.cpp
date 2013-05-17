/*
ID: dxmtb
PROG: 罪犯问题A
TIME: 2010.10.19
STATE: Solved
MEMO: 贪心
*/
#include <cstdio>
#include <algorithm>
using namespace std;

const int MAXN=1005;

int N,M;
int a1[MAXN],a2[MAXN];
int re1,re2;

int main()
{
	freopen("criminala.in","r",stdin);
	freopen("criminala.out","w",stdout);
	scanf("%d%d",&N,&M);
	for(int i=0;i<M;i++)
	{
		int X;
		scanf("%d",&X);
		if (X<0) a2[-X]++;
		else a1[X]++;
	}
	for(int i=1;i<=N;i++)
	{
		re1+=max(a1[i],a2[i]);
		re2+=min(a1[i],a2[i]);
	}
	printf("%d\n%d\n",re1,re2);
	return 0;
}
