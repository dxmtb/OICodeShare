/*
ID: dxmtb
PROG: Mobile Service
TIME: 2010.11.11
STATE: Solved
MEMO: ¶¯Ì¬¹æ»®
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXL=205,MAXN=1005,oo=100000000;

int d[2][MAXL][MAXL],c[MAXL][MAXL],v[MAXN];
int n,l,re=oo;

int main()
{
	freopen("service.in","r",stdin);
	freopen("service.out","w",stdout);
	scanf("%d%d",&l,&n);
	for(int i=1;i<=l;i++)
		for(int j=1;j<=l;j++)
			scanf("%d",c[i]+j);
	for(int i=1;i<=n;i++)
		scanf("%d",v+i);
	memset(d,-1,sizeof(d));
	d[0][1][2]=0;
	v[0]=3;
	for(int i=0;i<=n;i++)
	{
		int (*f)[205]=d[(i&1)],(*g)[205]=d[((i+1)&1)];
		for(int a=1;a<=l;a++)
			for(int b=1;b<=l;b++)
				g[a][b]=-1;
		for(int a=1;a<=l;a++)
			if (a!=v[i])
			for(int b=a+1;b<=l;b++)
			if (b!=v[i]&&f[a][b]>=0)
			{
	//			printf("%d %d %d %d\n",i,a,b,f[a][b]);
				int x=min(a,min(b,v[i])),z=max(a,max(b,v[i]));
				int y=a+b+v[i]-x-z;
				#define update(p,q,r) \
				if (p!=v[i+1]&&q!=v[i+1]&&g[p][q]==-1||g[p][q]>f[a][b]+c[r][v[i+1]])\
					g[p][q]=f[a][b]+c[r][v[i+1]]
				update(x,y,z);
				update(x,z,y);
				update(y,z,x);
				#undef update
			}
	}
	for(int i=1;i<=l;i++)
		for(int j=i+1;j<=l;j++)
			if (d[(n&1)][i][j]!=-1&&d[(n&1)][i][j]<re)
				re=d[(n&1)][i][j];
	printf("%d\n",re);
	return 0;
}
