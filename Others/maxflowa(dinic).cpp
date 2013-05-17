/*
ID: dxmtb
PROG: ‘À ‰Œ Ã‚1
TIME: 2010.4.17
STATE: Solved
MEMO: Dinic
*/
#include <cstdio>
#include <queue>
#include <stack>
#include <cstring>
#include <iostream>
using namespace std;

const int MAXN=100,MAXINT=(1<<31)-1;

int n,c[MAXN][MAXN],lv[MAXN],S=0,T,maxflow=0;

inline int min(int a,int b)
{
	return a>b?b:a;
}

void init()
{
	freopen("maxflowa.in","r",stdin);
	freopen("maxflowa.out","w",stdout);	
	scanf("%d",&n);
	T=n-1;
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
			scanf("%d",&c[i][j]);
}

bool dinic_lable()
{
	memset(lv,-1,sizeof(lv));
	queue<int> q;
	lv[S]=0;
	q.push(S);
	while(!q.empty())
	{
		int cur=q.front();
		q.pop();
		for(int i=0;i<n;i++)
		if (c[cur][i]>0&&lv[i]==-1)
		{
			q.push(i);lv[i]=lv[cur]+1;
		}
		if (lv[T]>0)return true;
	}
	return false;
}

void dinic_agument()
{
	int sta[MAXN+1],delta;
	sta[sta[0]=1]=S;
	while (sta[0])
	{
		int cur=sta[sta[0]];
		if (cur==T)
		{
			delta=MAXINT;
			for(int i=sta[0]-1;i;i--)delta=min(delta,c[sta[i]][sta[i+1]]);
			for(int i=sta[0]-1;i;i--)
			{
				c[sta[i]][sta[i+1]]-=delta,c[sta[i+1]][sta[i]]+=delta;
				if (c[sta[i]][sta[i+1]]==0)
					sta[0]=i;
			}
			maxflow+=delta;
		}
		else
		{
			int i;
			for(i=0;i<n;i++)
				if (c[cur][i]>0&&lv[i]==lv[cur]+1)
					break;
			if (i==n)
				sta[0]--,lv[cur]=-1;
			else sta[++sta[0]]=i;
		}
	}
}

void dinic()
{
	while (dinic_lable())
		dinic_agument();
}

int main() 
{
	init();
	dinic();
	printf("%d\n",maxflow);
	return 0;
}
