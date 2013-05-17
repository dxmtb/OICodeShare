/*
PROG: treasure
LANG: C++
ID: dxmtb1
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int MAXN=6000;

int d[2][MAXN];
int a[MAXN];
int N;

inline void Max(int &a,int b)
{
	if (b>a) a=b;
}

inline void Min(int &a,int b)
{
	if (b<a) a=b;
}

int main()
{
	freopen("treasure.in","r",stdin);
	freopen("treasure.out","w",stdout);
	scanf("%d",&N);
	for(int i=0;i<N;i++)
		scanf("%d",a+i);
	if (N%2)
	for(int i=0;i<N;i++)
		d[0][i]=a[i];
	for(int j=1;j<N;j++)
	{
		int *f=d[(j&1)],*g=d[(j&1)^1];
		memset(d[(j&1)],0,sizeof(d[(j&1)]));
		for(int i=0;i+j<N;i++)
		{
			if ((N-j)%2)  //Bessie
			{
				f[i]=g[i]+a[i+j];
				if (i!=N-1)
					Max(f[i],g[i+1]+a[i]);
			}
			else 
			{
				f[i]=g[i];
				if (i!=N-1)
					Min(f[i],g[i+1]);
			}
		}
	}
	printf("%d\n",d[(N-1)&1][0]);
	return 0;
}
