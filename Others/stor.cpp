/*
ID: dxmtb
PROG: 线性存储问题
TIME: 2010.9.28
STATE: Solved
MEMO: 贪心
*/
#include <cstdio>
#include <algorithm>
using namespace std;

const int MAXN=10005;

int n;
int L[MAXN],F[MAXN];
int re[MAXN];

bool cmp(int a,int b)
{
	return (F[a]*L[b]>F[b]*L[a]);
}

int main()
{
	freopen("stor.in","r",stdin);
	freopen("stor.out","w",stdout);
	scanf("%d",&n);
	for(int i=0;i<n;i++)
	{
		scanf("%d%d",L+i,F+i);
		re[i]=i;
	}
	sort(re,re+n,cmp);
	printf("%d",re[0]+1);
	for(int i=1;i<n;i++)
		printf(" %d",re[i]+1);
	printf("\n");
	return 0;
}
