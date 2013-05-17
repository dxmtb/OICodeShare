/*
ID: dxmtb
PROG: NOIP2006 作业调度方案
TIME: 2010.9.2
STATE: Solved
MEMO: 模拟
*/
#include <cstdio>
#include <cstring>
using namespace std;

struct Node
{
	Node(int a,int b,Node *nn,Node *ll)
	{
		l=a,r=b,next=nn,left=ll;
	}
	int l,r;
	Node *left,*next;
};

const int MAXN=450,MAXT=MAXN*MAXN*MAXN;

int n,m;
int order[MAXN],num[MAXN][MAXN],t[MAXN][MAXN],now[MAXN],last[MAXN];
Node *f[MAXN];

void init()
{
	scanf("%d%d",&m,&n);
	for(int i=0;i<n*m;i++)
		scanf("%d",&order[i]);
	for(int i=1;i<=n;i++)
		for(int j=0;j<m;j++)
		{
			scanf("%d",&num[i][j]);
			--num[i][j];
		}
	for(int i=1;i<=n;i++)
		for(int j=0;j<m;j++)
			scanf("%d",&t[i][j]);
	for(int i=0;i<m;i++)
		f[i]=new Node(0,MAXT,0,0);
}

void settle(int x)
{
	x=order[x];
	int need=num[x][now[x]],nt=t[x][now[x]];
	now[x]++;
	for(Node *p=f[need];p;p=p->next)
	{
		int l=p->l,r=p->r;
		if (l<last[x])
			l=last[x];
		if (r-l>=nt)
		{
			if (l+nt>last[x])
				last[x]=l+nt;
			if (p->l<l)
			{
				Node *q=new Node(p->l,l,p,p->left);
				if (p->left)p->left->next=q,p->left=q;
				else f[need]=q,p->left=q;
			}
			p->l=l+nt;
			break;
		}
	}
}

void print()
{
	int re=0;
	for(int i=0;i<m;i++)
		if (last[i]>re)
			re=last[i];
	for(int need=0;need<m;need++)
	for(Node *p=f[need];p;p=p->next)
	{
		if (p->r==MAXT)
		{
			if (p->l>re)
				re=p->l;
			break;
		}
	}	
	printf("%d\n",re);
}

int main() 
{
	freopen("jsp.in","r",stdin);
	freopen("jsp.out","w",stdout);
	init();
	for(int i=0;i<m*n;i++)
		settle(i);
	print();
	return 0;
}
