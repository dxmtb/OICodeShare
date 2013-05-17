/*
ID: dxmtb
PROG: ural1223
TIME: 2010.12.26
STATE: Solved
MEMO: dp
*/
#include <cstdio>
#include <cmath>
const int MAXN=1000;
const int LOGN=10;

int E,N;
int g[LOGN+1];

int main()
{
	freopen("eggle.in","r",stdin);
	freopen("eggle.out","w",stdout);
	while(true)
	{
		scanf("%d%d",&E,&N);
		if (E==0&&N==0)
			break;
		g[0]=0;
		int t=int(ceil(log(N+1.0)/log(2.0)));
		if (E>=t)
		{
			printf("%d\n",t);
			continue;
		}
		if (N==1)
		{
			printf("1\n");
			continue;
		}
		if (E==1)
		{
			printf("%d\n",N);
			continue;
		}
		for(int i=1;i<=E;i++)
			g[i]=1;
		for(int i=2;i<=N;i++)
		{
			g[E]+=g[E-1]+1;
			if (g[E]>=N)
			{
				printf("%d\n",i);
				break;
			}
			for(int j=E-1;j>=2;j--)
				g[j]+=g[j-1]+1;
			g[1]=i;
		}
	}
	return 0;
}

