/*
ID: dxmtb
PROG: tj1460 旅行
TIME: 2011.03.12
STATE: Solved
MEMO: 并查集
*/
#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long s64;
const s64 MAXM=200005;
const s64 MAXN=100005;

struct Node
{
	s64 u,v,w;
}edge[MAXM];

bool cmp(const Node &a,const Node &b)
{
	return a.w<b.w;
}

s64 father[MAXN],size[MAXN];

s64 getfather(s64 x)
{
	if (father[x]==x)
		return x;
	return father[x]=getfather(father[x]);
}

void join(s64 x,s64 y)
{
	s64 fx=getfather(x),fy=getfather(y);
	father[fx]=fy;
	size[fy]+=size[fx];
}

s64 N,M,Q;
pair<s64,s64> ask[MAXM];
s64 re[MAXM];
int main()
{
	scanf("%lld%lld%lld",&N,&M,&Q);
	for(s64 i=1;i<=N;i++)
		father[i]=i,size[i]=1;
	for(s64 i=0;i<M;i++)
		scanf("%lld%lld%lld",&edge[i].u,&edge[i].v,&edge[i].w);
	sort(edge,edge+M,cmp);
	for(s64 i=0;i<Q;i++)
	{
		scanf("%lld",&ask[i].first);
		ask[i].second=i;
	}
	sort(ask,ask+Q);
	s64 j=0;
	s64 ans=0;
	for(s64 i=0;i<Q;i++)
	{
		for(;j<M && edge[j].w<=ask[i].first;j++)
		{
			if (getfather(edge[j].u)==getfather(edge[j].v))
				continue;
			s64 size1=size[getfather(edge[j].u)];
			s64 size2=size[getfather(edge[j].v)];
			ans-=size1*(size1-1)/2+size2*(size2-1)/2;
			ans+=(size1+size2)*(size1+size2-1)/2;
			join(edge[j].u,edge[j].v);
		}
		re[ask[i].second]=ans;
	}
	for(s64 i=0;i<Q;i++)
		printf("%lld\n",re[i]);
	return 0;
}
