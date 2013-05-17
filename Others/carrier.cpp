/*
ID: dxmtb
PROG: 邮递员
TIME: 2010.11.17
STATE: Solved
MEMO: 欧拉路算法
*/
#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;

const int MAXN=1000;

int n,m;
int g[MAXN+1][MAXN+1];
int d[MAXN+1],res[MAXN+1]={0};
int top;

void euler(int v)
{
	for(int i=1;i<=n;i++)
		if (g[v][i])
		{
			g[v][i]--;
			g[i][v]--;
			euler(i);
		}
	res[top++]=v;
}

int main() 
{
	freopen("carrier.in","r",stdin);
	freopen("carrier.out","w",stdout);
	scanf("%d%d",&n,&m);	
	for(int i=0,t;i<n;i++)
		scanf("%d",&t);
	for(int i=0;i<m;i++)
	{
		int a,b;
		scanf("%d%d",&a,&b);
		g[a][b]++;
		g[b][a]++;
	}
	euler(1);
	printf("%d\n",top-1);
	printf("%d",res[top-1]);
	for(int i=top-2;i>=0;i--)
		printf(" %d",res[i]);
	printf("\n");
	return 0;
}
