/*
ID: dxmtb
PROG: SDOI2009 HH的项链
TIME: 2011.03.06
STATE: Solved
MEMO: 树状数组
*/
#include <cstdio>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;
const int MAXN=50005;
const int MAXM=200005;

int A[MAXN],next[MAXN],C[MAXN];
int N,M;

void add(int u,int v)
{
	while(u<=N)
	{
		C[u]+=v;
		u+=u&(-u);
	}
}

int getsum(int u)
{
	int ans=0;
	while(u>=1)
	{
		ans+=C[u];
		u-=u&(-u);
	}
	return ans;
}

int getsum(int l,int r)
{
	return getsum(r)-getsum(l-1);
}

int ans[MAXM];
int main()
{
	freopen("diff.in","r",stdin);
	freopen("diff.out","w",stdout);
	scanf("%d",&N);
	map<int,int> table;
	map<int,int>::iterator it;
	for(int i=1;i<=N;i++)
	{
		scanf("%d",A+i);
		it=table.find(A[i]);
		if (it!=table.end())
			next[it->second]=i;
		else add(i,1);
		table[A[i]]=i;
	}
	scanf("%d",&M);
	vector<pair<pair<int,int>,int> > q(M);
	for(int i=0;i<M;i++)
	{
		scanf("%d%d",&q[i].first.first,&q[i].first.second);
		q[i].second=i;
	}
	sort(q.begin(),q.end());
	for(int i=1,j=0;i<=N;i++)
	{
		while(j<M && q[j].first.first==i)
		{
			ans[q[j].second]=getsum(q[j].first.first,q[j].first.second);
			j++;
		}
		add(i,-1);
		if (next[i])
			add(next[i],1);
	}
	for(int i=0;i<M;i++)
		printf("%d\n",ans[i]);
	return 0;
}
