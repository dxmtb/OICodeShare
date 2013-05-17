/*
ID: dxmtb
PROG: NOI2004 郁闷的出纳员
TIME: 2010.9.6
STATE: Solved
MEMO: SBT
*/
#include <cstdio>
#include <iostream>
using namespace std;

const int MAXN=100005;

class SBT
{
	public:
		inline int size(){return s[root];}
		inline void insert(int num){ins(root,num);}
		inline int select(int k){return select(root,k);}
		inline void erase(int num)
		{
			era(root,num);
			maintain(root,true);
			maintain(root,false);
		}
	private:
		int s[MAXN],key[MAXN],l[MAXN],r[MAXN],top,root,tch;
		inline void clear(int &t)
		{
			if (!t)return ;
			clear(l[t]);clear(r[t]);
			s[t]=0;t=0;l[t]=r[t]=0;key[t]=0;
		}
		inline int erase(int &t,int v)
		{
			s[t]--;
			if (key[t]==v||(v<key[t]&&!l[t])||(v>key[t]&&!r[t]))
			{
				int temp=key[t];
				if (!l[t]||!r[t])t=l[t]+r[t];
				else key[t]=erase(l[t],v+1);
				return temp;
			}
			else if (v<key[t])return erase(l[t],v);
			else return erase(r[t],v);
		}
		inline int era(int &t,int num)
		{
			if (!t)return 0;
			int temp=0;
			if (key[t]<num)
			{
				temp=s[l[t]]+era(r[t],num);
				clear(l[t]);
				s[t]-=temp;
				erase(t,key[t]);
				temp++;
				return temp;
			}
			else 
			{
				temp=era(l[t],num);
				s[t]-=temp;
				return temp;
			}
		}			
		inline void right(int &t)
		{
			int k=l[t];
			l[t]=r[k];
			r[k]=t;
			s[k]=s[t];
			s[t]=s[l[t]]+s[r[t]]+1;
			t=k;
		}
		inline void left(int &t)
		{
			int k=r[t];
			r[t]=l[k];
			l[k]=t;
			s[k]=s[t];
			s[t]=s[l[t]]+s[r[t]]+1;
			t=k;
		}
		inline void maintain(int &t,bool flag)
		{
			if (!flag)
			{
				if (s[l[l[t]]]>s[r[t]])	right(t);
				else if (s[r[l[t]]]>s[r[t]]) {left(l[t]);right(t);}
				else return;
			}
			else
			{
				if (s[r[r[t]]]>s[l[t]]) left(t);
				else if (s[l[r[t]]]>s[l[t]]) {right(r[t]);left(t);}
				else return;
			}
			maintain(l[t],false);
			maintain(r[t],true);
			maintain(t,true);
			maintain(t,false);
		}
		inline void ins(int &t,int v)
		{
			if (!t)key[t=++top]=v,s[t]=1,l[t]=r[t]=0;
			else 
			{
				s[t]++;
				if (v<key[t])ins(l[t],v);
				else ins(r[t],v);
				maintain(t,v>=key[t]);
			}
		}
		inline int select(int t,int k)
		{
			if (s[l[t]]+1==k)return key[t];
			if (k<=s[l[t]]) return select(l[t],k);
			else return select(r[t],k-s[l[t]]-1);
		}
};

int n,m,re;
int add;
SBT tree;

int main()
{
	freopen("cashier.in","r",stdin);
	freopen("cashier.out","w",stdout);
	scanf("%d%d\n",&n,&m);
	for(int i=0;i<n;i++)
	{
		char ch;
		int k;
		scanf("%c%d\n",&ch,&k);
		switch (ch)
		{
			case 'I':
				{
					if (k>=m)
					{
						tree.insert(k-add);
						re++;
					}
					break;
				}
			case 'A':
				{
					add+=k;
					break;
				}
			case 'S':
				{
					add-=k;
					tree.erase(m-add);
					break;
				}
			case 'F':
				{
					if (k>tree.size()) printf("-1\n");
					else printf("%d\n",tree.select(tree.size()-k+1)+add);
				}
		}
	}
	printf("%d\n",re-tree.size());
	return 0;
}
