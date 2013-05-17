/*
ID: dxmtb
PROG: NOIP2004合唱队形
TIME: 2010.5.1
STATE: Solved
MEMO: 动态规划 最长升（降）子序列
*/
#include <cstdio>
using namespace std;

const int MAXN=102;

int n,t[MAXN];
int di[MAXN],dd[MAXN];

void init()
{
	scanf("%d",&n);
	for(int i=0;i<n;i++)
		scanf("%d",&t[i]);
}

inline int max(int a,int b)
{
	return a>b?a:b;
}

inline int min(int a,int b)
{
	return a<b?a:b;
}

void calcu()
{
	for(int i=0;i<n;i++)
	{
		di[i]=1;
		for(int j=0;j<i;j++)
			if (t[j]<t[i])di[i]=max(di[i],di[j]+1);
	}
	for(int i=n-1;i>=0;i--)
	{
		dd[i]=1;
		for(int j=n-1;j>i;j--)
			if (t[j]<t[i])dd[i]=max(dd[i],dd[j]+1);	
	}
}

int otry()
{
	int re=n-dd[0];
	int i;
	for(i=0;i<n;i++)
		re=min(re,n-di[i]-dd[i]+1);
	return re;
}

int main() 
{
	freopen("chorus.in","r",stdin);
	freopen("chorus.out","w",stdout);
	init();
	calcu();
	printf("%d",otry());
	return 0;
}
