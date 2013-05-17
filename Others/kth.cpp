/*
ID: dxmtb
PROG: GDOI2006 The kth element
TIME: 2011.02.17
STATE: Solved
MEMO: 二分答案+平衡树
*/
#include <cstdio>

using namespace std;

const int MAXN=20005;
const int oo=~0u>>1;

class SBT
{
	private:
		int key[MAXN];
		int s[MAXN],rep[MAXN],left[MAXN],right[MAXN],w[MAXN];
		void right_rotate(int &t)
		{
			int k=left[t];
			left[t]=right[k];
			right[k]=t;
			s[k]=s[t];rep[k]=rep[t];
			s[t]=s[left[t]]+s[right[t]]+1;
			rep[t]=rep[left[t]]+rep[right[t]]+w[t];
			t=k;
		}
		void left_rotate(int &t)
		{
			int k=right[t];
			right[t]=left[k];
			left[k]=t;
			s[k]=s[t];rep[k]=rep[t];
			s[t]=s[left[t]]+s[right[t]]+1;
			rep[t]=rep[left[t]]+rep[right[t]]+w[t];
			t=k;
		}
		void maintain(int &t,bool flag)
		{
			if (!flag)
				if (s[left[left[t]]]>s[right[t]])
					right_rotate(t);
				else if (s[right[left[t]]]>s[right[t]])
				{
					left_rotate(left[t]);
					right_rotate(t);
				} 
				else return;
			else 
				if (s[right[right[t]]]>s[left[t]])
					left_rotate(t);
				else if (s[left[right[t]]]>s[left[t]])
				{
					right_rotate(right[t]);
					left_rotate(t);
				}
				else return;
			maintain(left[t],false);
			maintain(right[t],true);
			maintain(t,true);
			maintain(t,false);
		}
		void insert(int &t,int v)
		{
			if (t==0)
			{
				t=++tot;
				key[t]=v;
				s[t]=rep[t]=w[t]=1;
				left[t]=right[t]=0;
				return ;
			}
			rep[t]++;
			if (v==key[t]) {w[t]++; return ;}
			if (v>key[t])
				insert(right[t],v);
			else if (v<key[t])
				insert(left[t],v);
			s[t]=s[left[t]]+1+s[right[t]];
			maintain(t,v>key[t]);
		}
		int rank(int t,int v,int &equal)
		{
			if (t==0) return 0;
			if (v==key[t])
			{
				equal+=w[t];
				return rep[left[t]];
			}
			if (v>key[t])
			{
				return rep[t]-rep[right[t]]+
				    rank(right[t],v,equal);
			}
			else return rank(left[t],v,equal);
		}
	public:
		int root,tot;
		void clear(){tot=root=0;}
		void insert(int v)
		{
			insert(root,v);
		}
		int rank(int v,int &equal)
		{
			return rank(root,v,equal);
		}
	/*	bool check(int t)
		{
			if (t==0) return true;
			if (rep[t]!=rep[left[t]]+w[t]+rep[right[t]])
				return false;
			return check(left[t])&&check(right[t]);
		}*/
}tree;

int N,K;
int sum[MAXN];

void solve()
{
	int l=-oo,r=oo;
	while(l<r)
	{
		int ans=(l+r)/2;
		int equal=0,tmp=0;
		tree.clear();
		tree.insert(0);
		for(int i=1;i<=N;i++)
		{
			tmp+=tree.rank(ans-sum[i],equal);
			if (tmp>K)
				break;
			tree.insert(-sum[i]);
		/*	printf("%d %d\n",tmp,equal);
			if (!tree.check(tree.root))
				printf("wrong!\n");*/
		}
		if (tmp<K&&tmp+equal>=K)
		{
			printf("%d\n",ans);
			return ;
		}
//		break;
		if (tmp>=K) r=ans-1;
		else l=ans+1;
	}
	if (l==r) printf("%d\n",l);
}

int main()
{
	freopen("kth.in","r",stdin);
	freopen("kth.out","w",stdout);
	scanf("%d%d",&N,&K);
	for(int i=1;i<=N;i++)
	{
		scanf("%d",sum+i);
		sum[i]+=sum[i-1];
	}
	solve();
	return 0;
}
