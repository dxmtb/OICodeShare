/*
ID: dxmtb
PROG: NOI2002 贪吃的九头龙
TIME: 2011.02.24
STATE: Solved
MEMO: 树形dp
*/
#include <cstdio>
#include <queue>
#include <cstring>
using namespace std;
const int MAXN=305;
const int oo=100000000;

int N,M,K;
int d[MAXN][MAXN][2];
int child[MAXN],sibling[MAXN],father[MAXN];
int w[MAXN][MAXN],ww[MAXN][MAXN];

bool vis[MAXN];
void bfs()
{
	queue<int> q;
	int u,former;
	q.push(1);vis[1]=true;
	while(q.size())
	{
		u=q.front();q.pop();
		former=0;
		for(int i=1;i<=N;i++)
			if (w[u][i]!=oo && !vis[i])
			{
				vis[i]=true;father[i]=u;
				if (former==0)
					child[u]=i;
				else
					sibling[former]=i;
				q.push(i);
				former=i;
			}
		if (!former && sibling[u]==0)
		{
			d[u][0][0]=ww[father[u]][u];
			d[u][0][1]=0;
			d[u][1][0]=0;
			d[u][1][1]=w[father[u]][u];
		}
	}
}

inline void Min(int &a,int b)
{
	if (b<a)
		a=b;
}

inline int min(int a,int b)
{
	return a<b?a:b;
}

void dp(int i,int j,int s)
{
	if (d[i][j][s]!=oo || !i) return ;
	if (s==1)
	{
		for(int k=0;k<=j;k++)
		{
			dp(sibling[i],k,1);
			dp(child[i],j-k,0);
			if (j!=k) 
			{
				dp(child[i],j-k-1,1);
				Min(d[i][j][1],d[sibling[i]][k][1]+
				min(d[child[i]][j-k][0],
				    d[child[i]][j-k-1][1]+w[i][father[i]]));
			}
			else
			{
				Min(d[i][j][1],d[sibling[i]][k][1]+
				d[child[i]][j-k][0]);
			}
			if (!sibling[i])
				break;
		}
	}
	else
	{
		for(int k=0;k<=j;k++)
		{
			dp(sibling[i],k,0);
			dp(child[i],j-k,0);
			if (j!=k)
			{
				dp(child[i],j-k-1,1);
				Min(d[i][j][0],d[sibling[i]][k][0]+
				min(d[child[i]][j-k][0]+ww[i][father[i]],
				    d[child[i]][j-k-1][1]));
			}
			else 
			{
				Min(d[i][j][0],d[sibling[i]][k][0]+
				d[child[i]][j-k][0]+ww[i][father[i]]);
			}
			if (!sibling[i])
				break;
		}
	}
	if (d[i][j][s]==oo)
		d[i][j][s]<<=1;
//	printf("%d %d %d %d\n",i,j,s,d[i][j][s]);
}

int main()
{
	freopen("dragon.in","r",stdin);
	freopen("dragon.out","w",stdout);
	scanf("%d%d%d",&N,&M,&K);
	for(int i=1;i<=N;i++)
		for(int j=1;j<=N;j++)
			w[i][j]=oo;
	for(int i=N;i;i--)
	{
		int a,b,c;	
		scanf("%d%d%d",&a,&b,&c);
		w[a][b]=w[b][a]=c;
	}
	if (M==2)
		memcpy(ww,w,sizeof(w));
	if (M+K-1>N)
	{
		printf("-1\n");
		return 0;
	}
	for(int i=0;i<=N;i++)
		for(int j=0;j<K;j++)
			d[i][j][0]=d[i][j][1]=oo;
	bfs();
	d[0][0][0]=d[0][0][1]=0;
	dp(child[1],K-1,1);
	printf("%d\n",d[child[1]][K-1][1]);
	return 0;
}
