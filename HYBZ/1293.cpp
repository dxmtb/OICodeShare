/*
ID: dxmtb
PROG: [SCOI2009]生日礼物
TIME: 2011.03.23
STATE: Solved
MEMO: 扫描
*/
#include <cstdio>
#include <queue>
using namespace std;

const int MAXK=65,MAXN=1000005;

struct Node
{
	int pos,i,j;
	inline Node(const int &a,const int &b,const int &c):
		pos(a),i(b),j(c){}
};

int pool[MAXN];
int *adj[MAXN];

inline bool operator < (const Node &a,const Node &b)
{
	return a.pos>b.pos;
}

int size[MAXK];
priority_queue<Node> q;

int N,K;
int main()
{
	freopen("1293.in","r",stdin);
	scanf("%d%d",&N,&K);
	for(int i=1,*mem=pool;i<=K;i++)
	{
		scanf("%d",size+i);
		adj[i]=mem;
		for(int j=0;j<size[i];j++)
			scanf("%d",mem+j);
		mem+=size[i];
	}	
	int maxr=0;
	for(int i=1;i<=K;i++)
	{
		if (adj[i][0]>maxr)
			maxr=adj[i][0];
		q.push(Node(adj[i][0],i,0));
	}
	int re=0x7fffffff;
	while(true)
	{
		int pos=q.top().pos;
		int nre=maxr-pos;
		if (nre<re)
			re=nre;
		do
		{
			int ni=q.top().i,nj=q.top().j+1;
			if (nj==size[ni])
				goto OUT;
			q.push(Node(adj[ni][nj],ni,nj));
			if (adj[ni][nj]>maxr)
				maxr=adj[ni][nj];
			q.pop();
		}while(q.top().pos==pos);
	}
OUT:
	printf("%d\n",re);
	return 0;
}
