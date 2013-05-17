/*
ID: dxmtb
PROG: 医院设置
TIME: 2010.10.21
STATE: Solved
MEMO: floyd
*/
#include <cstdio>
using namespace std;

const int MAXN=105;
const int oo=100000000;

int dis[MAXN][MAXN];
int peo[MAXN];
int n;

int main()
{
	freopen("hospital.in","r",stdin);
	freopen("hospital.out","w",stdout);
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			if (i!=j)
				dis[i][j]=dis[j][i]=oo;
	for(int i=1;i<=n;i++)
	{
		int l,r;
		scanf("%d%d%d",peo+i,&l,&r);
		if (l)
			dis[i][l]=dis[l][i]=1;
		if (r)
			dis[i][r]=dis[r][i]=1;
	}
	for(int k=1;k<=n;k++)
		for(int i=1;i<=n;i++)
			if (i!=k)
			for(int j=1;j<=n;j++)
			if (i!=j&&k!=j)
				if (dis[i][j]>dis[i][k]+dis[k][j])
					dis[i][j]=dis[i][k]+dis[k][j];
	int re=oo;
	for(int i=1;i<=n;i++)
	{
		int t=0;
		for(int j=1;j<=n;j++)
			t+=dis[i][j]*peo[j];
		if (t<re)
			re=t;
	}
	printf("%d\n",re);
	return 0;
}
