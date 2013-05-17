/*
ID: dxmtb
PROG: NOIP2007 Í³¼ÆÊý×Ö
TIME: 2010.5.15
STATE: Solved
MEMO: sort
*/
#include <cstdio>
#include <algorithm>
using namespace std;

const int MAXN=200000;

int n,a[MAXN];

void init()
{
	scanf("%d",&n);
	for(int i=0;i<n;i++)
		scanf("%d",&a[i]);
}

void solve()
{
	sort(a,a+n);
	printf("%d ",a[0]);
	int count=1;
	for(int i=1;i<n;i++)
	{
		if (a[i]!=a[i-1])
		{
			printf("%d\n%d ",count,a[i]);
			count=1;
		}
		else
			count++;
	}
	printf("%d\n",count);
}

int main() 
{
	freopen("count.in","r",stdin);
	freopen("count.out","w",stdout);
	init();
	solve();
	return 0;
}
