/*
ID: dxmtb
PROG: 方程的解数
TIME: 2010.10.19
STATE: Solved
MEMO: 搜索+Hash
*/
#include <cstdio>
#include <cmath>
using namespace std;

const int MAXN=8,MAXM=155;
const int mod=1741013;

struct Node
{
	int mod,re;
	Node *next;
	Node(int a,int b,Node *c):mod(a),re(b),next(c){}
}*has[2][mod];

int n,m;
int c[MAXN][MAXM+1];
int re;

void insert(int s)
{
	Node **hash;
	if (s<0) hash=has[0],s=-s;
	else hash=has[1];
	int j=s/mod,i=s%mod;
	if (!hash[i]||hash[i]->mod>j)
		hash[i]=new Node(j,1,hash[i]);
	else
	for(Node *p=hash[i];p;p=p->next)
		if (p->mod==j)
		{
			p->re++;
			return ;
		}
		else if (!p->next||p->next->mod>j)
		{
			Node *ne=new Node(j,1,p->next);
			p->next=ne;
			return ;
		}
}

int find(int s)
{
	Node **hash;
	if (s<0) hash=has[0],s=-s;
	else hash=has[1];
	int j=s/mod,i=s%mod;
	for(Node *p=hash[i];p&&p->mod<=j;p=p->next)
		if (p->mod==j)
			return p->re;
	return 0;
}

void dfs1(int i,int s)
{
	if (i==n/2+1)
	{
		insert(s);
		return ;
	}
	for(int j=1;j<=m;j++)
		dfs1(i+1,s+c[i][j]);
}

void dfs2(int i,int s)
{
	if (i==n+1)
	{
		re+=find(-s);
		return ;
	}
	for(int j=1;j<=m;j++)
		dfs2(i+1,s+c[i][j]);
}

int main()
{
	freopen("equation1.in","r",stdin);
	freopen("equation1.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		c[i][0]=1;
		for(int j=1;j<=m;j++)
			c[i][j]=x*pow(double(j),y);
	}
	dfs1(1,0);
	dfs2(n/2+1,0);
	printf("%d\n",re);
	return 0;
}

