/*
  ID: dxmtb1
  PROG: fence
  LANG: C++
*/
#include <cstdio>
using namespace std;
const int MAXN=501,MAXM=1025;

int g[MAXN][MAXN];
int n;
int d[MAXN];
int begin=0;
int stack[MAXM],stop=0;
bool used[MAXN];

void euler(int u)
{
	for(int i=1;i<MAXN;i++)
		if (g[u][i])
		{
			g[u][i]--;
			g[i][u]--;
			euler(i);
		}
	stack[stop++]=u;
}

int main()
{
	freopen("fence.in","r",stdin);
	freopen("fence.out","w",stdout);
	scanf("%d",&n);
	for(int i=0;i<n;i++)
	{
		int a,b;
		scanf("%d%d",&a,&b);
		used[a]=used[b]=true;
		g[a][b]++;
		g[b][a]++;
		d[a]++,d[b]++;
	}
	for(int i=1;i<MAXN;i++)
		if (d[i]&1)
		{
			begin=i;
			break;
		}
	if (!begin)
		for(int i=1;i<MAXN;i++)
			if (used[i])
			{
				begin=i;
				break;
			}
	euler(begin);
	for(int i=stop-1;i>=0;i--)
		printf("%d\n",stack[i]);
	return 0;
}
