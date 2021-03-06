/*
ID: dxmtb
PROG: HNOI2010 弹飞绵羊
TIME: 2011.03.11
STATE: Solved
MEMO: 动态树
*/
#include <cstdio>

const int MAXN=200005;

struct Node
{
	bool root;
	int size;
	Node *c[2],*father;
	Node *rz(){return size=c[0]->size+1+c[1]->size,this;}
	void zig(bool d);
	void zigzig(bool d);
	void splay();
}tree[MAXN],Tnull,*null=&Tnull;

void Node::zig(bool d)
{
	Node *p=father;
	p->c[d]=c[!d];
	c[!d]->father=p;
	p->rz();
	if (!father->root)
	{
		if (father->father->c[0]==father) 
			father->father->c[0]=this;
		else if (father->father->c[1]==father)
			father->father->c[1]=this;
	}
	father=father->father;
	p->father=this;
	c[!d]=p;
	rz();
	if (p->root) 
		p->root=false,root=true;
}

void Node::splay()
{
	while(!root)
	{
		bool d=(father->c[1]==this);
		if (father->root)
			zig(d);
		else
		{
			bool dd=(father->father->c[1]==father);
			if (d==dd) father->zig(d),zig(d);
			else zig(d),zig(dd);
		}
	}
}


void access(Node *v)
{
	Node *u=v;
	v=null;
	do
	{
		u->splay();
		u->c[1]->root=true;
		u->c[1]=v;
		v->root=false;
		u->rz();
		v=u;
		u=v->father;
	}while(u!=null);
}

void join(Node *u,Node *v)
{
	access(u);
	u->splay();
	u->c[0]->root=true;
	u->c[0]->father=null;
	u->c[0]=null;
	u->father=v;
	access(u);
}

int main()
{
	null->c[0]=null->c[1]=null->father=null;
	int N,M;
	scanf("%d",&N);
	for(int i=0;i<=N;i++)
	{
		tree[i].root=true;
		tree[i].father=tree[i].c[0]=tree[i].c[1]=null;
		tree[i].size=1;
	}
	for(int i=0;i<N;i++)
	{
		int k;
		scanf("%d",&k);
		if (i+k<N) tree[i].father=tree+i+k;
		else tree[i].father=tree+N;
	}
	scanf("%d",&M);
	while(M--)
	{
		int i,j,k;
		scanf("%d%d",&i,&j);
		if (i==1)
		{
			access(tree+j);
			tree[j].splay();
			printf("%d\n",tree[j].c[0]->size);
		}
		else
		{
			scanf("%d",&k);
			if (j+k<=N) join(tree+j,tree+j+k);
			else join(tree+j,tree+N);
		}
	}
	return 0;
}
