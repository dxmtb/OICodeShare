/*
ID: dxmtb
PROG: SPOJ2373 Order statistic set
TIME: 2010.7.5
STATE: Solved
MEMO: SBT
*/
#include <cstdio>
using namespace std;

const int MAXN=200001;

class SBT
{
	public:
		void ins(int num){if (!find(root,num))insert(root,num);}
		void del(int num){if (find(root,num))erase(root,num);}
		void sel(int num){select(root,num);}
		int cou(int num){return rank(root,num);}
		SBT(){tt=0;root=0;}
	private:
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
		void select(int &t,int v)
		{
			if (!t||s[t]<v)printf("invalid\n");
			else if (v==s[l[t]]+1)printf("%d\n",key[t]);
			else if (v<=s[l[t]])
				select(l[t],v);
			else select(r[t],v-s[l[t]]-1);
		}
		int rank(int &t,int v)
		{
			if (!t)return 1;
			if (v<=key[t])return rank(l[t],v);
			else return s[l[t]]+1+rank(r[t],v);
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
			else if (v<key[t]) return erase(l[t],v);
			else return erase(r[t],v);
		}
		bool find(int t,int v)
		{
			if (!t)return false;
			if (v<key[t])return find(l[t],v);
			else return (key[t]==v)||find(r[t],v);
		}
}tree;

int main()
{
	int n;
	scanf("%d\n",&n);
	char str[100];
	for(int i=0,num;i<n;i++)
	{
		char t;
		fgets(str,100,stdin);
		sscanf(str,"%c%d",&t,&num);
		switch(t)
		{
			case 'I':tree.ins(num);break;
			case 'D':tree.del(num);break;
			case 'K':tree.sel(num);break;
			case 'C':printf("%d\n",tree.cou(num)-1);break;
			default :return 1;
		}
	}
	return 0;
}
