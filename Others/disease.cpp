/*
ID: dxmtb
PROG: 疾病管理
TIME: 2010.9.9
STATE: Solved
MEMO: 枚举
*/
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

const int MAXN=1005,MAXD=15;
const int MAXS=(1<<MAXD);

int N,K,D,S,re;
int di[MAXN+1];
int tone[MAXS];

int main()
{
	freopen("disease.in","r",stdin);
	freopen("disease.out","w",stdout);
	scanf("%d%d%d",&N,&D,&K);
	if (K==D)
	{
		printf("%d\n",N);
		return 0;
	}
	for(int i=1;i<=N;i++)
	{
		int p;
		scanf("%d",&p);
		for(int j=0;j<p;j++)
		{
			int k;
			scanf("%d",&k);
			di[i]=di[i]|(1<<(k-1));
		}
	}
	S=(1<<D);
	tone[0]=0;
	for(int i=1;i<S;i++)
		tone[i]=tone[(i>>1)]+(i&1);
	for(int i=0;i<S;i++)
		if (tone[i]<=K)
		{
			int timer=0;
			for(int j=1;j<=N;j++)
				if ((i|di[j])==i)
					timer++;
			if (timer>re)
				re=timer;
		}
	printf("%d\n",re);
	return 0;
}
