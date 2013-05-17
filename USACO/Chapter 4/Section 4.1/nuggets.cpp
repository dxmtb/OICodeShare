/*
ID: dxmtb1
PROG: nuggets
LANG: C++
*/
#include <cstdio>
#include <algorithm>
using namespace std;

const int MAXN=10;
const int MAXI=256;

bool d[MAXI];
int a[MAXN];
int n,len;
int maxa=0,mina=0x7fffffff;

inline int gcd(int a,int b)
{
	int t;
	while(b!=0)
	{
		t=a%b;
		a=b;b=t;
	}
	return a;
}


int main()
{
	freopen("nuggets.in","r",stdin);
	freopen("nuggets.out","w",stdout);
	scanf("%d",&n);
	for(int i=0;i<n;i++)
	{
		scanf("%d",a+i);
		if (a[i]>maxa)
			maxa=a[i];
		if (a[i]<mina)
			mina=a[i];
	}
	int gc=a[0];
	for(int i=1;i<n;i++)
		gc=gcd(gc,a[i]);
	if (gc!=1)
	{
		printf("0\n");
		return 0;
	}
	d[0]=true;
	len=0;
	int i,j;
	for(i=0,j=0;i<=2000000000;i++,j++)
	{
		if (j>=maxa)j-=maxa;
		if (d[j])
		{
			for(int k=0;k<n;k++)
				d[(j+a[k])%maxa]=true;
			++len;
		}
		else len=0;
		if (len==mina)
			break;
	}
	printf("%d\n",max(0,i-len));
	return 0;
}

