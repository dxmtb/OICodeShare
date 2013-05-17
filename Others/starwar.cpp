/*
ID: dxmtb
PROG: 星际争霸
TIME: 2010.4.21
STATE: Solved
MEMO: 最大流最小割
*/
#include <cstdio>
#include <cstring>
#include <cmath>
#include <queue>
using namespace std;

const int MAXN=60,MAXINT=0x7fffffff;

int n,m,r,lv[MAXN];
int c[MAXN][MAXN],z[MAXN][3],maxflow=0;
double dis[MAXN];

void init()
{
	scanf("%d%d%d",&n,&m,&r);
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d%d",&z[i][0],&z[i][1],&z[i][2]);
		dis[i]=sqrt(double(z[i][0]*z[i][0]+z[i][1]*z[i][1]+z[i][2]*z[i][2]));
		if (dis[i]>r)
			c[i][n+1]=MAXINT;
	}
	for(int i=0;i<m;i++)
	{
		int a,b;
		scanf("%d%d",&a,&b);
		c[a][b]=c[b][a]=(z[a][0]-z[b][0])*(z[a][0]-z[b][0])+
			(z[a][1]-z[b][1])*(z[a][1]-z[b][1])+(z[a][2]-z[b][2])*(z[a][2]-z[b][2]);
	}	
}

bool lable()
{
	memset(lv,-1,sizeof(lv));
	lv[0]=0;
	queue<int> q;
	q.push(0);
	while (!q.empty())
	{
		int now=q.front();
		q.pop();
		for(int i=1;i<=n+1;i++)
			if (c[now][i]>0&&lv[i]==-1)
			{
				lv[i]=lv[now]+1;
				q.push(i);
			}
		if (lv[n+1]>0)return true;
	}
	return false;
}

void agument()
{
	int stack[MAXN],top=0;
	stack[++top]=0;
	while (top)
	{
		int now=stack[top];
		if (now==n+1)
		{
			int delta=MAXINT;
			for(int v=top-1;v;v--)if (c[stack[v]][stack[v+1]]<delta)delta=c[stack[v]][stack[v+1]];
			for(int v=top-1;v;v--)
			{
				c[stack[v]][stack[v+1]]-=delta;
				c[stack[v+1]][stack[v]]+=delta;
				if (c[stack[v]][stack[v+1]]==0)top=v;
			}
			maxflow+=delta;
		}
		else
		{
			int i;
			for(i=0;i<=n+1;i++)
				if (c[now][i]>0&&lv[i]==lv[now]+1)
					break;
			if (i==n+2)
				top--,lv[now]=-1;
			else
				stack[++top]=i;
		}
	}
}

int main() 
{
	freopen("starwar.in","r",stdin);
	freopen("starwar.out","w",stdout);
	init();
	while (lable())
		agument();
	printf("%d\n",maxflow);
	return 0;
}
