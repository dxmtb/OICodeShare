/*
ID: dxmtb
PROG: NOIP2005 篝火晚会
TIME: 2010.9.21
STATE: Solved
MEMO: 扫描
*/
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN=50000;

int hope[MAXN][2];
int in[MAXN],out[MAXN];
int a[MAXN];
int n,re;

int used[MAXN];
bool dfs(int u,int dep)
{
	if (dep==n) return true;
	a[dep]=u;
	used[u]=true;
	if (!used[hope[u][0]]||(hope[u][0]==1&&dep==n-1))
		return dfs(hope[u][0],dep+1);
	if (!used[hope[u][1]]||(hope[u][1]==1&&dep==n-1))
		return dfs(hope[u][1],dep+1);
	return false;
}

void solve()
{
	memset(used,false,sizeof(used));
	for(int i=0;i<n;i++)
		used[(a[i]-i-1+n)%n]++;
	for(int i=0;i<n;i++)
		re=max(used[i],re);
}

int main()
{
	freopen("fire.in","r",stdin);
	freopen("fire.out","w",stdout);
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d",hope[i],hope[i]+1);
	}
	if (!dfs(1,0))
	{
		printf("-1\n");
		return 0;
	}
	re=0;
	solve();
	int b[MAXN];
	memcpy(b,a,sizeof(a));
	for(int i=0;i<n;i++)
		a[i]=b[n-1-i];
	solve();
	printf("%d",n-re);
	return 0;
}

