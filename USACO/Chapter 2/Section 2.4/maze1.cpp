/*
ID: dxmtb1
PROG: maze1
LANG: C++
*/
#include <cstdio>
#include <iostream>
#include <queue>
using namespace std;

const int MAXW=40,MAXH=103,MAXS=(MAXW+2)*(MAXH+2),MAXINT=0x7fffffff;

struct Edge
{
	int v;
	Edge *next;
	Edge(int a,Edge *nn):v(a),next(nn){}
};

int W,H;
Edge *adj[MAXS+1];
string ch[2*MAXH+2];
int dis[MAXS+1];
bool in[MAXS];

inline int getnum(int x,int y)
{
	return x*(W+2)+y;
}

void init()
{
	cin>>W>>H;
	getchar();
	for(int i=1;i<=2*H+1;i++)
	{
		getline(cin,ch[i]);
		int li=(i+1)/2;
		if (i&1==1)
		{
			for(int j=1;j<=W;++j)
				if (ch[i][2*j-1]==' ')
				{
					int t1=getnum(li,j),t2;
					t2=getnum(li-1,j);
					adj[t1]=new Edge(t2,adj[t1]);
					adj[t2]=new Edge(t1,adj[t2]);
				}
		}
		else
			for(int j=1;j<=W+1;++j)
				if (ch[i][2*(j-1)]==' ')
				{
					int t1=getnum(li,j),t2;
					t2=getnum(li,j-1);
					adj[t1]=new Edge(t2,adj[t1]);
					adj[t2]=new Edge(t1,adj[t2]);
				}
			
	}
	for(int i=0;i<(W+2)*(H+2);i++)
		dis[i]=MAXINT;
}

void spfa()
{
	queue<int> q;
	for(int i=1;i<=W;i++)
	{
		q.push(getnum(0,i));
		q.push(getnum(H+1,i));
		dis[getnum(0,i)]=dis[getnum(H+1,i)]=0;
		in[getnum(0,i)]=in[getnum(H+1,i)]=true;
	}
	for(int i=1;i<=H;i++)
	{
		q.push(getnum(i,0));
		q.push(getnum(i,W+1));
		dis[getnum(i,0)]=dis[getnum(i,W+1)]=0;
		in[getnum(i,0)]=in[getnum(i,W+1)]=true;
	}
	int count=0;
	while (!q.empty())
	{
		count++;
		int u=q.front();
		q.pop();
		in[u]=false;
		for(Edge *p=adj[u];p;p=p->next)
		{
			if (dis[u]<MAXINT&&dis[u]+1<=dis[p->v])
			{
				dis[p->v]=dis[u]+1;
				if (!in[p->v])
				{
					q.push(p->v);
					in[p->v]=true;
				}
			}
		}
	}
}

void solve()
{
	int ans=0;
	for(int i=1;i<=H;i++)
		for(int j=1;j<=W;j++)
			if (dis[getnum(i,j)]>ans)
				ans=dis[getnum(i,j)];
	cout<<ans<<endl;
}

int main() 
{
	freopen("maze1.in","r",stdin);
	freopen("maze1.out","w",stdout);
	init();
	spfa();
	solve();
	return 0;
}
