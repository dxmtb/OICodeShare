/*
PROG: cowlpha
LANG: C++
ID: dxmtb1
*/
/*
TIME: 2011.02.11
STATE: Solved
MEMO: dp
*/
#include <cstdio>
using namespace std;

const int MAXN=252;
const int MO=97654321;

struct Node
{
	int v;
	Node *next;
	Node (int _v,Node *_next):v(_v),next(_next){}
}*adj[52];

int d[MAXN][MAXN][52];
int U,L,P;
bool used[MAXN];
int link[MAXN],size;

inline void addedge(int u,int v)
{
	adj[u]=new Node(v,adj[u]);
	used[u]=used[v]=true;
}

int main()
{
	freopen("cowlpha.in","r",stdin);
	freopen("cowlpha.out","w",stdout);
	scanf("%d%d%d",&U,&L,&P);
	while(P--)
	{
		char str[10];
		int u,v;
		scanf("%s",str);
		if (str[0]>='a'&&str[0]<='z')
			u=str[0]-'a';
		else u=str[0]-'A'+26;
		if (str[1]>='a'&&str[1]<='z')
			v=str[1]-'a';
		else v=str[1]-'A'+26;
		addedge(u,v);
		if (u>=26)
			d[0][1][u]=1;
		else d[1][0][u]=1;
	}
	for(int i=0;i<52;i++)
		if (used[i])
			link[size++]=i;
	for(int i=0;i<=L;i++)
		for(int j=0;j<=U;j++)
			for(int K=0;K<size;K++)
			{
				int k=link[K];
				if (d[i][j][k])
				{
					int dt=d[i][j][k];
					for(Node *p=adj[k];p;p=p->next)
					{
						int *q;
						if (p->v>=26)
							q=&d[i][j+1][p->v];
						else 
							q=&d[i+1][j][p->v];
						*q+=dt;
						*q%=MO;
					}
				}
			}
	int re=0;
	for(int k=0;k<52;k++)
	{
		re+=d[L][U][k];
		re%=MO;
	}
	printf("%d\n",re);
	return 0;
}
