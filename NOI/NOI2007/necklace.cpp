/*
ID: dxmtb
PROG: NOI2007 项链工厂
TIME: 2011.03.08
STATE: Solved
MEMO: 线段树
*/
#include <cstdio>
#include <assert.h>
#include <algorithm>
using namespace std;

#define change \
	t1=((t1-onepos)*reverse+1)%N;\
	if (t1<=0) t1+=N;\
	t2=((t2-onepos)*reverse+1)%N;\
	if (t2<=0) t2+=N

const int MAXN=500005;

struct Node
{
	int l,r,mid,color,sum,lcolor,rcolor;
	Node *left,*right;
	Node(int a,int b):l(a),r(b){}
	Node(){}
	void *operator new(unsigned,void *p){return p;}
}pool[MAXN*2],*mem=pool;

class STree
{
	private:
		Node *root;
		void build(Node *&v,int l,int r)
		{
			v=new (mem++)Node(l,r);
			if (l==r)
			{
				scanf("%d",&v->color);
				v->sum=1;
				v->lcolor=v->rcolor=v->color;
				v->mid=l;
				v->left=v->right=NULL;
			}
			else
			{
				int mid=(l+r)/2;
				v->mid=mid;
				build(v->left,l,mid);
				build(v->right,mid+1,r);
				update(v);
			}
		}
		inline void update(Node *v)
		{
			if (v->left->color!=0 && v->right->color!=0 && 
			    v->left->color==v->right->color)
			{
				v->color=v->left->color;
				v->sum=1;
			}
			else
			{
				v->color=0;
				if (v->left->rcolor==v->right->lcolor)
					v->sum=v->left->sum+v->right->sum-1;
				else v->sum=v->left->sum+v->right->sum;
			}
			v->lcolor=v->left->lcolor;
			v->rcolor=v->right->rcolor;
		}
		inline void pass(Node *v)
		{
			if (v->color==0) return ;
			if (v->left && v->color!=v->left->color)
			{
				v->left->color=v->left->rcolor=v->left->lcolor=v->color;
				v->left->sum=1;
			}
			if (v->right && v->color!=v->right->color)
			{
				v->right->color=v->right->rcolor=v->right->lcolor=v->color;
				v->right->sum=1;
			}
			v->lcolor=v->rcolor=v->color;
		}
		int count(Node *v,int l,int r)
		{
			if (l==v->l && r==v->r)
				return v->sum;
			pass(v);
			int mid=v->mid;
			if (l>mid)
				return count(v->right,l,r);
			else if (r<=mid)
				return count(v->left,l,r);
			else
				return count(v->left,l,mid)+count(v->right,mid+1,r)-
					((v->left->rcolor==v->right->lcolor)?1:0);
		}
		void draw(Node *v,int s,int t,int c)
		{
			if (v->l==s && v->r==t)
			{
				v->color=c;
				v->lcolor=v->rcolor=c;
				v->sum=1;
				return ;
			}
			pass(v);
			int mid=v->mid;
			if (s>mid) draw(v->right,s,t,c);
			else if (t<=mid) draw(v->left,s,t,c);
			else 
			{
				draw(v->left,s,mid,c);
				draw(v->right,mid+1,t,c);
			}
			update(v);
		}
		int getcolor(Node *v,int t)
		{
			if (v->l==t && v->r==t)
				return v->color;
			pass(v);
			if (t>v->mid) return getcolor(v->right,t);
			else return getcolor(v->left,t);
		}
	public:
		void build(int N)
		{
			build(root,1,N);
		}
		inline int getcolor(int t)
		{
			if (t==1) return root->lcolor;
			else if (t==root->r) return root->rcolor;
			return getcolor(root,t);
		}
		int count(int l,int r)
		{
			return count(root,l,r);
		}
		void draw(int s,int t,int c)
		{
			draw(root,s,t,c);
		}
}tree;

int N,C,Q;
int onepos;
//int real[MAXN];
int main()
{
	freopen("necklace.in","r",stdin);
	freopen("necklace.out","w",stdout);
	scanf("%d%d",&N,&C);
	tree.build(N);
	onepos=1;
	scanf("%d",&Q);
	int reverse=1;
	while(Q--)
	{
		char command;
		int t1,t2;
		int c1,c2;
		scanf(" %c",&command);
		switch(command)
		{
			case 'R':
				scanf("%d",&t1);
				onepos=(onepos+t1)%N;
				if (onepos==0)
					onepos=N;
				break;
			case 'F':
				reverse*=-1;
				onepos=(N-onepos+2)%N;
				if (onepos==0)
					onepos=N;
				break;
			case 'S':
				scanf("%d%d",&t1,&t2);
				change;
				c1=tree.getcolor(t1);
				c2=tree.getcolor(t2);
				tree.draw(t1,t1,c2);
				assert(tree.getcolor(t1)==c2);
				tree.draw(t2,t2,c1);
				assert(tree.getcolor(t2)==c1);
				break;
			case 'P':	
				scanf("%d%d%d",&t1,&t2,&c1);
				change;
				if (reverse==-1)
					swap(t1,t2);
				if (t1<=t2) tree.draw(t1,t2,c1);
				else {tree.draw(t1,N,c1);tree.draw(1,t2,c1);}
				break;
			case 'C':
				scanf("%c",&command);
				if (command=='S')
				{
					scanf("%d%d",&t1,&t2);
					change;
					if (reverse==-1)
						swap(t1,t2);
					if (t1>t2)
						c1=tree.count(1,t2)+tree.count(t1,N)-
						    ((tree.getcolor(1)==tree.getcolor(N))?1:0);
					else c1=tree.count(t1,t2);
				}
				else
					c1=tree.count(1,N)-((tree.getcolor(1)==tree.getcolor(N))?1:0);
				if (c1==0) c1=1;
				printf("%d\n",c1);
				break;
			default:
				return -1;
		}
/*		for(int i=1;i<=N;i++)
		{
			int t1=i,t2=i;
			change;
			real[i]=tree.getcolor(t1);
			printf("%d ",real[i]);
		}
		printf("\n");*/
	}
	return 0;
}
