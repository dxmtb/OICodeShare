/*
ID: dxmtb
PROG: NOIP2004 合并果子
TIME: 2010.5.15
STATE: Solved
MEMO: 贪心
*/
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN=10010;

int n,m;
vector<int>v;

bool comp(int a,int b)
{
	return (a>b);
}

void init()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		int x;
		scanf("%d",&x);
		v.push_back(x);
		push_heap(v.begin(),v.end(),comp);
	}
}

void solve()
{
	for(int i=0;i<n-1;i++)
	{
		int x1=v.front();
		pop_heap(v.begin(),v.end(),comp);
		v.pop_back();
		int x2=v.front();
		pop_heap(v.begin(),v.end(),comp);
		v.pop_back();
		m+=x1+x2;
		v.push_back(x1+x2);
		push_heap(v.begin(),v.end(),comp);
	}
	printf("%d\n",m);
}

int main() 
{
	freopen("fruit.in","r",stdin);
	freopen("fruit.out","w",stdout);
	init();
	solve();
	return 0;
}
