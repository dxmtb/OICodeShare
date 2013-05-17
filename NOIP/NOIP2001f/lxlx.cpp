/*
ID: dxmtb
PROG: NOIP2001 Car的旅行路线
TIME: 2010.8.3
STATE: Solved
MEMO: spfa
*/
#include <cstdio>
#include <cstring>
#include <cmath>
#include <queue>
using namespace std;

#define sqr(x) ((x)*(x))

const int MAXS=105,oo=0x7fffffff;

int s,t,A,B;
int x[MAXS][4],y[MAXS][4];
double g[MAXS*4][MAXS*4];
double dis[MAXS*4];
int path[MAXS*4];

inline int getdis2(int x,int y)
{
	return sqr(x)+sqr(y);
}

inline double getdis(int x,int y)
{
	return sqrt(double(getdis2(x,y)));
}

inline int num(int x,int y)
{
	if (x*4+y>=MAXS)
		printf("wrong!");
	return x*4+y;
}

void init()
{
	for(int i=0;i<MAXS*4;i++)
		for(int j=0;j<MAXS*4;j++)
			g[i][j]=oo;
	for(int i=0;i<MAXS*4;i++)
		g[i][i]=0;
	scanf("%d%d%d%d",&s,&t,&A,&B);
	--A;--B;
	for(int i=0;i<s;i++)
	{
		int T;
		scanf("%d%d%d%d%d%d%d",&x[i][0],&y[i][0],&x[i][1],&y[i][1],
				&x[i][2],&y[i][2],&T);
		int a,b,c;
		for(a=0;a<3;a++)
		{
			for(b=a+1;b<3;b++)
			{
				c=3-a-b;
				int l=getdis2(x[i][c]-x[i][a],y[i][c]-y[i][a])
						+getdis2(x[i][c]-x[i][b],y[i][c]-y[i][b]),
					r=getdis2(x[i][a]-x[i][b],y[i][a]-y[i][b]);
				if (l==r)
					break;
			}
			if(b!=3)
			{
				x[i][3]=x[i][a]+x[i][b]-x[i][c];
				y[i][3]=y[i][a]+y[i][b]-y[i][c];
				for(int p=0;p<4;p++)
					for(int q=0;q<4;q++)
						g[num(i,p)][num(i,q)]=getdis(x[i][p]-x[i][q],y[i][p]-y[i][q])*T;
				break;
			}
		}
	}
	for(int i=0;i<s;i++)
		for(int j=i+1;j<s;j++)
			for(int a=0;a<4;a++)
				for(int b=0;b<4;b++)
					g[num(i,a)][num(j,b)]=g[num(j,b)][num(i,a)]=getdis(x[i][a]-x[j][b],y[i][a]-y[j][b])*t;
}

void spfa(int ss)
{
	for(int i=0;i<MAXS*4;i++)
		dis[i]=oo;
	bool in[MAXS*4];
	memset(in,false,sizeof(in));
	dis[ss]=0;
	queue<int> q;
	q.push(ss);
	in[ss]=true;
	while (!q.empty())
	{
		int now=q.front();
		q.pop();
		in[now]=false;
		for(int i=0;i<s*4;i++)
			if (g[now][i]!=oo&&dis[now]+g[now][i]<dis[i])
			{
				path[i]=now;
				dis[i]=dis[now]+g[now][i];
				if (!in[i])
				{
					in[i]=true;
					q.push(i);
				}
			}
	}
}

void solve()
{
	init();
	double re=oo;
	for(int ii=0;ii<4;ii++)
	{
		spfa(A*4+ii);
		for(int j=0;j<4;j++)
			if (dis[B*4+j]<re)
				re=dis[B*4+j];
	}
	printf("%.1lf\n",re);
}

int main() 
{
	freopen("lxlx.in","r",stdin);
	freopen("lxlx.out","w",stdout);
	int n;
	scanf("%d",&n);
	for(int i=0;i<n;i++)
		solve();
	return 0;
}
