/*
ID: dxmtb
PROG: 一笔画
TIME: 2010.4.17
STATE: Solved
MEMO: 欧拉路算法
*/
#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;

const int MAXN=1000;

int n,m,odt=0,start=0;
bool g[MAXN+1][MAXN+1];
int d[MAXN+1],res[MAXN+1]={0};

void init()
{
	scanf("%d%d",&n,&m);	
	scanf("%*[^\n]");
	for(int i=0;i<m;i++)
	{
		int a,b;
		scanf("%d%d",&a,&b);
		scanf("%*[^\n]");
		g[a][b]=true;
		g[b][a]=true;
		d[a]++,d[b]++;
	}
	for(int i=1;i<=n&&odt<=2;i++)
		if (d[i]&1==1)
		{
			odt++;
			start=i;
		}
	if (odt>2) 
	{
		printf("no");
		exit(0);
	}
}

void euler(int v)
{
	for(int i=1;i<=n;i++)
		if (g[v][i])
		{
			g[v][i]=g[i][v]=false;
			euler(i);
		}
	res[++res[0]]=v;
}

int main() 
{
	freopen("ybh.in","r",stdin);
	freopen("ybh.out","w",stdout);
	init();
	if(start==0)start=1;
	euler(start);
	printf("%d",res[res[0]]);
	for(int i=res[0]-1;i>0;i--)
		printf(" %d",res[i]);
	printf("\n");
	return 0;
}
