/*
ID: dxmtb
PROG: NOIP2003 Éñ¾­ÍøÂç
TIME: 2010.5.13
STATE: Solved
MEMO: Ä£Äâ
*/
#include <cstdio>
#include <cstring>
using namespace std;

const int MAXN=220;

int n,m;
int U[MAXN],C[MAXN],W[MAXN][MAXN];
bool g[MAXN][MAXN],in[MAXN];
int id[MAXN],od[MAXN];

void init()
{
	memset(W,-1,sizeof(W));
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d",&C[i],&U[i]);
		if (C[i]==0)C[i]-=U[i];
	}
	for(int i=0;i<m;i++)
	{
		int a,b;
		scanf("%d%d",&a,&b);
		scanf("%d",&W[a][b]);
		g[a][b]=true;
		id[b]++;
		od[a]++;
	}
}

void solve()
{
	bool flag=true;
	while (flag)
	{
		flag=false;
		for(int i=1;i<=n;i++)
			if (id[i]==0&&!in[i])
			{
				flag=true;
				in[i]=true;
				for(int j=1;j<=n;j++)
					if (g[i][j])
					{
						if (C[i]>0)C[j]+=W[i][j]*C[i];
						id[j]--;
					}
				if (od[i])C[i]=0;
			}
	}
}

void print()
{
	bool flag=true;
	for(int i=1;i<=n;i++)
		if (C[i]>0&&!od[i])
		{
			printf("%d %d\n",i,C[i]);
			flag=false;
		}
	if (flag)
		printf("NULL\n");
}

int main() 
{
	freopen("sjwl.in","r",stdin);
	freopen("sjwl.out","w",stdout);
	init();
	solve();
	print();
	return 0;
}
