/*
ID: dxmtb
PROG: 智力大冲浪
TIME: 2010.9.9
STATE: Solved
MEMO: 贪心
*/
#include <cstdio>
#include <algorithm>
using namespace std;

const int MAXN=500;
const int oo=0x7fffffff;

struct Node
{
	int s,t;
}g[MAXN];

bool operator < (Node a,Node b)
{
	return a.t>b.t||(a.t==b.t&&a.s<b.s);
}

int m,n,ans;
bool used[MAXN+1];

int main()
{
	freopen("riddle.in","r",stdin);
	freopen("riddle.out","w",stdout);
	scanf("%d%d",&m,&n);
	for(int i=0;i<n;i++)
		scanf("%d",&g[i].s);
	for(int i=0;i<n;i++)
		scanf("%d",&g[i].t);
	sort(g,g+n);
	for(int i=0;i<n;i++)
	{
		int j;
		for(j=g[i].s;j;j--)
			if (!used[j])
			{
				used[j]=true;
				break;
			}
		if (!j)
			ans+=g[i].t;
	}
	printf("%d\n",m-ans);
	return 0;
}
