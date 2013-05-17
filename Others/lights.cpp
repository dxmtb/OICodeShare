/*
 * Problem: 灯灯
 * Time: 2011.04.12
 * Author: dxmtb
 * State: Solved
 * Memo: 解异或方程组+搜索
*/
#include <cstdio>
#include <algorithm>
using namespace std;

const int MAXN=50;

long long change[MAXN];

inline void addedge(int u,int v)
{
	change[u]|=(1ll<<v);
	change[v]|=(1ll<<u);
}

int N,M;
int A[MAXN][MAXN],B[MAXN];

inline void swaparr(int i,int j)
{
	for(int k=0;k<N;k++)
		swap(A[i][k],A[j][k]);
	swap(B[i],B[j]);
}

long long sta;

int re;
bool sure[MAXN];
void dfs(int now,int tot)
{
	if (tot>=re)
		return ;
	if (sta==0)
		re=tot;
	if (now==N)
		return ;
	dfs(now+1,tot);
	if (!sure[now])
	{
		sta^=change[now];
		dfs(now+1,tot+1);
		sta^=change[now];
	}
}

int main()
{
	freopen("lights.in","r",stdin);
	freopen("lights.out","w",stdout);
	scanf("%d%d",&N,&M);
	for(int i=0;i<M;i++)
	{
		int a,b;
		scanf("%d%d",&a,&b);
		a--,b--;
		addedge(a,b);
		A[a][b]=A[b][a]=1;
	}
	for(int i=0;i<N;i++)
		A[i][i]=1,B[i]=1,addedge(i,i);
	for(int i=0;i<N;i++)
	{
		if (A[i][i]!=1)
			for(int j=i+1;j<N;j++)
				if (A[j][i]==1)
				{
					swaparr(i,j);
					break;
				}
		if (A[i][i]!=-1)
		for(int j=i+1;j<N;j++)
			if (A[j][i]==1)
			{
				for(int k=0;k<N;k++)
					A[j][k]^=A[i][k];
				B[j]^=B[i];
			}
	}
	int tre=0;
	sta=(1ull<<N)-1;
	for(int i=N-1;i>=0;i--)
	if (A[i][i]==1)
	{
		sure[i]=true;
		for(int j=0;j<N;j++)
			if (j!=i && A[i][j]==1)
			{
				sure[i]=false;
				break;
			}
		if (sure[i] && A[i][i]==1)
		{
			if (B[i]==1)
			{
				tre++;
				sta^=change[i];
			}
			for(int j=0;j<i;j++)
				if (A[j][i]==1)
				{
					for(int k=0;k<N;k++)
						A[j][k]^=A[i][k];
					B[j]^=B[i];
				}
		}
	}
	re=N;
	dfs(0,tre);
	printf("%d\n",re);
	return 0;
}
