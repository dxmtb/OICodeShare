/*
 * Problem: [JSOI2008]星球大战starwar 
 * Time: 2011.05.13
 * Author: dxmtb
 * State: Solved
 * Memo: 离线回答 + 并查集
*/
 #include <cstdio>
#include <vector>
using namespace std;

const int MAXM=200005,MAXN=2*MAXM;

struct Node
{
	int u,v;
}E[MAXM];

int N,M,K;

int father[MAXN];

int getfather(int u)
{
	if (father[u]==u)
		return u;
	return father[u]=getfather(father[u]);
}

void join(int u,int v)
{
	int fu=getfather(u),fv=getfather(v);
	father[fu]=fv;
}

int bdes[MAXN];
int des[MAXN];
vector<int> v[MAXN];
bool used[MAXN];
int ans[MAXN];

int main()
{
	freopen("1015.in","r",stdin);
	scanf("%d%d",&N,&M);
	for(int i=0;i<M;i++)
		scanf("%d%d",&E[i].u,&E[i].v);
	for(int i=0;i<N;i++)
		father[i]=i;
	scanf("%d",&K);
	for(int i=0;i<K;i++)
	{
		scanf("%d",des+i);
		bdes[des[i]]=i+1;
	}
	for(int i=0;i<M;i++)
		if (bdes[E[i].u] || bdes[E[i].v])
		{
			int t;
			if (bdes[E[i].u])
			{
				t=E[i].u;
				if (bdes[E[i].v] && bdes[E[i].v]<bdes[E[i].u])
					t=E[i].v;
			}
			else
				t=E[i].v;
			v[bdes[t]-1].push_back(i);
		}
		else join(E[i].u,E[i].v);
	int now=0;
	for(int i=0;i<N;i++)
	{
		int f=getfather(i);
		if (!used[f])
			used[f]=true,now++;
	}
	for(int i=K-1;i>=0;i--)
	{
		ans[i]=now-(i+1);
		for(int j=0,size=v[i].size();j<size;j++)
		{
			int fu=getfather(E[v[i][j]].u),fv=getfather(E[v[i][j]].v);
			if (fu!=fv)
			{
				join(fu,fv);
				now--;
			}
		}
	}
	printf("%d\n",now);
	for(int i=0;i<K;i++)
		printf("%d\n",ans[i]);
	return 0;
}
