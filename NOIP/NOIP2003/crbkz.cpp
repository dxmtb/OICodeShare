/*
ID: dxmtb
PROG: NOIP2003 传染病控制
TIME: 2010.8.21
STATE: Solved
MEMO: 贪心+搜索
*/
#include <cstdio>
#include <queue>
using namespace std;

const int MAXN=300;

struct Node
{
	int v;
	Node *next;
	Node(int a,Node *b):v(a),next(b){}
};

int n,p;
Node *g[MAXN];
int child[MAXN],depth[MAXN],mdep[MAXN];
int best=1000;

inline void add(int a,int b)
{
	a--,b--;
	g[a]=new Node(b,g[a]);
	g[b]=new Node(a,g[b]);
}

void bfs()
{
	queue<int> q;
	q.push(0);
	depth[0]=1;
	while(!q.empty())
	{
		int u=q.front();q.pop();
		for(Node *p=g[u];p;p=p->next)
			if (!depth[p->v])
			{
				depth[p->v]=depth[u]+1;
				q.push(p->v);
			}
	}
}

void countchild(int u)
{
	for(Node *p=g[u];p;p=p->next)
		if (depth[p->v]==depth[u]+1)
		{
			countchild(p->v);
			if (mdep[p->v]+1>mdep[u])
				mdep[u]=mdep[p->v]+1;
			child[u]+=child[p->v];
		}
}

deque<int> q[MAXN+1];
void search_c(int dep,int ill)
{
	deque<int> *one=&q[dep],*two=&q[dep-1];
	int max=-1,former=-1;
	for(deque<int>::iterator it=two->begin();it!=two->end();
			it++)
		for(Node *p=g[*it];p;p=p->next)
			if (depth[p->v]==depth[*it]+1)
				if (child[p->v]>max||(child[p->v]==max&&mdep[p->v]>mdep[former]))
				{
					if (former!=-1)
						one->push_back(former);
					else one->push_back(p->v);
				}
	int size=one->size();
	if(size==0)
	{
		best=ill;
		return ;
	}
	search_c(dep+1,ill+size-1);
}
void greed()
{
	bfs();
	countchild(0);
	q[1].push_front(0);
	search_c(2,1);
}

void search(int dep,int ill)
{
	deque<int> *one=&q[dep],*two=&q[dep-1];
	if (ill>=best)return;
	one->clear();
	for(deque<int>::iterator it=two->begin();it!=two->end();
			it++)
		for(Node *p=g[*it];p;p=p->next)
			if (depth[p->v]==depth[*it]+1)
			one->push_back(p->v);
	int size=one->size();
	if (size==0)
	{
		best=ill;
//		printf("%d\n",best);
		return ;
	}
	for(int i=0;i<size;i++)
	{
		int temp=one->front();
		one->pop_front();
		search(dep+1,ill+size-1);
		one->push_back(temp);
	}
}

int main()
{
	freopen("epidemic.in","r",stdin);
	freopen("epidemic.out","w",stdout);
	scanf("%d%d",&n,&p);
	for(int i=0,a,b;i<p;i++)
	{
		scanf("%d%d",&a,&b);
		add(a,b);
	}
	greed();
//	printf("%d\n",best);
	search(2,1);
	printf("%d\n",best);
	return 0;
}


