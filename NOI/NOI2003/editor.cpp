/*
ID: dxmtb
PROG: NOI2003 文本编辑器
TIME: 2011.02.21
STATE: Solved
MEMO: zkw splay
*/
#include <cstdio>
#include <stack>
#include <cstring>
#include <string>
using namespace std;

const int MAXN=1025;
const int MAXL=10;
const int oo=~0u>>1;

struct Node
{
	Node *c[2];
	int size;
	char chr;
	Node(){c[0]=c[1]=this;}
	Node *rz()
	{
		return size=c[0]->size+c[1]->size+1,this;
	}
	Node(char _ch,Node *_c0,Node *_c1):
		chr(_ch){c[0]=_c0,c[1]=_c1;}
};	

struct Splay
{
	Node *root,*null;
	Splay()
	{
		null=new Node();
		root=(new Node(*null))->rz();
		Node *oldroot=root;
		root=(new Node('\0',oldroot->c[0],oldroot))->rz();
		oldroot->c[0]=null;
		oldroot->rz();
	}
	void zig(bool d)
	{
		Node *t=root->c[d];
		root->c[d]=null->c[d];
		null->c[d]=root;
		root=t;
	}
	void zigzig(bool d)
	{
		Node *t=root->c[d];
		root->c[d]=root->c[d]->c[!d];
		t->c[!d]=root->rz();
		root=t->c[d];
		t->c[d]=null->c[d];
		null->c[d]=t;
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
	}
	void select(int k)
	{
		int t;
		while(true)
		{
			bool d=k>(t=root->c[0]->size);
			if (k==t||root->c[d]==null)
				break;
			if (d) k-=t+1;
			bool dd=k>(t=root->c[d]->c[0]->size);
			if (k==t||root->c[d]->c[dd]==null)
			{
				zig(d);
				break;
			}
			if (dd) k-=t+1;
			if (d!=dd) zig(d),zig(dd);
			else zigzig(d);
		}
		finish(0),finish(1);
		root->rz();
	}
	Node *buildtree(string str)
	{
		Node *p,*t;
		int length=str.length();
		p=new Node(str[0],null,null);
		p->size=length;
		t=p;
		for(int i=1;i<length;i++)
		{
			t->c[1]=new Node(str[i],null,null);
			t->c[1]->size=length-i;
			t=t->c[1];
		}
		return p;
	}
	void ins(int P,string str)
	{
		Node *p=buildtree(str);
		select(P);
		Node *oldroot=root;
		root=root->c[1];
		select(0);
		root->c[0]=p;	
		root->rz();
		oldroot->c[1]=root;
		root=oldroot->rz();
	}
	void getRange(int l,int r)
	{
		select(l);
		Node *oldroot=root;
		root=root->c[1];
		select(r-l+1);
		oldroot->c[1]=root;
		root=oldroot->rz();
	}
}tree;

int P;

void move() {scanf("%d",&P);}
void prev() {P--;}
void next() {P++;}

void travel(Node *p)
{
	stack<pair<Node*,int> > s;
	s.push(make_pair(p,0));
	while(s.size())
	{
		pair<Node*,int> now=s.top();s.pop();
		now.second++;
		if (now.second==1)
		{
			s.push(now);
			if (now.first->c[0]!=tree.null)
				s.push(make_pair(now.first->c[0],0));
		}
		else if (now.second==2)
		{
			s.push(now);
			printf("%c",now.first->chr);
			if (now.first->c[1]!=tree.null)
				s.push(make_pair(now.first->c[1],0));
		}
	}
}

void get()
{
	int k;
	scanf("%d",&k);
	tree.getRange(P,P+k-1);
	travel(tree.root->c[1]->c[0]);
	printf("\n");
}

void insert()
{
	int k;
	scanf("%d",&k);
	string str;
	while(k)
	{
		char s[100];
		fgets(s,sizeof(s)-1,stdin);
		if (s[strlen(s)-1]=='\n')
			s[strlen(s)-1]='\0';
		if (s[strlen(s)-1]=='\r')
			s[strlen(s)-1]='\0';
		str+=s;
		k-=strlen(s);
	}
	tree.ins(P,str);
}

void erase()
{
	int k;
	scanf("%d",&k);
	tree.getRange(P,P+k-1);
	tree.root->c[1]->c[0]=tree.null;
}

int main()
{
	freopen("editor2003.in","r",stdin);
	freopen("editor2003.out","w",stdout);
	int T;
	scanf("%d",&T);
	while(T--)
	{
		char opt[MAXL];
		scanf("%s",opt);
		switch (opt[0])
		{
			case 'M':move();break;
			case 'I':insert();break;
			case 'D':erase();break;
			case 'N':next();break;
			case 'P':prev();break;
			case 'G':get();break;
			default:return -1;
		}
	}
	return 0;
}
