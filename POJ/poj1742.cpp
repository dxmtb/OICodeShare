/*
ID: dxmtb
PROG: poj1742 Coins
TIME: 2010.12.15
STATE: Solved
MEMO: dp+按余数划分
*/
#include <cstdio>
const int MAXM=100005;
const int MAXN=105;

int N,M;
int A[MAXN],C[MAXN];
bool f[MAXM];

int main()
{
	freopen("coins.in","r",stdin);
	freopen("coins.out","w",stdout);
	while(scanf("%d",&N))
	{
		scanf("%d",&M);
		if (N==0&&M==0)
			break;
		for(int i=0;i<N;i++)
			scanf("%d",A+i);
		for(int i=0;i<N;i++)
			scanf("%d",C+i);
		f[0]=true;
		for(int i=1;i<=M;i++)
			f[i]=false;
		for(int i=0;i<N;i++)
		{
			for(int v=0;v<A[i];v++)
			{
				int k=-1;
				for(int j=0;v+j*A[i]<=M;j++)
				if (f[v+j*A[i]])
				{
					k=j;	
					int t=C[i];
					while((t--)&&v+(++j)*A[i]<=M)
					{
						if (f[v+j*A[i]])
						{
							k=j;
							t=C[i];
						}
						else f[v+j*A[i]]=true;
					}
				}
			}				
		}
		int re=0;
		for(int i=1;i<=M;i++)
			if (f[i])
				re++;
		printf("%d\n",re);
	}	
	return 0;
}
