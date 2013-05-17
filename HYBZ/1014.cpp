/*
 * Problem: [JSOI2008]火星人prefix
 * Time: 2011.05.13
 * Author: dxmtb
 * State: Solved
 * Memo: 平衡树维护hash值
*/
 #include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

typedef long long s64;

const int MAXL=100005,MAXM=150005;
const int MO=1741013;
const int seed=133;

int powseed[MAXL];
inline int pow(int n)
{
	return powseed[n];
}

struct Node
{
	char ch;
	int hash,size;
	Node *c[2];
	Node();
	Node(char _ch,Node *c0,Node *c1):ch(_ch){c[0]=c0,c[1]=c1;}
	void *operator new(size_t,void *p){return p;}
	Node *rz()
	{
		size=c[0]->size+1+c[1]->size;
		hash=((s64)c[0]->hash*pow(c[1]->size+1)%MO+(s64)ch*pow(c[1]->size)%MO+c[1]->hash)%MO;
		return this;
	}
}pool[MAXM],*mem=pool+1,*null=pool;

Node::Node()
{
	ch='\0';
	hash=size=0;
	c[0]=c[1]=null;
}

struct Splay
{
	Node *root;
	Splay()
	{
		root=new (mem++)Node('\0',null,null);
		root->c[1]=new (mem++)Node('\0',null,null);
		root->c[1]->rz();
		root->rz();
	}
	void init()
	{
		char str[MAXL];
		scanf("%s",str);
		int N=strlen(str);
		Node *p=null;
		for(int i=0;i<N;i++)
		{
			p=new (mem++)Node(str[i],p,null);
			p->rz();
		}
		root->c[1]->c[0]=p;
		root->c[1]->rz();
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
		null->c[d]->c[!d]=root->rz();
		root=p;
	}
	void finish(bool d)
	{
		Node *p=root->c[!d],*t=null->c[d];
		while(t!=null)
		{
			t=null->c[d]->c[d];
			null->c[d]->c[d]=p;
			p=null->c[d]->rz();
			null->c[d]=t;
		}
		root->c[!d]=p;
	}
	void select(int k)
	{
		int t;
		while(true)
		{
			bool d=(k>(t=root->c[0]->size));
			if (k==t || root->c[d]==null)
				break;
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
	void insert(int k,char ch)
	{
		select(k);
		Node *oldroot=root;
		root=root->c[1];
		select(0);
		root->c[0]=new (mem++)Node(ch,null,null);
		root->c[0]->rz();
		root->rz();
		oldroot->c[1]=root;
		root=oldroot->rz();
	}
	void change(int k,char ch)
	{
		select(k);
		root->ch=ch;
		root->rz();
	}
	void find(int k,int l)
	{
		select(k-1);
		Node *oldroot=root;
		root=root->c[1];
		select(l);
		oldroot->c[1]=root;
		root=oldroot->rz();
	}
	bool check(int x,int y,int mid)
	{
		if (mid==0) 
			return true;
		find(x,mid);
		int h1=root->c[1]->c[0]->hash;
		find(y,mid);
		int h2=root->c[1]->c[0]->hash;
		if (h1==h2) return true;
		else return false;
	}
	int query(int x,int y)
	{
		int l=0,r=root->size-2-max(x,y)+1;
		if (check(x,y,r)) return r;
		while(l+1<r)
		{
			int mid=(l+r)/2;
			if (check(x,y,mid)) l=mid;
			else r=mid-1;
		}
		if (l==r || !check(x,y,r)) return l;
		else return r;
	}
}tree;

char str[MAXL];
int M;
int main()
{
	freopen("1014.in","r",stdin);
	powseed[0]=1;
	for(int i=1;i<MAXL;i++)
		powseed[i]=powseed[i-1]*seed%MO;
	tree.init();
	scanf("%d",&M);
	while(M--)
	{
		char com='\0';
		int a,b;
		scanf(" %c%d",&com,&a);
		if (com=='Q')
		{
			scanf("%d",&b);
			printf("%d\n",tree.query(a,b));
		}
		else if (com=='R')
		{
			scanf(" %c",&com);
			tree.change(a,com);
		}
		else //(com=='I')
		{
			scanf(" %c",&com);
			tree.insert(a,com);
		}
	}
	return 0;
}
