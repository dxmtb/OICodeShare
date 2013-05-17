/*
ID: dxmtb
PROG: poj2318 TOYS
TIME: 2010.6.5
STATE: Solved
MEMO: ²æ»ý ¶þ·Ö
*/
#include <cstdio>
#include <cstring>
using namespace std;

const long long MAXN=5001,MAXM=5001;

long long n,m,x1,y1,x2,y2;
long long U[MAXN],L[MAXN],x[MAXM],y[MAXM];
int re[MAXN];
bool first=true;

inline long long det(long long x1,long long y1,long long x2,long long y2)
{
	return x1*y2-x2*y1;
}

inline long long cross(long long x1,long long y1,long long x2,long long y2,long long x3,long long y3)
{
	return det(x2-x1,y2-y1,x3-x1,y3-y1);
}

void init()
{
	for(int i=1;i<=n;i++)
		scanf("%lld%lld",&U[i],&L[i]);
	U[0]=L[0]=x1;
	U[n+1]=L[n+1]=x2;
	for(int i=0;i<m;i++)
		scanf("%lld%lld",&x[i],&y[i]);
}

void solve()
{
	if (!first)printf("\n");	
	else first=false;
	memset(re,0,sizeof(re));
	for(int i=0;i<m;i++)
	{
		long long tx=x[i],ty=y[i];
		int l=0,r=n+1;
		int m;
		while(l<r-1)
		{
			m=(l+r)/2;
			long long a=cross(U[l],y1,tx,ty,L[l],y2);
			long long b=cross(U[m],y1,tx,ty,L[m],y2);
			long long c=cross(U[r],y1,tx,ty,L[r],y2);
			if (a*b<0)
				r=m;
			else if (b*c<0)
				l=m;
			else printf("wrong");
		}
		++re[l];
	}
	for(int i=0;i<=n;i++)
		printf("%d: %d\n",i,re[i]);
}

int main() 
{
	freopen("2318.in","r",stdin);
	freopen("2318.out","w",stdout);
	while(scanf("%lld",&n)!=EOF&&n)
	{
		scanf("%lld%lld%lld%lld%lld",&m,&x1,&y1,&x2,&y2);
		init();
		solve();
	}
	return 0;
}
