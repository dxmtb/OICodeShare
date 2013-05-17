/*
ID: dxmtb
PROG: APIO2010 巡逻
TIME: 2010.8.5
STATE: Solved
MEMO: dp求K个最长链
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN=100000,MAXK=2;

struct Node
{
	int v;
	Node *next;
	Node(int a,Node *b):v(a),next(b){}
}*adj[MAXN+1];

int n,K;
int d[MAXN+1][MAXK+1][3];

void dp(int now,int father)
{
	for(Node *p=adj[now];p;p=p->next)
		if (p->v!=father)
		{
			int v=p->v;
			dp(v,now);
			int dc[MAXK+1][3];
			memcpy(dc,d[now],sizeof(dc));
			for(int i=0;i<=K;i++)
				for(int j=0;j<=i;j++)
				{
					d[now][i][0]=max(d[now][i][0],d[v][j][0]+dc[i-j][0]);
					if (i-j>=1)d[now][i][0]=max(d[now][i][0],d[v][j][1]+dc[i-j-1][1]+1);
					d[now][i][1]=max(d[now][i][1],d[v][j][1]+dc[i-j][0]+1);
					d[now][i][1]=max(d[now][i][1],d[v][j][0]+dc[i-j][1]);
				}
		}
}

int main()
{
	freopen("patrol.in","r",stdin);
	freopen("patrol.out","w",stdout);
	scanf("%d%d",&n,&K);
	for(int i=0,a,b;i<n;i++)
	{
		scanf("%d%d",&a,&b);
		adj[a]=new Node(b,adj[a]);
		adj[b]=new Node(a,adj[b]);
	}	
	dp(1,0);
	printf("%d\n",2*(n-1)-d[1][K][0]+K);
	return 0;
}
