/*
ID: dxmtb1
PROG: spin
LANG: C++
*/
#include <cstdio>
#include <cstring>
using namespace std;

const int n=5;

int be[n][n],le[n][n];
int w[n],v[n];

int main()
{
	freopen("spin.in","r",stdin);
	freopen("spin.out","w",stdout);
	for(int i=0;i<n;i++)
	{
		scanf("%d%d",v+i,w+i);
		for(int j=0;j<w[i];j++)
			scanf("%d%d",&be[i][j],&le[i][j]);
	}
	for(int t=0;t<360;t++)
	{
		bool can[360];
		memset(can,true,sizeof(can));
		int timer=360;
		for(int i=0;i<n;i++)
		{
			bool tcan[360];
			memset(tcan,false,sizeof(tcan));
			for(int j=0;j<w[i];j++)
			{
				int l=(be[i][j]+v[i]*t)%360,r=(be[i][j]+v[i]*t+le[i][j])%360;
				if (r<l)
				{
					for(int k=0;k<=r;k++)
						tcan[k]=true;
					for(int k=l;k<360;k++)
						tcan[k]=true;
				}
				else 
					for(int k=l;k<=r;k++)
						tcan[k]=true;
			}
			for(int j=0;j<360;j++)
				if (!tcan[j]&&can[j])
					can[j]=false,timer--;
			if (timer==0)
				break;
		}
		if (timer)
		{
			printf("%d\n",t);
			return 0;	
		}
	}
	printf("none\n");
	return 0;
}
