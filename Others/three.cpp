/*
ID: dxmtb
PROG: 三元数对
TIME: 2010.9.18
STATE: Solved
MEMO: BST
*/
#include <cstdio>
#include <cstring>
using namespace std;

const int MAXN=30005;

#define init(x) memset(x,0,sizeof(x))
class BinaryTree
{
	private:
		int root,l[MAXN],r[MAXN],s[MAXN],key[MAXN],cf[MAXN],tot;
		void insert(int &t,int num)
		{
			if (!t)
			{
				key[t=++tot]=num;
				cf[t]=s[t]=1;
				l[t]=r[t]=0;
				return ;
			}
			s[t]++;
			if (num==key[t])
			{
				cf[t]++;
				return;
			}
			if (num<key[t]) insert(l[t],num);
			else insert(r[t],num);
		}
		int rank0(int t,int num)
		{
			if (!t)return 0;
			if (num<key[t]) return rank0(l[t],num);
			else 
			{
				if (num==key[t])return s[l[t]];
				return s[l[t]]+cf[t]+rank0(r[t],num);
			}
		}
		int rank1(int t,int num)
		{
			if (!t)return 0;
			if (num>key[t]) return rank1(r[t],num);
			else 
			{
				if (num==key[t])return s[r[t]];
				return rank1(l[t],num)+cf[t]+s[r[t]];
			}
		}
	public:
		void insert(int num){insert(root,num);}
		int rank(int type,int num){return type?rank1(root,num):rank0(root,num);}
		int size(){return tot;}
		void clear()
		{
			init(l);init(s);
			init(r);init(key);
			init(cf);
			tot=0;root=0;
		}
}tree;

int n;
int a[MAXN];
int d1[MAXN],d2[MAXN];
long long re;

void solve1()
{
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<i;j++)
			if (a[j]<a[i])
				d1[i]++;
		for(int j=i+1;j<n;j++)
			if (a[j]>a[i])
				d2[i]++;
	}
	for(int i=0;i<n;i++)
		re+=(long long)d1[i]*d2[i];
}

void solve2()
{
	tree.insert(a[0]);
	for(int i=1;i<n;i++)
	{
		d1[i]=tree.rank(0,a[i]);
		tree.insert(a[i]);
	}
	tree.clear();
	d2[n-1]=0;
	tree.insert(a[n-1]);
	for(int i=n-2;i>=0;i--)
	{
		d2[i]=tree.rank(1,a[i]);
		tree.insert(a[i]);
	}
	for(int i=0;i<n;i++)
		re+=(long long)(d1[i])*d2[i];
}

int main()
{
	freopen("three.in","r",stdin);
	freopen("three.out","w",stdout);
	scanf("%d",&n);
	for(int i=0;i<n;i++)
		scanf("%d",a+i);
//	solve1();
	if (n<=2000) solve1();
	else solve2();
	printf("%lld\n",re);
	return 0;
}
