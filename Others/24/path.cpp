/*
ID: dxmtb
PROG: 线性规划与网络流24题 最小路径覆盖问题
TIME: 2011.01.31
STATE: Solved
MEMO: 最小路径覆盖
*/
#include <cstdio>
#include <queue>
#include <vector>
#include <cstring>
using namespace std;

const int MAXN=300;
const int oo=0x7fffffff;

vector<int> adj[MAXN];

inline void addedge(int u,int v)
{
	adj[u].push_back(v);
}

int S,T;

int n,m;

bool used[MAXN];
int mat[MAXN];
bool find(int u)
{
	for(int i=0;i<adj[u].size();i++)
	{
		int v=adj[u][i];
		if (!used[v])
		{
			used[v]=true;
			if (mat[v]==0||find(mat[v]))
			{
				mat[v]=u;
				return true;
			}
		}
	}
	return false;
}

int maxmatch;
void hungrian()
{
	for(int i=1;i<=n;i++)
	{
		if (find(i))
			maxmatch++;
		memset(used,false,sizeof(used));
	}
}

void print()
{
	for(int i=1;i<=n;i++)
		if (mat[i])
			used[mat[i]]=true;
	for(int i=1;i<=n;i++)
		if (!used[i])
		{
			printf("%d",i);
			for(int j=mat[i];j!=0;j=mat[j])
				printf(" %d",j);
			printf("\n");
		}
}

int main()
{
	freopen("path.in","r",stdin);
	freopen("path.out","w",stdout);
	scanf("%d%d",&n,&m);
	while(m--)
	{
		int a,b;
		scanf("%d%d",&a,&b);
		addedge(a,b);
	}
	hungrian();
	print();
	if (maxmatch==n) printf("1\n");
	else printf("%d\n",n-maxmatch);
	return 0;
}

