#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN=101,MAXINT=0x7ffff;

int w[MAXN][MAXN],n,ans=0;
bool is[MAXN][MAXN];

int main()
{
	freopen("cityroad.in","r",stdin);
	freopen("cityroad.out","w",stdout);
	scanf("%d",&n);
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
		{
			scanf("%d",&w[i][j]);
			if (w[i][j]>0)is[i][j]=true;
			else w[i][j]=MAXINT,is[i][j]=false;
		}
	for(int k=0;k<n;k++)
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
			if (i!=j)
				if (i!=k&&k!=j)
				if (w[i][k]+w[k][j]<=w[i][j])
					w[i][j]=w[i][k]+w[k][j],
					is[i][j]=is[j][i]=false;
	for(int i=0;i<n;i++)
		for(int j=i+1;j<n;j++)
			if (is[i][j])
				ans+=w[i][j];
	printf("%d\n",ans);
	for(int i=0;i<n;i++)
	{
		printf("%d",is[i][0]);
		for(int j=1;j<n;j++)
			printf(" %d",is[i][j]);
		printf("\n");
	}
	return 0;
}
