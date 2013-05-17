/*
ID: dxmtb
PROG: 奶茶配方
TIME: 2010.7.5
STATE: Solved
MEMO: SBT
*/
#include <cstdio>
using namespace std;

const int MAXN=80000;
const int MAXINT=0x7fffffff;

class SBT
{
public:
	int s[MAXN],l[MAXN],r[MAXN],key[MAXN];
	int tt,root;
	void right(int &t)
		{
			int k=l[t];
			l[t]=r[k];
			r[k]=t;
			s[k]=s[t];
			s[t]=s[l[t]]+s[r[t]]+1;
			t=k;
		}
	void left(int &t)
		{
			int k=r[t];
			r[t]=l[k];
			l[k]=t;
			s[k]=s[t];
			s[t]=s[l[t]]+s[r[t]]+1;
			t=k;
		}
	void maintain(int &t,bool flag)
		{
			if (!flag)
				if (s[l[l[t]]]>s[r[t]])
					right(t);
				else if (s[r[l[t]]]>s[r[t]])
				{
					left(l[t]);
					right(t);
				}
				else return;
			else
				if (s[r[r[t]]]>s[l[t]])
					left(t);
				else if (s[l[r[t]]]>s[l[t]])
				{
					right(r[t]);
					left(t);
				}
				else return;
			maintain(l[t],false);
			maintain(r[t],true);
			maintain(t,true);
			maintain(t,false);
		}
	void insert(int &t,int v)
		{
			if(!t)key[t=++tt]=v,l[t]=r[t]=0,s[t]=1;
			else
			{
				s[t]++;
				if (v<key[t])insert(l[t],v);
				else insert(r[t],v);
				maintain(t,v>=key[t]);
			}
		}
	int erase(int &t,int v)
		{
			s[t]--;
			if (key[t]==v||(v<key[t]&&!l[t])||(v>key[t]&&!r[t]))
			{
				int temp=key[t];
				if (!l[t]||!r[t]) t=l[t]+r[t];
				else key[t]=erase(l[t],v+1);
				return temp;
			}
			else
				if (v<key[t]) return erase(l[t],v);
				else return erase(r[t],v);
		}
	int pred(int v)
	{
		int re=-200000000;
		int t=root;
		while(t)
			if (v>=key[t])
			{
				if (key[t]>re)re=key[t];
				t=r[t];
			}
			else t=l[t];
		return re;
	}
	int succ(int v)
	{
		int re=MAXINT;
		int t=root;
		while(t)
			if (key[t]>=v)
			{
				if (key[t]<re)re=key[t];
				t=l[t];
			}
			else t=r[t];
		return re;
	}
}tree;

inline int abs(int a)
{return a<0?-a:a;}

int n,re;
int s;
int a[MAXN];

int main()
{
	freopen("naicha.in","r",stdin);
	freopen("naicha.out","w",stdout);
	scanf("%d",&n);
	for(int i=0;i<n;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		if (x==s||tree.s[tree.root]==0)
			{tree.insert(tree.root,y);s=x;continue;}
		int a=tree.pred(y),b=tree.succ(y);
		if (y-a<=b-y)
			{	
				tree.erase(tree.root,a);
				re+=y-a;
			}
			else
			{
				tree.erase(tree.root,b);
				re+=b-y;
			}
			re%=1000000;
	}
	printf("%d\n",re);
	return 0;
}
