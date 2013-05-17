/*
ID: dxmtb
PROG: 教官
TIME: 2010.11.17
STATE: Solved
MEMO: lcm
*/
#include <cstdio>
const int MAXN=10005;

typedef long long LL;

int a[MAXN];
int N;
bool vis[MAXN];

inline LL gcd(LL a,LL b)
{
	LL c;
	while(b!=0)
	{
		c=a;
		a=b;
		b=c%a;;
	}
	return a;
}

inline LL lcm(LL a,LL b)
{
	return a*b/gcd(a,b);
}

int main()
{
	freopen("officer.in","r",stdin);
	freopen("officer.out","w",stdout);
	scanf("%d",&N);
	for(int i=1;i<=N;i++)
		scanf("%d",a+i);
	LL re=1;
	for(int i=1;i<=N;i++)
	if (!vis[i])
	{
		LL p=1;vis[i]=true;
		for(int j=a[i];j!=i;j=a[j],p++)
			vis[j]=true;
		re=lcm(re,p);
	}
	printf("%lld\n",re);
	return 0;
}
