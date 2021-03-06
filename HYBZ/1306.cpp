/*
ID: dxmtb
PROG: [CQOI2009]match循环赛
TIME: 2011.03.30
STATE: Solved
MEMO: 最小表示+搜索
*/
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN=10,MAXM=MAXN*MAXN/2;
const int MO=174101;

typedef long long s64;

struct Node
{
	s64 num;
	int v;
	Node *next;
	Node (s64 _num,int _v,Node *_next):
		num(_num),v(_v),next(_next){}
};

struct Hash
{
	Node *adj[MO];
	Node *find(int num)
	{
		for(Node *p=adj[num%MO];p;p=p->next)
			if (p->num==num)
				return p;
		return NULL;
	}
	void insert(int num,int v)
	{
		int k=num%MO;
		adj[k]=new Node(num,v,adj[k]);
	}
}table[MAXN];

int score[MAXN];
int N,re;
int ns[MAXN];
int tmp[MAXN];

void dfs(int dep1,int dep2)
{
	if (dep1==N-1)
	{
		if (ns[dep1]==0)
			re++;
		return ;
	}
	if (dep2==N)
	{
		if (ns[dep1])
			return ;
		memcpy(tmp,ns,sizeof(ns));
		sort(tmp+dep1+1,tmp+N);
		int hashnum=0;
		for(int i=dep1+1;i<N;i++)
			hashnum=hashnum*23+tmp[i];
		Node *p=table[dep1].find(hashnum);
		if (p!=NULL) re+=p->v;
		else 
		{
			int tre=re;
			dfs(dep1+1,dep1+2);
			table[dep1].insert(hashnum,re-tre);
		}
		return ;
	}
	if (ns[dep1]-3>=0)
	{
		ns[dep1]-=3;
		dfs(dep1,dep2+1);
		ns[dep1]+=3;
	}
	if (ns[dep1]-1>=0 && ns[dep2]-1>=0)
	{
		ns[dep1]-=1;
		ns[dep2]-=1;
		dfs(dep1,dep2+1);
		ns[dep1]+=1;
		ns[dep2]+=1;
	}
	if (ns[dep2]-3>=0)
	{
		ns[dep2]-=3;
		dfs(dep1,dep2+1);
		ns[dep2]+=3;
	}
}

int main()
{
	freopen("1306.in","r",stdin);
	scanf("%d",&N);
	for(int i=0;i<N;i++)
	{
		scanf("%d",score+i);
		ns[i]=score[i];
	}
	dfs(0,1);
	printf("%d\n",re);
	return 0;
}
