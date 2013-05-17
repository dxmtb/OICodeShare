/*
 * Problem: 1892: Match 
 * Time: 2011.07.08
 * Author: dxmtb
 * State: Solved
 * Memo: KMP变种
*/
#include <cstdio>
#include <vector>
#include <cstring>
using namespace std;

const int MAXN=500005,MAXS=10005;

int N,M,S;

struct BitArray
{
	int sum[MAXS];
	void init(){memset(sum,0,sizeof(sum));}
	int getsum(int pos)
	{
		int re=0;
		while(pos>=1)
		{
			re+=sum[pos];
			pos-=pos&(-pos);
		}
		return re;
	}
	void insert(int pos,int val)
	{
		while(pos<=S)
		{
			sum[pos]+=val;
			pos+=pos&(-pos);
		}
	}
}s1,s2;

int A[MAXN],B[MAXN];
int next[MAXN];

inline bool cmp(int ch1,int ch2)
{
	return (s1.getsum(ch1-1)==s2.getsum(ch2-1));
}

void initKmp()
{
	next[0]=-1;
	s1.init();
	s2.init();
	for(int i=1,j=-1;i<M;i++)
	{
		while(j>=0 && !cmp(B[i],B[j+1]))
		{
			int L=j-next[j];
			for(int k=0;k<L;k++)
			{
				s1.insert(B[i-1-j+k],-1);
				s2.insert(B[j-L+k+1],-1);
			}
			j=next[j];
		}
		if (cmp(B[i],B[j+1]))
		{
			j++;
			s1.insert(B[i],1);
			s2.insert(B[j],1);
		}
		next[i]=j;
	}
}

vector<int> re;
void Kmp()
{
	s1.init();
	s2.init();
	for(int i=0,j=-1;i<N;i++)
	{
		while(j>=0 && (j==M-1 || !cmp(A[i],B[j+1])))
		{
			int L=j-next[j];
			for(int k=0;k<L;k++)
			{
				s1.insert(A[i-1-j+k],-1);
				s2.insert(B[j-L+k+1],-1);
			}
			j=next[j];
		}
		if (cmp(A[i],B[j+1]))
		{
			j++;
			s1.insert(A[i],1);
			s2.insert(B[j],1);
		}
		if (j==M-1)
			re.push_back(i+1-M+1);
	}
}

int main()
{
	scanf("%d%d%d",&N,&M,&S);
	for(int i=0;i<N;i++)
		scanf("%d",A+i);
	for(int i=0;i<M;i++)
		scanf("%d",B+i);
	initKmp();
	Kmp();
	printf("%d\n",(int)re.size());
	for(int i=0;i<(int)re.size();i++)
		printf("%d\n",re[i]);
	return 0;
}
