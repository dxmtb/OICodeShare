/*
ID: dxmtb
PROG: USACO MAR11 Brownie Slicing
TIME: 2011.03.20
STATE: Solved
MEMO: 二分答案
*/
#include <cstdio>
#include <cstring>

const int MAXN=505;

int A,B,R,C;
int a[MAXN][MAXN];
int sum[MAXN];
bool judge(int mid)
{
	int na=0,ni=1;
	memset(sum,0,sizeof(sum));
	while(na<A&&ni<=R)
	{
		for(int i=1;i<=C;i++)
			sum[i]+=a[ni][i];
		int nb=0;
		for(int i=1,ns=0;i<=C&&nb<B;i++)
		{
			ns+=sum[i];
			if (ns>=mid) nb++,ns=0;
		}
		if (nb==B)
		{
			memset(sum,0,sizeof(sum));
			na++;
		}
		ni++;
	}
	return (na==A);
}

void solve()
{
	int l=0,r=2000000;
	while(l+1<r)
	{
		int mid=((long long)(l)+r)/2;
		if (judge(mid)) l=mid;
		else r=mid-1;
	}
	if (l==r) printf("%d\n",l);
	else if (judge(r)) printf("%d\n",r);
	else printf("%d\n",l);
}

int main()
{
	freopen("brownie.in","r",stdin);
	freopen("brownie.out","w",stdout);
	scanf("%d%d%d%d",&R,&C,&A,&B);
	for(int i=1;i<=R;i++)
		for(int j=1;j<=C;j++)
			scanf("%d",a[i]+j);
	solve();
	return 0;
}
