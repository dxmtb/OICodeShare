/*
PROG: protest
LANG: C++
ID: dxmtb1
*/
/*
TIME: 2011.02.18
STATE: Solved
MEMO: dp+树状数组
*/
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN=100005;
const int MO=1000000009;

int N;
int sum[MAXN],a[MAXN];
int f[MAXN],d[MAXN];
vector<pair<int,int> >v;

void update(int i,int k)
{
	while(i<=N)
	{
		a[i]+=k;
		if (a[i]>MO) a[i]-=MO;
		i+=i&(-i);
	}
}

int getsum(int i)
{
	int s=0;
	while(i>0)
	{
		s+=a[i];
		if (s>MO) s-=MO;
		i-=i&(-i);
	}
	return s;
}

int main()
{
	freopen("protest.in","r",stdin);
	freopen("protest.out","w",stdout);
	scanf("%d",&N);
	v.push_back(make_pair(0,0));
	for(int i=1;i<=N;i++)
	{
		scanf("%d",sum+i);
		sum[i]+=sum[i-1];
		v.push_back(make_pair(sum[i],i));
	}
	sort(v.begin(),v.end());
	for(int i=0,tot=0;i<=N;i++)
		if (i==0||v[i].first!=v[i-1].first) f[v[i].second]=++tot;
       		else f[v[i].second]=tot;
	d[0]=1;	
	update(f[0],1);
	for(int i=1;i<=N;i++)
	{
		d[i]=getsum(f[i]);
		update(f[i],d[i]);
	}
	printf("%d\n",d[N]);
	return 0;
}
