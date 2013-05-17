/*
ID: dxmtb
PROG: APIO2010 特别行动队
TIME: 2010.5.29
STATE: Solved
MEMO: 动态规划 斜率优化
*/
#include <iostream>
#include <cstdio>
using namespace std;

const int MAXN=1000010;

long long s[MAXN+1];
long long d[MAXN+1];
int n,a,b,c;

inline long long max(int i,int j)
{
	if (i>j)return i;
		else return j;
}

inline long long pow(int a)
{
	return a*a;
}

inline double g(int j,int k)
{
	return double(d[j]-d[k])/(s[j]-s[k])+a*(s[j]+s[k])-b;
}

inline long long h(int x)
{
	return 2*a*s[x];
}

void init()
{
	scanf("%d%d%d%d",&n,&a,&b,&c);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&s[i]);
		s[i]+=s[i-1];
	}
}

int ss,t;
int q[MAXN];

void dp()
{
	q[ss=t=0]=0;
	for(int i=1;i<=n;i++)
	{
		while (ss<t&&g(q[ss],q[ss+1])>=h(i))ss++;
		int k=q[ss];
		d[i]=d[k]+a*pow(s[i]-s[k])+b*(s[i]-s[k])+c;
		while (ss<t&&g(q[t-1],q[t])<g(q[t],i))--t;
		q[++t]=i;
	}
}

int main()
{
	freopen("commando.in","r",stdin);
	freopen("commando.out","w",stdout);
	init();
	dp();
	cout<<d[n]<<endl;
	return 0;
}
