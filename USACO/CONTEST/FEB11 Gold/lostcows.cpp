/*
PROG: lostcows
LANG: C++
ID: dxmtb1
*/
/*
TIME: 2011.02.11
STATE: Solved
MEMO: 图论
*/
#include <cstdio>
#include <cstring>
#include <queue>

using namespace std;

const int MAXN=205;

struct Node
{
	int v;
	Node *next;
	Node(int _v,Node *_next):v(_v),next(_next){}
}*adj[MAXN][MAXN]; //who came to i after hearing j

inline void addedge(int u,int sign,int v)
{
	adj[u][sign]=new Node(v,adj[u][sign]);
}

unsigned char afterhome[MAXN][MAXN][MAXN];
int next[MAXN][MAXN];
int S[MAXN][MAXN];
int N,M;

void bfs()
{
	queue<pair<int,int> >q;
	q.push(make_pair(0,0));
	memset(afterhome,-1,sizeof(afterhome));
	for(int i=0;i<N;i++)
		afterhome[i][0][0]=i;
	memset(next,-1,sizeof(next));
	while(q.size())
	{
		int a=q.front().first,b=q.front().second;
		q.pop();
		for(int sign=0;sign<M;sign++)
			for(Node *p1=adj[a][sign];p1;p1=p1->next)
				for(Node *p2=adj[b][sign];p2;p2=p2->next)
				{
					int v1=p1->v,v2=p2->v;
					if (v1>v2)
						swap(v1,v2);
					if ((v1||v2)&&next[v1][v2]==-1)
					{
						next[v1][v2]=sign;
						q.push(make_pair(v1,v2));
						for(int i=0;i<N;i++)
							afterhome[i][v1][v2]=afterhome[S[i][sign]][a][b];
					}
				}
	}
}

void print()
{
	bool havecow[MAXN];
	bool thavecow[MAXN];
	for(int i=0;i<N;i++)
		havecow[i]=true;
	while(true)
	{
		int a=0,b=0;
		for(int i=1;i<N;i++)
			if (havecow[i])
			{
				if (a) {b=i;break;}
				else a=i;
			}
		if (!a) break;
		if (a>b)
			swap(a,b);
		memset(thavecow,false,sizeof(thavecow));
		for(int i=0;i<N;i++)
			if (havecow[i])
				thavecow[afterhome[i][a][b]]=true;
		memcpy(havecow,thavecow,sizeof(havecow));
		while(true)
		{
			int sign=next[a][b];
			if (sign==-1) {printf("wrong!\n");}
			a=S[a][sign],b=S[b][sign];
			if (a>b)
				swap(a,b);
			printf("%d\n",sign+1);
			if (a==0&&b==0)
				break;
		}
	}
}

int main()
{
	freopen("lostcows.in","r",stdin);
	freopen("lostcows.out","w",stdout);
	scanf("%d%d",&N,&M);
	for(int j=0;j<M;j++)
		for(int i=0;i<N;i++)
		{
			scanf("%d",S[i]+j);
			S[i][j]--;
			addedge(S[i][j],j,i);
		}
	bfs();
	/*
	for(int i=0;i<N;i++)
		if (afterhome[i][0][0]!=i)
			printf("wrong!!\n");
	for(int i=0;i<N;i++)
		for(int v1=0;v1<N;v1++)
			for(int v2=v1;v2<N;v2++)
				if (v1||v2)
				if (afterhome[i][v1][v2]==-1)
				{
				//	printf("wrong %d %d %d",i,v1,v2);
				//	return 0;
				}
				else 
				{
					int a=S[v1][next[v1][v2]],
					    b=S[v2][next[v1][v2]];
					if(a>b)
						swap(a,b);
					if (afterhome[i][v1][v2]!=
					    afterhome[S[i][next[v1][v2]]][a][b])
					{
						printf("wrong %d %d %d",
							i,v1,v2);
						return 0;
					}
				}*/
	print();
	return 0;
}
