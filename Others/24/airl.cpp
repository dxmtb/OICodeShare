#include <cstdio>
#include <cstring>
#include <queue>
#include <string>
#include <map>
using namespace std;

const int MAXN=200;
const int oo=0x7fffffff;

struct Node
{
	int v,c,w;
	Node *next,*back;
	Node(){}
	Node(int _v,int _c,int _w,Node *_next,Node *_back=NULL):
		v(_v),c(_c),w(_w),next(_next),back(_back){}
}*adj[MAXN],dist[MAXN*10],*mem=dist;

inline void addedge(int u,int v,int c,int w)
{
	adj[u]=new (mem++) Node(v,c,w,adj[u]);
	adj[v]=new (mem++) Node(u,0,-w,adj[v],adj[u]);
	adj[u]->back=adj[v];
}

int S,T,piS,mincost,maxflow;
int N,M;

inline bool label()
{
	deque<int> q;
	int dis[MAXN],dt;
	for(int i=S;i<=T;i++)
		dis[i]=oo;
	dis[T]=0;
	q.push_back(T);
	while(q.size())
	{
		int u=q.front();q.pop_front();
		for(Node *p=adj[u];p;p=p->next)
			if (p->back->c && (dt=dis[u]-p->w)<dis[p->v])
			{
				dis[p->v]=dt;
				if (q.size() && dt < dis[q.front()])
					q.push_front(p->v);
				else q.push_back(p->v);
			}
	}
	for(int i=S;i<=T;i++)
		for(Node *p=adj[i];p;p=p->next)
			p->w += dis[p->v]-dis[i];
	piS+=dis[S];
	return dis[S]<oo;
}

inline int min(int a,int b)
{
	return a>b?b:a;
}

bool vis[MAXN];
inline int augment(int u,int m)
{
	if (u==T)
	{
		mincost += m*piS;
		maxflow += m;
		return m;
	}
	int l=m;
	vis[u]=true;
	for(Node *p=adj[u];p;p=p->next)
		if (!p->w && p->c && !vis[p->v])
		{
			int d=augment(p->v,min(p->c,l));
			p->c-=d;p->back->c+=d;
			l-=d;
			if (!l)
				break;
		}
	return m-l;
}

inline void solve()
{
	while(label())
		do memset(vis,false,sizeof(vis));
		while(augment(S,oo));
}

map<string,int> s1;
map<int,string> s2;

inline void print()
{
	printf("%d\n",-mincost);
	int S1=0,S2=0;
	int next[MAXN];
	for(Node *p=adj[S+1];p;p=p->next)
		if (!p->c)
		{
			if (S1==0) S1=(p->v+1)/2;
			else 
			{
				S2=(p->v+1)/2;
				break;
			}
		}
	if (S1==S2)
	{
		printf("%s\n%s\n%s\n",s2[1].c_str(),s2[S1].c_str(),
				      s2[1].c_str());
		return ;
	}
	for(int i=2;i<N;i++)
		for(Node *p=adj[i*2];p;p=p->next)
			if (p->v>i*2&&p->c==0)
			{
				next[i]=(p->v+1)/2;
				break;
			}
	printf("%s\n",s2[1].c_str());
	while(S1!=N)
	{
		printf("%s\n",s2[S1].c_str());
		S1=next[S1];
	}
	printf("%s\n",s2[N].c_str());
	vector<int> re;
	while(S2!=N)
	{
		re.push_back(S2);
		S2=next[S2];
	}
	for(int i=re.size()-1;i>=0;i--)
		printf("%s\n",s2[re[i]].c_str());
	printf("%s",s2[1].c_str());
}

int main()
{
	freopen("airl.in","r",stdin);
	freopen("airl.out","w",stdout);
	scanf("%d%d",&N,&M);
	for(int i=1;i<=N;i++)
	{
		char str[20];
		scanf("%s",str);
		s1[string(str)]=i;
		s2[i]=string(str);
	}
	S=1,T=2*N-1;
	while(M--)
	{
		char str1[20],str2[20];
		scanf("%s%s",str1,str2);
		int u=s1[str1],v=s1[str2];
		if (u>v)
			swap(u,v);
		addedge(2*u,2*v-1,1,0);
		addedge(2*u,2*v-1,1,0);
	}
	addedge(1,2,2,-1);
	for(int i=2;i<N;i++)
		addedge(i*2-1,i*2,1,-1);
	solve();
	if (maxflow!=2)
		printf("No Solution!\n");
	else print();
	return 0;
}
