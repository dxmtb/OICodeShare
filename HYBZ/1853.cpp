/*
ID: dxmtb
PROG: SCOI2010 幸运数字
TIME: 2011.03.21
STATE: Solved
MEMO: 枚举+容斥原理
*/
#include <cstdio>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <cstdlib>
using namespace std;

typedef long long s64;

const s64 MAXN=10000000005LL;

s64 limit;

s64 lucky[2100];
int size;

void dfs(s64 num)
{
	if (num>limit)
		return ;
	lucky[size++]=num;
	dfs(num*10+6);
	dfs(num*10+8);
}

#define assert(x)
s64 gcd(s64 a,s64 b)
{
	s64 t;
	while(b!=0)
	{
		assert(b!=0);
		t=a%b;
		a=b;
		b=t;
	}
	return a;
}

s64 ans;
void calcu(int dep,s64 lcmval,int tot)
{
	if (dep==size)
	{
		if (tot)
		{
			assert(lcmval!=0);
			s64 change=limit/lcmval;
			if (tot&1) ans+=change;
			else ans-=change;
		}
		return ;
	}
	for(int i=dep;i<=size;i++)
	{
		s64 tmp=gcd(lcmval,lucky[dep]);
		assert(tmp!=0);
		assert(lucky[dep]!=0);
		if (double(lcmval)/tmp>double(limit)/lucky[dep]) return ;
		tmp=lcmval*lucky[dep]/tmp;
		calcu(i+1,tmp,tot+1);
	}
//	calcu(dep+1,lcm(lcmval,lucky[dep]),tot+1);
//	calcu(dep+1,lcmval,tot);
}

inline bool cmp(const s64 &a,const s64 &b)
{
	return a>b;
}

bool need[2100];
s64 getans(s64 a)
{
	if (a<6)
		return 0;
	limit=a;
	size=0;
	dfs(6);
	dfs(8);
	sort(lucky,lucky+size);
	for(int i=0;i<size;i++)
	{
		need[i]=true;
		for(int j=0;j<i;j++)
			if (lucky[i]%lucky[j]==0)
				need[i]=false;
	}
	int j=size;
	size=0;
	for(int i=0;i<j;i++)
		if (need[i])
			lucky[size++]=lucky[i];
	sort(lucky,lucky+size,cmp);
	ans=0;
	for(int i=0;i<size;i++)
		calcu(i,1,0);
	return ans;
}

int main()
{
	s64 a,b;
	cin>>a>>b;
	cout<<getans(b)-getans(a-1)<<endl;
	return 0;
}
