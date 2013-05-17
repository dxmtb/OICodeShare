/*
ID: dxmtb1
PROG: cowtour
LANG: C++
*/
#include <cstdio>
#include <cmath>
using namespace std;

const int MAXN=160;

struct Edge
{
	int v;
	Edge *next;
	Edge(int a,Edge *b):v(a),next(b){}
};

int n,scc=0;
double re=0x7fffffff;
Edge *adj[MAXN];
double dis[MAXN][MAXN],d[MAXN][MAXN],id[MAXN],own[MAXN];
int m[MAXN],father[MAXN];

inline double max(double x,double y)
{
	if (x>y)return x;
	return y;
}

void dfs(int u)
{
	father[u]=scc;
	for(Edge *p=adj[u];p;p=p->next)
		if (!father[p->v])
			dfs(p->v);
}

void init()
{
	scanf("%d",&n);
	int x[MAXN],y[MAXN];
	for(int i=0;i<n;i++)
		scanf("%d%d",&x[i],&y[i]);
	for(int i=0;i<n;i++)
		for(int j=i+1;j<n;j++)
		{
			int x1=x[i],y1=y[i];
			int x2=x[j],y2=y[j];
			dis[i][j]=dis[j][i]=sqrt(double(x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
			d[i][j]=d[j][i]=0x7fffffff;			
		}
	for(int i=0;i<n;i++)
		d[i][i]=0;
	getchar();
	for(int i=0;i<n;i++)
	{
		char str[MAXN+1];
		gets(str);
		for(int j=0;j<n;j++)
			if (str[j]-'0')
			{
				adj[i]=new Edge(j,adj[i]);
				d[i][j]=dis[i][j];
			}
	}
	for(int i=0;i<n;i++)
		if(!father[i])
		{
			++scc;
			dfs(i);
		}
}

void solve()
{
	for(int k=0;k<n;k++)
		for(int i=0;i<n;i++)
			if (i!=k&&father[i]==father[k])
			for(int j=0;j<n;j++)
				if (i!=j&&j!=k&&father[j]==father[k]&&father[i]==father[j])
				if (d[i][j]>d[i][k]+d[k][j])
					d[i][j]=d[i][k]+d[k][j];
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
			if (father[i]==father[j])
				if (d[i][j]>id[i])
					id[i]=d[i][j];
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
			if (father[i]==father[j]&&d[i][j]>own[father[i]])
				own[father[i]]=d[i][j];				
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
			if (father[i]!=father[j]&&max(id[i]+id[j]+dis[i][j],max(own[father[i]],own[father[j]]))<re)
					re=max(id[i]+id[j]+dis[i][j],max(own[father[i]],own[father[j]]));
	printf("%.6lf\n",re);
}

int main() 
{
	freopen("cowtour.in","r",stdin);
	freopen("cowtour.out","w",stdout);
	init();
	solve();
	return 0;
}
