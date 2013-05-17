/*
ID: dxmtb
PROG: 多人背包
TIME: 2010.9.19
STATE: Solved
MEMO: dp
*/
#include <cstdio>
using namespace std;

const int MAXN=200,MAXK=55,MAXV=5005;
const int oo=0x7fffffff;

int d[2][MAXV+1][MAXK];
int K,V,N;

int main()
{
	freopen("bags.in","r",stdin);
	freopen("bags.out","w",stdout);
	scanf("%d%d%d",&K,&V,&N);
	for(int i=0;i<=V;i++)
		for(int j=0;j<K;j++)
			d[0][i][j]=d[1][i][j]=-oo;
	d[0][0][0]=d[1][0][0]=0;
	for(int i=1;i<=N;i++)
	{
		int v,w;
		scanf("%d%d",&v,&w);
#define dd d[i&1]
#define df d[1-(i&1)]
		for(int j=V;j>=v;j--)
			for(int k=0,a=0,b=0;k<K;k++)
				if (df[j-v][a]+w>df[j][b]) dd[j][k]=df[j-v][a++]+w;
				else dd[j][k]=df[j][b++];
		for(int j=v-1;j>=0;j--)
			for(int k=0;k<K;k++)
				dd[j][k]=df[j][k];
	}
	int re=0;
	for(int i=0;i<K;i++)
		re+=d[N&1][V][i];
	printf("%d\n",re);
	return 0;
}
