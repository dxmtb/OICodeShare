/*
ID: dxmtb
PROG: 数学家旅游
TIME: 2010.10.31
STATE: Solved
MEMO: 搜索
*/
#include <cstdio>
using namespace std;

const int MAXN=1000;
const int way[4][2]={{0,1},{0,-1},{1,0},{-1,0}};//n s e w 
const int op[4]={1,0,3,2};

int n,re;
bool g[MAXN*2][MAXN*2];
char path[MAXN*MAXN];

#define f(t) ((t)+500)
//#define max(a,b) ((a)>(b)?(a):(b))
//#define min(a,b) ((a)<(b)?(a):(b))

inline void sign(int x,int y,int i,int step,bool flag)
{
	int nx=x,ny=y;
	for(int j=0;j<step;j++)
	{
		nx+=way[i][0],ny+=way[i][1];
		g[f(nx)][f(ny)]=flag;
	}
}

inline int sum(int l,int r)
{
	return (l+r)*(r-l+1)/2;
}

void search(int x,int y,int step,int di)
{
	if (step>n+1) return ;
	if (sum(step,n)<x+y)
		return ;
	if (step!=1&&x==0&&y==0)
	{
		if (step==n+1)
		{
			re++;
			for(int i=1;i<step;i++)
				printf("%c",path[i]);
			printf("\n");
		}
		return ;
	}
	for(int i=0;i<4;i++)
		if (di==-1||(i!=di&&i!=op[di]))
		{
			bool flag=true;
			int nx=x,ny=y;
			for(int j=0;j<step&&flag;j++)
			{
				nx+=way[i][0],ny+=way[i][1];
				flag=flag&g[f(nx)][f(ny)];
			}
			if (flag)
			{
				sign(x,y,i,step,false);
				switch (i)
				{
					case 0:path[step]='n';break;
					case 1:path[step]='s';break;
					case 2:path[step]='e';break;
					case 3:path[step]='w';break;
					default:printf("wrong!!\n");
				}
				search(nx,ny,step+1,i);
				sign(x,y,i,step,true);
			}
		}
}	


int main()
{
	freopen("golygon.in","r",stdin);
	freopen("golygon.out","w",stdout);
	scanf("%d",&n);
	int p;
	scanf("%d",&p);
	for(int i=0;i<MAXN*2;i++)
		for(int j=0;j<MAXN*2;j++)
			g[i][j]=true;
	for(int i=0,x,y;i<p;i++)
	{
		scanf("%d%d",&x,&y);
		g[f(x)][f(y)]=false;
	}
	search(0,0,1,-1);
	printf("Found %d golygon(s).\n",re);
	return 0;
}

