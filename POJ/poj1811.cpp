/*
ID: dxmtb
PROG: poj1811 Prime Test
TIME: 2010.10.29
STATE: Solved
MEMO: miller-rabbin && pollard-rho
*/
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <cstdio>
using namespace std;

typedef unsigned long long LL;

const int S=8;

inline void swap(LL &a,LL &b)
{
	a=a^b;
	b=a^b;
	a=a^b;
}

LL modular_multi(LL x,LL y,LL mo)
{
	LL t;
	x%=mo;
	for(t=0;y;x=(x<<1)%mo,y>>=1)
		if (y&1)
			t=(t+x)%mo;
	return t;
}

LL modular_exp(LL num,LL t,LL mo)
{
	LL ret=1,temp=num%mo;
	for(;t;t>>=1,temp=modular_multi(temp,temp,mo))
		if (t&1)
			ret=modular_multi(ret,temp,mo);
	return ret;
}

bool miller_rabbin(LL n)
{
	if (n==2)return true;
	if (n<2||!(n&1))return false;
	int t=0;
	LL a,x,y,u=n-1;
	while((u&1)==0) t++,u>>=1;
	for(int i=0;i<S;i++)
	{
		a=rand()%(n-1)+1;
		x=modular_exp(a,u,n);
		for(int j=0;j<t;j++)
		{
			y=modular_multi(x,x,n);
			if (y==1&&x!=1&&x!=n-1)
				return false;
			x=y;
		}
		if (x!=1)
			return false;
	}
	return true;
}

LL gcd(LL a,LL b)
{
	while(b)
	{
		swap(a,b);
		b=b%a;
	}
	return a>0?a:-a;
}

LL re;

LL pollard_rho(LL n,int c)
{
	LL x,y,d,i=1,k=2;
	x=rand()%(n-1)+1;
	y=x;
	while(true)
	{
		++i;
		x=(modular_multi(x,x,n)+c)%n;
		d=gcd(y-x,n);
		if (1<d&&d<n) return d;
		if (x==y) return n;
		if (i==k)
			y=x,k<<=1;
	}
}

void findFactor(LL n,int k)
{
	if (n==1) return ;
	if (miller_rabbin(n))
	{
		if (n<re)
			re=n;
		return ;
	}
	LL p=n;
	while(p>=n)
		p=pollard_rho(p,k--);
	findFactor(p,k);
	findFactor(n/p,k);
}

int main()
{
	int T;
	LL num;
	cin>>T;
	srand(time(0));
	while(T--)
	{
		cin>>num;
		if (miller_rabbin(num))
			cout<<"Prime"<<endl;
		else
		{
			if (num&1)
			{
				re=num;
				findFactor(num,107);
				cout<<re<<endl;
			}
			else cout<<2<<endl;
		}
	}
	return 0;
}
