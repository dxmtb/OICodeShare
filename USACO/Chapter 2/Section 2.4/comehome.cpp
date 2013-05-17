/*
ID: dxmtb1
LANG: C++
TASK: comehome
*/
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

const int MAXN=53,MAXINT=0x7fffffff;

struct Edge
{
	int v,w;
	Edge *next;
	Edge(int x,int y,Edge *n):v(x),w(y),next(n){}
};

Edge *adj[MAXN];
int dis[MAXN];

inline int get(char ch)
{
	if (ch>='A'&&ch<='Z')
		return ch-'A'+26;
	else return ch-'a';
}

void init()
{
	int p;
	char ch1,ch2;	
	scanf("%d",&p);
	for(int i=0;i<p;i++)
	{
		scanf("%c",&ch1);
		int x;
		scanf("%c %c%d",&ch1,&ch2,&x);
		int a=get(ch1),b=get(ch2);
		adj[a]=new Edge(b,x,adj[a]);
		adj[b]=new Edge(a,x,adj[b]);
	}
	for(int i=0;i<MAXN;i++)
		dis[i]=MAXINT;
}

void spfa(int s)
{
	bool in[MAXN];
	memset(in,false,sizeof(in));
	queue<int> q;
	q.push(s);
	in[s]=true;
	dis[s]=0;
	while (!q.empty())
	{
		int u=q.front();
		q.pop();
		in[u]=false;
		for(Edge *p=adj[u];p;p=p->next)
		{
			int v=p->v,w=p->w;
			if (dis[u]+w<dis[v])
			{
				dis[v]=dis[u]+w;
				if(!in[v])
				{
					q.push(v);
					in[v]=true;
				}
			}
		}
	}
}

void print()
{
	int min=MAXINT;
	char re='\0';
	for(char ch='A';ch<='Y';ch++)
		if (dis[get(ch)]<min)
		{
			min=dis[get(ch)];
			re=ch;
		}
	printf("%c %d\n",re,min);
}

int main()
{
	freopen("comehome.in","r",stdin);
	freopen("comehome.out","w",stdout);
	init();
	spfa(get('Z'));
	print();
	return 0;
}
