/*
ID: dxmtb
PROG: 线性规划与网络流24题 孤岛营救问题
TIME: 2011.02.08
STATE: Solved
MEMO: 二进制表状态 最短路
*/
#include <cstdio>
#include <queue>
using namespace std;

const int MAXN=10,MAXS=(1<<9)-1;
const int oo=0x7fffffff;
const int way[4][2]={{0,-1},{0,1},{1,0},{-1,0}};

struct Node
{
	int x,y,S;
	Node(int _x,int _y,int _S):x(_x),y(_y),S(_S){}
	Node(){}
};

int g[MAXN][MAXN][MAXN][MAXN];

int dis[MAXN][MAXN][MAXS];
int key[MAXN][MAXN];
int N,M,P;

void spfa()
{
	deque<Node> q;
	for(int i=0;i<N;i++)
		for(int j=0;j<M;j++)
			for(int S=0;S<(1<<P);S++)
				dis[i][j][S]=oo;
	dis[0][0][key[0][0]]=0;
	q.push_back(Node(0,0,key[0][0]));
	while(q.size())
	{
		Node u=q.front();q.pop_front();
		typedef int T[10];
		T *gp=g[u.x][u.y];
		int dt=dis[u.x][u.y][u.S];
		for(int i=0;i<4;i++)
		{
			int nx=u.x+way[i][0],ny=u.y+way[i][1];
			if (nx>=0&&ny>=0&&nx<=N&&ny<=M)
			{
				int G=gp[nx][ny];
				if (G)
				{
					if (G<=P)
						if (!(u.S&(1<<(G-1))))
							continue;
					int nS=u.S | (key[nx][ny]);
					int &ndis=dis[nx][ny][nS];
					if (ndis>dt+1)
					{
						ndis=dt+1;
						q.push_back(Node(nx,ny,nS));
					}
				}
			}
		}
	}
}

int main()
{
	freopen("rescue.in","r",stdin);
	freopen("rescue.out","w",stdout);
	scanf("%d%d%d",&N,&M,&P);
	for(int i=0;i<N-1;i++)
		for(int j=0;j<M;j++)
			g[i][j][i+1][j]=g[i+1][j][i][j]=P+1;
	for(int i=0;i<N;i++)
		for(int j=0;j<M-1;j++)
			g[i][j+1][i][j]=g[i][j][i][j+1]=P+1;
	int K;	
	scanf("%d",&K);
	while(K--)
	{
		int x1,y1,x2,y2,G;
		scanf("%d%d%d%d%d",&x1,&y1,&x2,&y2,&G);
		x1--,y1--,x2--,y2--;
		g[x1][y1][x2][y2]=g[x2][y2][x1][y1]=G;
	}
	scanf("%d",&K);
	while(K--)
	{
		int x,y,Q;
		scanf("%d%d%d",&x,&y,&Q);
		x--,y--;
		key[x][y]|=(1<<(Q-1));
	}
	spfa();
	int re=oo,*disg=dis[N-1][M-1];
	for(int S=0;S<(1<<P);S++)
		if (disg[S]<re)
			re=disg[S];
	if (re==oo) printf("-1\n");
	else printf("%d\n",re);
	return 0;
}
