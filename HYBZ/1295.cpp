/*
ID: dxmtb
PROG: [SCOI2009]最长距离
TIME: 2011.03.24
STATE: Solved
MEMO: 最短路
*/
#include <cstdio>
#include <queue>
#include <cmath>
using namespace std;

const int MAXN=35;
const int oo=0x7fffffff/2;
const int way[4][2]={{0,1},{0,-1},{1,0},{-1,0}};

int N,M,T;
char str[MAXN][MAXN];

deque<pair<int,int> > q;
int dis[MAXN][MAXN];
void bfs(int x,int y)
{
	for(int i=0;i<N;i++)
		for(int j=0;j<M;j++)
			dis[i][j]=oo;
	dis[x][y]=(str[x][y]=='1');
	q.push_back(make_pair(x,y));
	while(q.size())
	{
		int nx=q.front().first,ny=q.front().second;
		q.pop_front();
		for(int i=0;i<4;i++)
		{
			x=nx+way[i][0],y=ny+way[i][1];
			if (x>=0 && x<N && y>=0 && y<M && dis[x][y]==oo)
			{
				dis[x][y]=dis[nx][ny]+(str[x][y]=='1');
				if (dis[x][y]<=T)
				{
					if (q.empty() || dis[x][y]<=dis[q.front().first][q.front().second])
						q.push_front(make_pair(x,y));
					else 
						q.push_back(make_pair(x,y));
				}
			}
		}
	}
}

double getdis(int a,int b,int c,int d)
{
	int x=a-c,y=b-d;
	return sqrt(x*x+y*y);
}

void Max(double &a,const double &b)
{
	if (b>a)
		a=b;
}

int main()
{
	scanf("%d%d%d",&N,&M,&T);
	for(int i=0;i<N;i++)
		scanf(" %s",str[i]);
	double re=0;
	for(int i=0;i<N;i++)
		for(int j=0;j<M;j++)
		{
			bfs(i,j);
			for(int x=0;x<N;x++)
				for(int y=0;y<M;y++)
					if (dis[x][y]<=T)
						Max(re,getdis(i,j,x,y));
		}
	printf("%.6lf\n",re);
	return 0;
}
