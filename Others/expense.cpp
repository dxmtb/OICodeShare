/*
ID: dxmtb
PROG: 月度花费
TIME: 2010.10.23
STATE: Solved
MEMO: 二分答案
*/
#include <cstdio>
#include <algorithm>
using namespace std;

const int MAXN=100000;

int n,m,f[MAXN],maxe,sum;

inline bool check(int ans)
{
	int need=1,sum=0;
	for(int i=0;i<n&&need<=m;i++)
	{
		if (f[i]>ans) return false;
		if (sum+f[i]>ans) need++,sum=f[i];
		else sum+=f[i];
	}
	if (need>m)	return false;
	else return true;
}

inline void solve()
{
	int l=maxe,r=sum;
	while(l<=r)
	{
		int mid=(l+r)>>1;
		if (check(mid)) r=mid-1;
		else l=mid+1;
	}
	printf("%d\n",r+1);
}

int main()
{
	freopen("expense.in","r",stdin);
	freopen("expense.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=0;i<n;i++)
	{
		scanf("%d",f+i);
		sum+=f[i];
		maxe=max(maxe,f[i]);
	}
	solve();
	return 0;
}
