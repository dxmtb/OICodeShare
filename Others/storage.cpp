/*
ID: dxmtb
PROG: 仓库建设
TIME: 2010.7.8
STATE: Solved
MEMO: 斜率优化单调队列
*/
#include <cstdio>
using namespace std;

const int MAXN=1000011;
const long long MAXINT=((~0llu)>>1);

long long d[MAXN],s[MAXN],c[MAXN],p[MAXN],t[MAXN];
int n;

inline long long min(long long a,long long b)
{
	return a>b?b:a;
}

inline long long a(int k1,int k2)
{
	return d[k1+1]+s[k1]*p[k1-1]-t[k1-1]+c[k1]-d[k2+1]-s[k2]*p[k2-1]+t[k2-1]-c[k2];
}

inline long long b(int k1,int k2)
{
	return s[k1]-s[k2];
}

inline double g(int k1,int k2)
{
	return double(a(k1,k2))/b(k1,k2);
}

int main()
{
	freopen("storage.in","r",stdin);
	freopen("storage.out","w",stdout);
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%lld%lld%lld",s+i,p+i,c+i);
		t[i]=t[i-1]+p[i]*s[i];
		p[i]+=p[i-1];
	}
	for(int i=1;i<=n;i++)
			d[i]=MAXINT;
	d[n+1]=0;
	int q[MAXN];
	int l=0,r=-1;
	q[++r]=n;
	for(int i=n;i;i--)
	{
		while (l<r&&a(q[l],q[l+1])>=b(q[l],q[l+1])*p[i-1])
			l++;
		int k=q[l];
		d[i]=min(d[i],d[k+1]+s[k]*(p[k-1]-p[i-1])-t[k-1]+t[i-1]+c[k]);
		while (l<r&&g(q[r-1],q[r])<=g(q[r],i-1))
			r--;
		q[++r]=i-1;
	}
	printf("%lld\n",d[1]);
	return 0;
}



