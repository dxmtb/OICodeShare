/*
ID: dxmtb
PROG: NOI2005 维护数列
TIME: 2011.03.14
STATE: Solved
MEMO: splay
*/
#include <cstdio>
#include <algorithm>
using namespace std;

const int MAXN=20005;
const int oo=100000;

struct Node
{
	Node *c[2];
	int data,sum,msum,mssum[2],size;
	bool rev,same;
	inline Node *rz();
	inline void make_same(int);
	inline void pass();
	Node();
}Null,*null=&Null;

Node::Node()
{
	size=1;
	c[0]=c[1]=null;
}

inline Node* Node::rz()//rev==false same==false//remain to be changed
{
	size=c[0]->size+1+c[1]->size;
	sum=c[0]->sum+data+c[1]->sum;
	msum=max(c[0]->msum,max(c[1]->msum,max(0,c[0]->mssum[c[0]->rev^1])+data+max(0,c[1]->mssum[c[1]->rev])));
	mssum[0]=max(c[0]->mssum[c[0]->rev],c[0]->sum+data+max(0,c[1]->mssum[c[1]->rev]));
	mssum[1]=max(c[1]->mssum[c[1]->rev^1],c[1]->sum+data+max(0,c[0]->mssum[c[0]->rev^1]));
	return this;
}

inline void Node::make_same(int ndata)
{
	data=ndata;
	same=true;
	rev=false;
	sum=size*ndata;
	if (ndata<0)
		msum=mssum[0]=mssum[1]=ndata;
	else 
		msum=mssum[0]=mssum[1]=size*ndata;
}

inline void Node::pass()
{
	if (same)
	{
		rev=same=false;
		if (c[0]!=null)
			c[0]->make_same(data);
		if (c[1]!=null)
			c[1]->make_same(data);
	}
	else if (rev)
	{
		rev=false;
		swap(c[0],c[1]);
		if (c[0]!=null)
			c[0]->rev^=1;
		if (c[1]!=null)
			c[1]->rev^=1;
	}
	else return ;
	rz();
}

struct Splay
{
		Node *root;
		Splay()
		{
			null->size=0;
			root=new Node();
			root->size=2;
			root->c[1]=new Node();
			null->data=null->msum=null->mssum[0]=null->mssum[1]=-oo;
			root->data=root->msum=root->mssum[0]=root->mssum[1]=-oo;
			root->c[1]->data=root->c[1]->msum=root->c[1]->mssum[0]=root->c[1]->mssum[1]=-oo;
		}
		void finish(bool d)
		{
			Node *t=null->c[d],*p=root->c[!d];
			while(t!=null)
			{
				t=null->c[d]->c[d];
				null->c[d]->c[d]=p;
				p=null->c[d]->rz();
				null->c[d]=t;
			}
			root->c[!d]=p;
			root->rz();
		}
		void zig(bool d)
		{
			Node *p=root->c[d];
			root->c[d]=null->c[d];
			null->c[d]=root;
			root=p;
		}
		void zigzig(bool d)
		{
			Node *p=root->c[d]->c[d];
			root->c[d]->c[d]=null->c[d];
			null->c[d]=root->c[d];
			root->c[d]=root->c[d]->c[!d];
			root->rz();
			null->c[d]->c[!d]=root;
			root=p;
		}
		void select(int k)
		{
			int t;
			while(true)
			{
				root->pass();
				bool d=(k>(t=root->c[0]->size));
				if (k==t || root->c[d]==null)
					break;
				root->c[d]->pass();
				if (d) k-=t+1;
				bool dd=(k>(t=root->c[d]->c[0]->size));
				if (k==t || root->c[d]->c[dd]==null)
				{
					zig(d);
					break;
				}
				if (dd) k-=t+1;
				if (d==dd) zigzig(d);
				else zig(d),zig(dd);
			}
			finish(0);
			finish(1);
			root->rz();
		}
		inline void insert(int pos,int tot)
		{
			Node *p=null,*t;
			while(tot--)
			{
				t=new Node();
				scanf("%d",&t->data);
				t->c[0]=p;
				p=t->rz();
			}
			getRange(pos+1,0);
			root->c[1]->c[0]=p;
			root->c[1]->rz();
			root->rz();
		}
		inline void erase(int pos,int tot)
		{
			getRange(pos,tot);
			root->c[1]->c[0]=null;
			root->c[1]->rz();
			root->rz();
		}
		inline void getRange(int pos,int tot)
		{
			select(pos-1);
			Node *oldroot=root;
			root=root->c[1];
			select(tot);
			oldroot->c[1]=root;
			root=oldroot->rz();
		}
		inline int getmax()
		{
			root->pass();
			root->rz();
			return root->msum;
		}
		inline int getsum(int pos,int tot)
		{
			getRange(pos,tot);
			return root->c[1]->c[0]->sum;
		}
		inline void make_same(int pos,int tot,int c)
		{
			getRange(pos,tot);
			root->c[1]->c[0]->make_same(c);
			root->c[1]->rz();
			root->rz();
		}
		inline void reverse(int pos,int tot)
		{
			getRange(pos,tot);
			root->c[1]->c[0]->rev^=1;
			root->c[1]->c[0]->pass();
			root->c[1]->rz();
			root->rz();
		}
}tree;

int main()
{
	freopen("seq2005.in","r",stdin);
	freopen("seq2005.out","w",stdout);
	int N,M;
	scanf("%d%d",&N,&M);
	tree.insert(0,N);
	for(int i=1;i<=M;i++)
	{
		char command[20];
		int pos,tot;
		scanf(" %s",command);
		switch (command[0])
		{
			case 'I':
				scanf("%d%d",&pos,&tot);
				tree.insert(pos,tot);
				break;
			case 'D':
				scanf("%d%d",&pos,&tot);
				tree.erase(pos,tot);
				break;
			case 'M':
				if (command[2]=='K')
				{
					scanf("%d%d%d",&pos,&tot,&N);
					tree.make_same(pos,tot,N);
				}
				else 
					printf("%d\n",tree.getmax());
				break;
			case 'R':
				scanf("%d%d",&pos,&tot);
				tree.reverse(pos,tot);
				break;
			case 'G':
				scanf("%d%d",&pos,&tot);
				printf("%d\n",tree.getsum(pos,tot));
				break;
		}
	}
	return 0;
}
