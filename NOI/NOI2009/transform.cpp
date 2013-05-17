/*
 * Problem: NOI2009 变换序列
 * Time: 2011.05.18
 * Author: dxmtb
 * State: Solved
 * Memo: 倒着匹配
*/
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int MAXN=10005;

int mat[MAXN];
bool vis[MAXN];
int adj[MAXN][2];
bool find(int u)
{
	if (vis[u])
		return false;
	vis[u]=true;
	for(int i=0;i<2;i++)
		if (!mat[adj[u][i]] || find(mat[adj[u][i]]))
		{
			mat[adj[u][i]]=u;
			return true;
		}
	return false;
}

int N;
void hungary()
{
	for(int i=N-1;i>=0;i--)
	{
		memset(vis,false,sizeof(vis));
		if (!find(i))
		{
			printf("No Answer\n");
			exit(0);
		}
	}
}

int ans[MAXN];
int main()
{
	freopen("transform.in","r",stdin);
	freopen("transform.out","w",stdout);
	scanf("%d",&N);
	for(int i=0;i<N;i++)
	{
		int x;
		scanf("%d",&x);
		adj[i][0]=(i+x)%N;
		x=i-x;
		if (x<0) x+=N;
		adj[i][1]=x;
		if (adj[i][1]<adj[i][0])
			swap(adj[i][0],adj[i][1]);
	}
	hungary();
	for(int i=0;i<N;i++)
		ans[mat[i]]=i;
	printf("%d",ans[0]);
	for(int i=1;i<N;i++)
		printf(" %d",ans[i]);
	return 0;
}
