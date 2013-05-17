/*
ID: dxmtb
PROG: NOI2010 能量采集
TIME: 2010.10.4
STATE: Solved
MEMO: 数论
*/
#include <iostream>
#include <cstdio>
using namespace std;

const long long MAXN=100005;

long long n,m,re;
long long d[MAXN];

int main()
{
	freopen("energy.in","r",stdin);
	freopen("energy.out","w",stdout);
	cin>>n>>m;
	long long K=n>m?m:n;
	long long t=0x7fffffff;
	for(long long i=K;i>=1;i--)
	{
		d[i]=(n/i)*(m/i);
		if (d[i]==t)
			d[i]=d[i+1];
		else
		{
			t=d[i];
			for(long long j=2;j<=K/i;j++)
				d[i]-=d[i*j];
		}
		re+=d[i]*i;
	}
	cout<<re*2-n*m<<endl;
	return 0;
}
