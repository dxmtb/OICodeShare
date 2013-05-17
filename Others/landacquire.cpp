/*
ID: dxmtb
PROG: 土地购买
TIME: 2010.7.10
STATE: Solved
MEMO: dp+单调队列优化
*/
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

const long long MAXN=50000;

struct Node
{
	long long x,y;
	Node(long long a=0,long long b=0):x(a),y(b){}
};

bool operator < (Node a,Node b)
{ return (a.x<b.x)||(a.x==b.x&&a.y<b.y);}

long long n;
Node a[MAXN];

void init()
{
	vector<Node> v;
	scanf("%lld",&n);
//	printf("%lld\n",n);
	for(long long i=0,x,y;i<n;i++)
	{
		scanf("%lld%lld",&x,&y);
		v.push_back(Node(x,y));
	}
	sort(v.begin(),v.end());
	n=0;
	for(unsigned i=0;i<v.size();i++)
	{
		while(n&&a[n].y<=v[i].y)
			n--;
		a[++n]=v[i];
	}
//	printf("%lld\n",n);
}

long long d[MAXN+1];

inline long long f(long long j,long long k)
{
	return d[k]-d[j];
}

inline long long b(long long j,long long k)
{
	return a[j+1].y-a[k+1].y;
}

int main()
{
	freopen("landacquire.in","r",stdin);
	freopen("landacquire.out","w",stdout);
	init();
	long long K[MAXN];
	int q[MAXN],l,r;
	q[l=r=0]=0;
	for(long long i=1;i<=n;i++)
	{
		while(l<r&&f(q[l],q[l+1])<=b(q[l],q[l+1])*a[i].x)
			l++;
		int k=q[l];
		d[i]=d[k]+a[i].x*a[k+1].y,K[i]=k;
		while(l<r&&f(q[r-1],q[r])*b(q[r],i)>=f(q[r],i)*b(q[r-1],q[r]))
			r--;
		q[++r]=i;
//		printf("%lld %lld\n",d[i],K[i]);
	} 
	printf("%lld\n",d[n]);
	return 0;
}
