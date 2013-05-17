/*
ID: dxmtb
PROG: 数列操作
TIME: 2010.4.29
STATE: Solved
MEMO: 线段树
*/
#include <cstdio>
#include <cstring>
using namespace std;

const int MAXN=100000;

struct Node
{
	Node()
	{s=0;left=right=NULL;}
	int s,l,r;
	Node *left,*right;
};

class Ptree
{
public:
	void make(int size,int first[])
	{
		head=new Node;
		make_tree(head,1,size+1,first);
	}
	void make_tree(Node *x,int l,int r,int first[])
	{
		x->l=l;
		x->r=r;
		if (l==r)return;
		if (r-l==1)
		{
			x->s=first[l-1];
			return;
		}
		x->left=new Node;
		make_tree(x->left,l,(l+r)/2,first);
		x->right=new Node;
		make_tree(x->right,(l+r)/2,r,first);
		x->s=x->left->s+x->right->s;
	}
	void insert(Node *x,int k,int d)
	{
		if (x->r==x->l)return;
		x->s+=d;
		if(x->r-x->l==1)
			return;
		int mid=(x->l+x->r)/2;
		if (mid>k)
			insert(x->left,k,d);
		else insert(x->right,k,d);
	}
	int check(Node *x,int s,int t)
	{
		if (x==NULL)return 0;
		if (s>=t)return 0;
		if (s==x->l&&t==x->r)return x->s;
		int mid=(x->l+x->r)/2;
		if (mid>=t)
			return check(x->left,s,t);
		else if (mid<=s)
			return check(x->right,s,t);
		else return check(x->left,s,mid)+check(x->right,mid,t);
	}
	void add(int a,int b)
	{
		insert(head,a,b);
	}
	int sum(int a,int b)
	{
		return check(head,a,b+1);
	}
private:	
	Node *head;
};

int n,m;
Ptree t;

void init()
{
	scanf("%d",&n);
	int first[MAXN];
	for(int i=0;i<n;i++)
		scanf("%d",&first[i]);
	t.make(n,first);
	scanf("%d",&m);	
}

int main() 
{
	freopen("shulie.in","r",stdin);
	freopen("shulie.out","w",stdout);
	init();
	for(int i=0;i<m;i++)
	{
		char command[4];
		int a,b;
		scanf("%s%d%d",command,&a,&b);
		if (strcmp(command,"SUM")==0)
			printf("%d\n",t.sum(a,b));
		else 
			t.add(a,b);
	}
    return 0;
}
