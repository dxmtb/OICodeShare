/*
ID: dxmtb
PROG: 路由选择问题
TIME: 2010.10.20
STATE: Solved
MEMO: 最短路与次短路
*/
#include <cstdio>
#include <cstring>
using namespace std;

const int MAXN=55;
const int oo=1e8;

int path[MAXN][MAXN],path2[MAXN][MAXN];
int N,S,T;
int bad[6];
int a[MAXN][MAXN],b[MAXN][MAXN];
int s0,s1,s2;

void floyd(int path[][MAXN])
{
	memset(path,0,sizeof(path));
	for(int k=0;k<N;k++)
		for(int i=0;i<N;i++)
		if (i!=k)
			for(int j=0;j<N;j++)
			if (j!=k&&j!=i&&b[i][k]+b[k][j]<b[i][j])
				b[i][j]=b[i][k]+b[k][j],path[i][j]=k;
}

int main()
{
	freopen("route.in","r",stdin);
	freopen("route.out","w",stdout);
	scanf("%d%d%d",&N,&S,&T);
	S--,T--;
	for(int i=0;i<N;i++)
		for(int j=0;j<N;j++)
		{
			scanf("%d",a[i]+j);
			if (i!=j&&!a[i][j])
				a[i][j]=oo;
		}
	memcpy(b,a,sizeof(a));
	floyd(path);
	s1=b[S][T];
	s2=oo;
	for(int u=path[S][T],v=T;u;v=u,u=path[S][u])
	{
		memcpy(b,a,sizeof(a));
		b[u][v]=b[v][u]=oo;
		floyd(path2);
		if (b[S][T]<s2)
			s2=b[S][T];
	}
	int p;
	scanf("%d",&p);
	for(int i=0;i<p;i++)
	{
		scanf("%d",bad+i);
		bad[i]--;
	}
	memcpy(b,a,sizeof(a));
	for(int i=0;i<p;i++)
		for(int j=0;j<N;j++)
			if (j!=bad[i])
				b[bad[i]][j]=b[j][bad[i]]=oo;
	floyd(path);
	s0=b[S][T];
	printf("%d %d %d\n",s0,s1,s2);
	return 0;
}
