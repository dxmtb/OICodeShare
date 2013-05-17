/*
ID: dxmtb
PROG: 线性规划与网络流24题 汽车加油行驶问题
TIME: 2011.02.09
STATE: Solved
MEMO: 最短路
*/
#include <cstdio>
#include <queue>
using namespace std;

const int MAXN=105,MAXK=15;
const int oo=0x7fffffff;
const int way[4][2]={{0,1},{0,-1},{-1,0},{1,0}};
int fee[4]={0,-100000,-100000,0};

struct Node
{
	int a,b,c;
	int *d;
	Node(int _a,int _b,int _c,int *_d):a(_a),b(_b),c(_c),d(_d){}
};

int N,K,A,B,C;
int dis[MAXN][MAXN][MAXK];
int g[MAXN][MAXN];

void spfa()
{
	for(int i=0;i<N;i++)
		for(int j=0;j<N;j++)
			for(int k=0;k<=K;k++)
				dis[i][j][k]=oo;
	dis[0][0][K]=0;
	deque<Node> q;
	q.push_back(Node(0,0,K,dis[0][0]+K));
	while(q.size())
	{
		Node u=q.front();q.pop_front();
		if (u.c==0)
		{
			int ndis=*(u.d)+A+C;
			u.c=K;
			u.d=u.d+K;
			if (*(u.d)>ndis)
			{
				*(u.d)=ndis;
				if (q.empty()||ndis>*(q.front().d))
					q.push_back(u);
				else q.push_front(u);
			}
		}
		else
		{
			for(int i=0;i<4;i++)
			{
				int nx=u.a+way[i][0],ny=u.b+way[i][1];
				if (nx>=0&&nx<N&&ny>=0&&ny<N)
				{
					int ndis=*u.d+fee[i];
					int nc;
					if (g[nx][ny]) nc=K,ndis+=A;
					else nc=u.c-1;
					int *nd=&dis[nx][ny][nc];
					if (ndis<*nd)
					{
						*nd=ndis;
						Node nN(nx,ny,nc,nd);
						if (q.empty()||
						    ndis>*(q.front().d))
							q.push_back(nN);
						else q.push_front(nN);
					}
				}
			}
		}
	}
}

int main()
{
	freopen("trav.in","r",stdin);
	freopen("trav.out","w",stdout);
	scanf("%d%d%d%d%d",&N,&K,&A,&B,&C);
	fee[1]=fee[2]=B;
	for(int i=0;i<N;i++)
		for(int j=0;j<N;j++)
			scanf("%d",g[i]+j);
	spfa();
	int re=oo;
	for(int i=0,*j=dis[N-1][N-1];i<=K;i++,j++)
		if (*j<re)
			re=*j;
	printf("%d\n",re);
	return 0;
}
