/*
ID: dxmtb1
PROG: camelot
LANG: C++
*/
#include <cstdio>
#include <queue>
#include <cstring>
using namespace std;

#define abs(x) ((x)<0)?(-(x)):(x)
struct Node
{
	int x,y;
	Node(int a=0,int b=0):x(a),y(b){}
};

const int MAXR=26,MAXC=40;
const int way[8][2]={{1,2},{2,1},{1,-2},{-1,2},{-2,1},{2,-1},{-1,-2},{-2,-1}};
const int oo=0x7fffffff;

int R,C,n;
Node king,knight[MAXR*MAXC];

int dis[MAXR][MAXC][MAXR][MAXC];

void spfa(Node s)
{
	queue<Node> q; 
	q.push(s);
	dis[s.x][s.y][s.x][s.y]=0;
	while(!q.empty())
	{
		Node now=q.front();
		q.pop();
		for(int i=0;i<8;i++)
		{
			int x=now.x+way[i][0],y=now.y+way[i][1];
			if (x>=0&&x<R&&y>=0&&y<C&&dis[s.x][s.y][x][y]==-1)
			{
				q.push(Node(x,y));
				dis[s.x][s.y][x][y]=dis[s.x][s.y][now.x][now.y]+1;
			}
		}
	}
}

int main()
{
	freopen("camelot.in","r",stdin);
	freopen("camelot.out","w",stdout);
	scanf("%d%d\n",&C,&R);
	scanf("%c%d\n",&king.x,&king.y);
	king.x-='A';king.y--;
	for(n=0;scanf("%c %d ",&knight[n].x,&knight[n].y)!=EOF;
			knight[n].x-='A',knight[n++].y--);
	if (!n){printf("0\n");return 0;}
	memset(dis,-1,sizeof(dis));
	for(int i=0;i<R;i++)
		for(int j=0;j<C;j++)
			spfa(Node(i,j));
	int re=oo;
	for(int i=0;i<R;i++)
		for(int j=0;j<C;j++)
		{
			int t1=0;
			bool flag=false;
			for(int k=0;k<n;k++)
			if (dis[knight[k].x][knight[k].y][i][j]!=-1)
				t1+=dis[knight[k].x][knight[k].y][i][j];
			else {flag=true;break;}
			if (flag)continue;
			int t2=max(abs(king.x-i),abs(king.y-j))+t1;
			if (t2<re)
				re=t2;
			if (t1>re)
				continue;
			for(int a=max(king.x-2,0);a<R&&a<king.x+3;a++)
				for(int b=max(king.y-2,0);b<C&&b<king.y+3;b++)
					for(int k=0;k<n;k++)
					if (dis[knight[k].x][knight[k].y][a][b]!=-1)
					{
						int temp=t1;
						Node now=knight[k];
						temp-=dis[now.x][now.y][i][j];
						temp+=dis[now.x][now.y][a][b];
						temp+=dis[a][b][i][j];
						int p=abs(king.x-a),q=abs(king.y-b);
						temp+=max(p,q);
						if (temp<re)
							re=temp;
					}
		}
	printf("%d\n",re);
	return 0;
}
