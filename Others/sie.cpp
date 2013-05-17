/*
ID: dxmtb
PROG: 公路网
TIME: 2010.10.21
STATE: Solved
MEMO: 枚举
*/
#include <cstdio>
using namespace std;

const int MAXN=205;

int n,dis[MAXN][MAXN];

int main()
{
	freopen("sie.in","r",stdin);
	freopen("sie.out","w",stdout);
	scanf("%d",&n);
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
			scanf("%d",dis[i]+j);
	for(int i=0;i<n;i++)
		for(int j=i+1;j<n;j++)
		{
			int t=0;
			for(int k=0;k<n&&!t;k++)
				if (k!=i&&k!=j)
					if (dis[i][k]+dis[k][j]==dis[i][j])
						t++;
			if (!t)
				printf("%d %d\n",i+1,j+1);
		}
	return 0;
}
