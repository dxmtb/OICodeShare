/*
 * Problem: [HNOI2008]越狱
 * Time: 2011.04.21
 * Author: dxmtb
 * State: Solved
 * Memo: 加法原理
*/
#include <iostream>
using namespace std;

const int MO=100003;

typedef long long s64;

int pow(s64 a,s64 b)
{
	if (a==0)
		return 0;
	int c=1;
	while(b)
	{
		if (b&1) c=(c*a)%MO;
		a=(a*a)%MO;
		b>>=1;
	}
	return c;
}

int main()
{
	freopen("1008.in","r",stdin);
	s64 N,M;
	cin>>M>>N;
	if (N==1)
	{
		cout<<0<<endl;
		return 0;
	}
	s64 re=(pow(M,N)-M*pow(M-1,N-1))%MO;
	if (re<0)
		re+=MO;
	cout<<re<<endl;
	return 0;
}
