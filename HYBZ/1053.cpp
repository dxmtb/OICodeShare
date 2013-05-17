/*
ID: dxmtb
PROG: POI2001 反素数
TIME: 2011.03.24
STATE: Solved
MEMO: 数学方法 搜索
*/
#include <cstdio>

const int MAXN=45000;

bool flag[MAXN];
int prime[MAXN],tot;
int re=1,g=1;
void init()
{
	for(int i=2;i<MAXN;i++)
		flag[i]=true;
	for(int i=2;i<MAXN;i++)
		if (flag[i])
		{
			prime[tot++]=i;
			for(int j=i+i;j<MAXN;j+=i)
				flag[j]=false;
		}
}

typedef long long s64;

int N;
void dfs(int dep,s64 multi,int before,int ng)
{
	if (multi>N)
		return ;
	if (ng>g || (ng==g && multi<re))
	{
		g=ng;
		re=multi;
	}
	multi*=prime[dep];
	for(int j=1;j<=before && multi<=N;j++,multi*=prime[dep])
		dfs(dep+1,multi,j,ng*(j+1));
}

int main()
{
	freopen("ant.in","r",stdin);
	freopen("ant.out","w",stdout);
	scanf("%d",&N);
	init();
	dfs(0,1,100,1);
	printf("%d\n",re);
	return 0;
}
