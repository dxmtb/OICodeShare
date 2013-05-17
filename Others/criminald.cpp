/*
ID: dxmtb
PROG: 罪犯问题D
TIME: 2010.10.19
STATE: Solved
MEMO: 构图
*/
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <queue>
#include <iostream>
using namespace std;

const int MAXN=50005;

struct Node
{
	int v,w;
	Node *next;
	Node(int a,int b,Node *c):v(a),w(b),next(c){}
};

short int sta[MAXN];
int N,M;
Node *adj[MAXN];

queue<int> q;

void spfa()
{
	while(!q.empty())
	{
		int u=q.front();q.pop();
		for(Node *p=adj[u];p;p=p->next)
		if (sta[p->v]==-1)
		{
			sta[p->v]=sta[u]^p->w;
			q.push(p->v);
		}
	}
}	

inline void add(int a,int b)
{
	adj[a]=new Node(abs(b),b>0,adj[a]);
	if (sta[a]!=-1) q.push(a);
	adj[abs(b)]=new Node(a,b>0,adj[abs(b)]);
	if (sta[abs(b)]!=-1) q.push(abs(b));
	spfa();
}

int main()
{
	freopen("criminald.in","r",stdin);
	freopen("criminald.out","w",stdout);
	scanf("%d%d",&N,&M);
	memset(sta,-1,sizeof(sta));
	for(int i=0;i<M;i++)
	{
		int T;
		scanf("%d",&T);
		sta[T]=1;
		q.push(T);
	}
	spfa();
	while(true)
	{
		char ch;
		int t1,t2;
		do ch=getchar();
		while(ch!='A'&&ch!='S'&&ch!='E');
		if (ch=='E')
			break;
		if (ch=='A')
		{
			scanf("%d",&t1);
			switch (sta[t1])
			{
				case -1:printf("Unknown\n");break;
				case 1:printf("Yes\n");break;
				case 0:printf("No\n");break;
				default:cerr<<"wrong!\n";
			}
		}
		else if (ch=='S')
		{
			scanf("%d%d",&t1,&t2);
			add(t1,t2);
		}
	}
	return 0;
}
