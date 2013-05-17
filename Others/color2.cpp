/*
 * Problem: APIO2011 方格染色
 * Time: 2011.06.02
 * Author: dxmtb
 * State: Solved
 * Memo: 映射到第一行+并查集
*/
#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <algorithm>
#include <vector>
using namespace std;

const int MAXN=100005;
const int MO=1000000000;

int color[MAXN],father[MAXN],edge[MAXN];

inline void noans()
{
	printf("0\n");
	exit(0);
}

int getfather(int x)
{
	if (father[x]==x)
	{
		assert(edge[x]==0);
		return x;
	}
	int fx=getfather(father[x]);
	if (color[father[x]]!=-1)
	{
		if (color[x]!=-1)
		{
			if (color[x]!=(color[father[x]]^edge[x]))
				noans();
		}
		else
			color[x]=(color[father[x]]^edge[x]);
	}
	edge[x]=(edge[x]^edge[father[x]]);
	return father[x]=fx;
}

void join(int k,int x,int y)
{
	int fx=getfather(x),fy=getfather(y);
	if (fx==fy)
	{
		if ((k^edge[x]^edge[y])==0)
			return ;
		noans();
	}
	if (color[x]!=-1)
	{
		if (color[fx]==-1)
			color[fx]=(color[x]^edge[x]);
		else
		{
			if (color[fx]!=(color[x]^edge[x]))
				noans();
		}
	}
	if (color[y]!=-1)
	{
		if (color[fy]==-1)
			color[fy]=(color[y]^edge[y]);
		else
		{
			if (color[fy]!=(color[y]^edge[y]))
				noans();
		}
	}
	k^=edge[x];
	k^=edge[y];
	father[fx]=fy;
	edge[fx]=k;
	if (color[fx]!=-1 && color[fy]!=-1)
	{
		if ((color[fx]^color[fy])!=k)
			noans();
	}
	else if (color[fx]==-1 && color[fy]==-1)
		return ;
	else if (color[fx]!=-1)
		color[fy]=(color[fx]^edge[fx]);
	else
		color[fx]=(color[fy]^edge[fx]);
}

int N,M,K;
vector<pair<int,int> > v[MAXN];
bool used[MAXN];
int main()
{
	freopen("color.in","r",stdin);
	freopen("color.out","w",stdout);
	scanf("%d%d%d",&N,&M,&K);
	for(int i=1;i<=M;i++)
	{
		color[i]=-1;
		father[i]=i;
		edge[i]=0;
	}
	for(int i=0;i<K;i++)
	{
		int x,y,c;
		scanf("%d%d%d",&x,&y,&c);
		if (x==1)
			color[y]=c;
		else
		{
			v[x].push_back(make_pair(y,c));
		}
	}
	for(int i=2;i<=N;i++)
	{
		sort(v[i].begin(),v[i].end());
		int size=v[i].size();
		for(int j=1;j<size;j++)
		{
			int k1=v[i][j].first-v[i][j-1].first,k2=i-1;
			int k;
			if ((k1&1)==0 || (k2&1)==0)
				k=0;
			else
				k=1;
			k^=(v[i][j-1].second^v[i][j].second);
			join(k,v[i][j-1].first,v[i][j].first);
		}
	}
	for(int i=1;i<=M;i++)
		getfather(i);
	int ans=0;
	for(int i=1;i<=M;i++)
	{
		int fx=getfather(i);
		if (!used[fx])
		{
			used[fx]=true;
			if (color[fx]==-1)
				ans++;
		}
	}
	for(int i=2;i<=N;i++)
		if (v[i].size()==0)
			ans++;
	int re=1;
	for(int i=1;i<=ans;i++)
		re=re*2%MO;
	printf("%d\n",re);
	return 0;
}
