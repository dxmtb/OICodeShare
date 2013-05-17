/*
 * Problem: POI 金矿
 * Time: 2011.07.07
 * Author: dxmtb
 * State: Solved
 * Memo: 事件点 + 离散化 + 线段树
*/
#include <cstdio>
#include <vector>
#include <set>
#include <map>
using namespace std;

const int MAXN=30005;

struct Node
{
	int l,r,mid;
	int sum,maxs;
	Node *c[2];
	Node (){}
	Node (int _l,int _r):l(_l),r(_r){sum=maxs=0;c[0]=c[1]=NULL;}
	void *operator new (size_t,void *p){return p;}
	void update()
	{
		sum=c[0]->sum+c[1]->sum;
		maxs=max(c[0]->maxs,max(sum-c[1]->sum,c[0]->sum+c[1]->maxs));
	}
}pool[2*MAXN],*mem=pool;

struct SegmentTree
{
	Node *root;
	void build(int n)
	{
		build(root,0,n-1);
	}
	void build(Node *&v,int l,int r)
	{
		v=new (mem++)Node(l,r);
		v->mid=(l+r)/2;
		if (l==r)
			return ;
		build(v->c[0],l,v->mid);
		build(v->c[1],v->mid+1,r);
	}
	void insert(int pos,int val)
	{
		insert(root,pos,val);
	}
	void insert(Node *v,int pos,int val)
	{
		if (v->l!=v->r)
		{
			if (pos<=v->mid)
				insert(v->c[0],pos,val);
			else
				insert(v->c[1],pos,val);
			v->update();
		}
		else
		{
			v->sum+=val;
			v->maxs=v->sum;
		}
	}
	int getmax(){return root->maxs;}
}tree;

int N,M1,M2,S,W;
int x[MAXN],y[MAXN];

set<int> s1,s2;
map<int,int> hashx,hashy;
vector<int> event[MAXN][2];

void init()
{
	for(int i=0;i<N;i++)
	{
		s1.insert(x[i]);
		s1.insert(x[i]+S+1);
		s2.insert(y[i]);
		s2.insert(y[i]+W+1);
	}
	set<int>::iterator it;
	for(it=s1.begin(),M1=0;it!=s1.end();M1++,it++)
		hashx[*it]=M1;
	for(it=s2.begin(),M2=0;it!=s2.end();M2++,it++)
		hashy[*it]=M2;
	for(int i=0;i<N;i++)
	{
		int j;
		j=hashx[x[i]];
		event[j][1].push_back(hashy[y[i]]);
		event[j][0].push_back(hashy[y[i]+W+1]);
		j=hashx[x[i]+S+1];
		event[j][0].push_back(hashy[y[i]]);
		event[j][1].push_back(hashy[y[i]+W+1]);
	}
}

int re;
void solve()
{
	tree.build(M2);
	for(int i=0;i<M1;i++)
	{
		for(int j=0;j<(int)event[i][0].size();j++)
			tree.insert(event[i][0][j],-1);
		for(int j=0;j<(int)event[i][1].size();j++)
			tree.insert(event[i][1][j],1);
		int ans=tree.getmax();
		if (ans>re)
			re=ans;
	}
}

int main()
{
	freopen("kop.in","r",stdin);
	freopen("kop.out","w",stdout);
	scanf("%d%d",&S,&W);
	scanf("%d",&N);
	for(int i=0;i<N;i++)
		scanf("%d%d",x+i,y+i);
	init();
	solve();
	printf("%d\n",re);
	return 0;
}
