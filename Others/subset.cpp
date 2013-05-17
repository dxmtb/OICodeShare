/*
ID: dxmtb
PROG: 最优连通子集
TIME: 2010.7.3
STATE: Solved
MEMO: 树形dp
*/
#include <cstdio>
#include <cstring>
using namespace std;

const int MAXN=1000,MAXINT=0x7fffffff;

int n,re=-MAXINT;
int x[MAXN],y[MAXN],c[MAXN];
bool g[MAXN][MAXN];
int d[MAXN];
bool v[MAXN];

inline int abs(int x)
{ return x>0?x:-x;}

void dd(int i)
{
	v[i]=true;
	d[i]+=c[i];
	for(int j=0;j<n;j++)
		if(g[i][j]&&!v[j])
		{
			dd(j);
			if(d[j]>0)
				d[i]+=d[j];
		}
	if(d[i]<0)
		d[i]=0;
}

int main()
{
	freopen("subset.in","r",stdin);
	freopen("subset.out","w",stdout);
	scanf("%d",&n);
	for(int i=0;i<n;i++)
		scanf("%d%d%d",x+i,y+i,c+i);
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
			if(i!=j&&abs(x[i]-x[j])+abs(y[i]-y[j])==1)
				g[i][j]=true;
	memset(v,false,sizeof(v));
	memset(d,0,sizeof(d));
	dd(0);
	for(int i=0;i<n;i++)
	  if(d[i]>re)re=d[i];
	printf("%d\n",re);
	return 0;
}
