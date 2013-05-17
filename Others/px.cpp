/*
ID: dxmtb
PROG: 排序工作量-加强版
TIME: 2010.10.14
STATE: Solved
MEMO: 非递归线段树
*/
#include <cstdio>
using namespace std;

const int m=(1<<20);

int tree[2*m+5];
int re;

inline void insert(int n)
{
	for(tree[n+=m]++,n>>=1;n;n>>=1)
		tree[n]=tree[n+n]+tree[n+n+1];
}

inline int sum(int s,int t)
{
	int ans=0;
	for(s=s+m-1,t=t+m+1;s^t^1;s>>=1,t>>=1)
	{
		if (~s&1) ans+=tree[s^1];
		if (t&1) ans+=tree[t^1];
	}
	return ans;
}

int main()
{
	freopen("px.in","r",stdin);
	freopen("px.out","w",stdout);
	int t;
	scanf("%d",&t);
	while(t--)
	{
		int k;
		scanf("%d",&k);
		re+=sum(k+1,1000000);
		insert(k);
	}
	printf("%d",re);
	return 0;
}
