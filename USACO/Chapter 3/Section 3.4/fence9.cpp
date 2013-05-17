/*
ID: dxmtb1
PROG: fence9
LANG: C++
*/
#include <cstdio>
#include <cstdlib>
using namespace std;

const int MAXN=32000;

int n,m,p,re;

inline int gcd(int a,int b)
{
	int t;
	while(b!=0)
	{
		t=a%b;
		a=b;
		b=t;
	}
	return a;
}

int main()
{
	freopen("fence9.in","r",stdin);
	freopen("fence9.out","w",stdout);
	scanf("%d%d%d",&n,&m,&p);
	printf("%d\n",(p*m-gcd(n,m)-gcd(abs(p-n),m)-p)/2+1);
	return 0;
}

