/*
 * Problem: [JSOI2008]最小生成树计数
 * Time: 2011.05.13
 * Author: dxmtb
 * State: Solved
 * Memo: 相同边权形成连通分量数相同
*/
#include <cstdio>
#include <cmath>
#include <cassert>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN=105,MAXM=1005;
const int MO=31011;

struct Edge
{
	int u,v,w;
	bool used,vis;
}E[MAXM];

inline bool operator < (const Edge &a,const Edge &b)
{
	return a.w<b.w;    
}

int getfather(int *father,int u)
{
	if (father[u]==u)
	    return u;	
	return father[u]=getfather(father,father[u]);
}


int ret;
void dfs(int *now,int dep,int end,int left)
{
	if (left==0)
	{
		ret++;
		return ;
	}
	if (dep==end+1)
		return ;
	int c_now[MAXN];
	memcpy(c_now,now,sizeof(c_now));
	dfs(c_now,dep+1,end,left);
	int fu=getfather(c_now,E[dep].u),fv=getfather(c_now,E[dep].v);
	if (fu!=fv)
	{
		c_now[fu]=fv;
		dfs(c_now,dep+1,end,left-1);
	}
}

int father[MAXN],now[MAXN];
int N,M;
int re=1;
int main()
{
	freopen("1016.in","r",stdin);
	scanf("%d%d",&N,&M);
	for(int i=1;i<=N;i++)
		father[i]=i;
	for(int i=0;i<M;i++)
		scanf("%d%d%d",&E[i].u,&E[i].v,&E[i].w);
	sort(E,E+M);
	for(int i=0,j=N;i<M && j!=1;)
	{
		int k;
		for(k=i;k+1<M;k++)
			if (E[k+1].w!=E[i].w)
				break;
		memcpy(now,father,sizeof(father));
		int tot=0;
		for(int kk=i;kk<=k;kk++)
		{
			int fu=getfather(father,E[kk].u);
			int fv=getfather(father,E[kk].v);
			if (fu!=fv)
			{
				father[fu]=fv;
				tot++;
				j--;
			}
		}
		ret=0;
		dfs(now,i,k,tot);
		re=re*ret%MO;
		i=k+1;
		if (i==M && j>1)
		{
			printf("0\n");
			return 0;
		}
	}
	printf("%d\n",re);
	return 0;
}
