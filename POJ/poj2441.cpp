/*
  ID: dxmtb
  PROG: poj 2441
  TIME: 2010.6.28
  STATE: Solved
  MEMO: SRC
*/
#include <cstdio>
#include <cstring>
using namespace std;

const int MAXN=20;
const int a[MAXN+1]={1,2,4,8,16,32,64,128,256,512,1024,2048,4096,8192,16384,32768,65536,131072,262144,524288,1048576};

int n,m,re;
bool g[MAXN+1][MAXN+1];
int d[1<<MAXN]={1},z[1<<MAXN];

int main() 
{
	freopen("2441.in","r",stdin);
	freopen("2441.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1,t1,t2;i<=n;i++)
	{
		scanf("%d",&t1);
		while(t1--)scanf("%d",&t2),g[i][t2]=true;
	}
	for(int i=1;i<a[m];i++)
	{
		z[i]=z[i>>1]+(i&1);
		for(int t=i,j=0;t;t>>=1,j++)
			if(t&1&&g[z[i]][j+1])
				d[i]+=d[i^a[j]];
		if (z[i]==n)
			re+=d[i];
	}
	printf("%d\n",re);
	return 0;
}
