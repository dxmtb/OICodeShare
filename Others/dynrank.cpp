/*
ID: dxmtb
PROG: 动态排名系统
TIME: 2011.03.12
STATE: Solved
MEMO: 线段树+平衡树
*/
#include <cstdio>

const int maxint=1000000005;
const int MAXN=1000000;

struct SplayNode
{
	int key,size,num;
	SplayNode *c[2];
	SplayNode *rz(){return size=c[0]->size+num+c[1]->size,this;}
	SplayNode(){}
	SplayNode(int _key,SplayNode *c0,SplayNode *c1):key(_key)
		{c[0]=c0,c[1]=c1;num=1;}
	void *operator new (unsigned ,void *p){return p;}
}pool[MAXN],*mem,Tnull,*null=&Tnull;

class Splay
{
	public:
		SplayNode *root;
		void init()
		{
			root=(new (mem++)SplayNode(*null))->rz();
			root->key=maxint;
			root->num=1;
		}
		void zig(bool d)
		{
			SplayNode *p=root->c[d];
			root->c[d]=null->c[d];
			null->c[d]=root;
			root=p;
		}
		void zigzig(bool d)
		{
			SplayNode *p=root->c[d]->c[d];
			root->c[d]->c[d]=null->c[d];
			null->c[d]=root->c[d];
			root->c[d]=root->c[d]->c[!d];
			null->c[d]->c[!d]=root->rz();
			root=p;
		}
		void finish(bool d)
		{
			SplayNode *t=null->c[d],*p=root->c[!d];
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
				if (d==dd) zigzig(d);
				else zig(d),zig(dd);
			}
			finish(0);
			finish(1);
			root->rz();
		}
		void search(int x)
		{
			while(true)
			{
				bool d=(x>root->key);
				if (root->c[d]==null)
					break;
				bool dd=(x>root->c[d]->key);
				if (root->c[d]->c[dd]==null)
				{
					zig(d);
					break;
				}
				if (d==dd) zigzig(d);
				else zig(d),zig(dd);
			}
			finish(0);
			finish(1);
			root->rz();
			if (x>root->key) 
				select(root->c[0]->size+1);
		}
		int rank(int x,int &flag)
		{
			search(x);
			if (root->key==x) flag+=root->num;
			return root->c[0]->size;
		}
		void erase()
		{
			if (root->num>1)
			{
				root->num--;
				return ;
			}
			SplayNode *oldroot=root;
			root=root->c[1];
			select(0);
			root->c[0]=oldroot->c[0];
			root->rz();
		}
		void change(int from,int to)
		{
			search(from);
			erase();
			insert(to);
		}
		void insert(int x)
		{
			search(x);
			if (root->key==x)
			{
				root->num++;
				return ;
			}
			root=new (mem++)SplayNode(x,root->c[0],root);
			root->c[1]->c[0]=null;
			root->c[1]->rz();
			root->rz();
		}
};

struct SegNode
{
	int l,r,mid;
	Splay t;
	SegNode *left,*right;
	SegNode(){}
	SegNode(int _l,int _r):l(_l),r(_r)
	{
		t.init();
		left=right=NULL;
	}
	void *operator new (unsigned ,void *p){return p;}
}Spool[MAXN],*Smem;

int A[MAXN];
class SegmentTree
{
	public:
		SegNode *root;
		void build(SegNode *&v,int l,int r)
		{
			v=new (Smem++)SegNode(l,r);
			v->mid=(l+r)/2;
			for(int i=l;i<=r;i++)
				v->t.insert(A[i]);
			if (l==r)
				return ;
			build(v->left,l,v->mid);
			build(v->right,v->mid+1,r);
		}
		int rank(SegNode *v,int l,int r,int x,int &flag)
		{
			if (v->l==l && v->r==r) return v->t.rank(x,flag);
			if (l>v->mid) return rank(v->right,l,r,x,flag);
			if (r<=v->mid) return rank(v->left,l,r,x,flag);
			return rank(v->left,l,v->mid,x,flag)+
			       rank(v->right,v->mid+1,r,x,flag);
		}
		int select(int i,int j,int k)
		{
			int l=1,r=maxint;
			int mid;
			int flag;
			while(l<r)
			{
				mid=(l+r)/2;
				flag=0;
				int ran=rank(root,i,j,mid,flag)+1;
				if (ran<=k && ran+flag-1>=k) return mid;
				if (ran>k) r=mid-1;
				else l=mid+1;
			}
			return l;
		}
		void change(SegNode *v,int k,int to)
		{
			v->t.change(A[k],to);
			if (v->l==v->r) return ;
			if (k>v->mid) change(v->right,k,to);
			else change(v->left,k,to);
		}
}tree;

int main()
{
	freopen("dynrank.in","r",stdin);
	freopen("dynrank.out","w",stdout);
	int D,N,M;
	null->c[0]=null->c[1]=null;
	scanf("%d",&D);
	while(D--)
	{
		mem=pool;
		Smem=Spool;
		scanf("%d%d",&N,&M);
		for(int i=1;i<=N;i++)
			scanf("%d",A+i);
		tree.build(tree.root,1,N);
		while(M--)
		{
			char com;
			int i,j,k;
			scanf(" %c",&com);
			if (com=='Q')
			{
				scanf("%d%d%d",&i,&j,&k);
				printf("%d\n",tree.select(i,j,k));
			}
			else if (com=='C')
			{
				scanf("%d%d",&i,&j);
				tree.change(tree.root,i,j);
				A[i]=j;
			}
		}
	}
	return 0;
}
