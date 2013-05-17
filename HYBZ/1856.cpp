/*
ID: dxmtb
PROG: [Scoi2010]字符串 
TIME: 2011.03.22
STATE: Solved
MEMO: 卡特兰数
*/
#include <cstdio>
#include <iostream>
using namespace std;

const int P=20100403;
typedef long long s64;

s64 powmod(s64 a,int N)
{
/*	s64 b=1;
	for(int i=1;i<=N;i++)
		b=b*a%P;
	return b;*/
	s64 b=(N&1)?a:1;
	N>>=1;
	while(N)
	{
		a=a*a%P;
		if (N&1)
			b=b*a%P;
		N>>=1;
	}
	return b;
}

int N,M;
int main()
{
	freopen("1856.in","r",stdin);
	scanf("%d%d",&N,&M);
	s64 ans=1;
	for(int i=N+1;i<=N+M;i++)
		ans=ans*i%P;
	s64 tmp=1;
	for(int i=1;i<=M;i++)
		tmp=tmp*i%P;
	ans=ans*powmod(tmp,P-2)%P;
	tmp=1;
	for(int i=N+2;i<=N+M;i++)
		tmp=tmp*i%P;
	s64 tmp2=1;
	for(int i=2;i<=M-1;i++)
		tmp2=tmp2*i%P;
	ans=(ans-tmp*powmod(tmp2,P-2))%P;
	if (ans<0)
		ans+=P;
	cout<<ans<<endl;
	return 0;
}
