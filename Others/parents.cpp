/*
 * Problem: 双亲数
 * Time: 2011.04.13
 * Author: dxmtb
 * State: Solved
 * Memo: 加法原理
*/
#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;
const int MAXN=1000005;

long long A,B,D;
long long d[MAXN];

int main()
{
	freopen("parents.in","r",stdin);
	freopen("parents.out","w",stdout);
	scanf("%lld%lld%lld",&A,&B,&D);
	long long C=min(A,B),t1=-1,t2=-1;
	for(int i=C;i>=D;i--)
	{
		if (A/i==t1 && B/i==t2)
			d[i]=d[i+1];
		else
		{
			t1=A/i;
			t2=B/i;
			d[i]=t1*t2;
			for(int j=i+i;j<=C;j+=i)
				d[i]-=d[j];
		}
	}
	cout<<d[D]<<endl;
	return 0;
}
