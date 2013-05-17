/*
ID: dxmtb
PROG: NOI2010 超级钢琴
TIME: 2010.10.15
STATE: Solved
MEMO: rmq+堆
*/
#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long LL;

const int MAXN=500005;
const int two[]={1,2,4,8,16,32,64,128,256,512,1024,2048,4096,1<<13,
		1<<14,1<<15,1<<16,1<<17,1<<18,1<<19};

struct Node
{
	int i,j,l,r,data;
	Node(int a=0,int b=0,int c=0,int d=0,int e=0)
		:i(a),j(b),l(c),r(d),data(e){}
};

int N,L,R,F[MAXN][20],A[MAXN],sum[MAXN];
LL re;
vector<Node> heap;

inline int rmq(int l,int r,int &j)
{
	int f,d=r-l+1;
	for(f=0;two[f]<=d;f++);
	f--;
	if (sum[F[l][f]]<sum[F[r-two[f]+1][f]])
	{
		j=F[l][f];
		return sum[F[l][f]];
	}
	else
	{
		j=F[r-two[f]+1][f];
		return sum[F[r-two[f]+1][f]];
	}
}

inline bool operator < (const Node &a,const Node &b)
{
	return a.data<b.data;
}

inline void push_Node(int i,int l,int r)
{
	int j;
	LL data=sum[i]-rmq(l,r,j);
	heap.push_back(Node(i,j,l,r,data));
}

int main()
{
	freopen("piano.in","r",stdin);
	freopen("piano.out","w",stdout);
//init
	register int i;
	int K;
	scanf("%d%d%d%d",&N,&K,&L,&R);
	F[0][0]=0;
	for(i=1;i<=N;i++)
	{
		scanf("%d",A+i);
		sum[i]=sum[i-1]+A[i];
		F[i][0]=i;
	}
#define irmq(j)\
	if (two[j]<=R-L+1)\
		for(i=0;i+two[j]-1<=N;i++)\
		{\
			if (sum[F[i][j-1]]<sum[F[i+two[j-1]][j-1]])\
				F[i][j]=F[i][j-1];\
			else \
				F[i][j]=F[i+two[j-1]][j-1];\
		}\
	else\
		goto OUT;
	irmq(1) irmq(2) irmq(3) irmq(4) irmq(5) irmq(6) irmq(7)
	irmq(8) irmq(9) irmq(10) irmq(11) irmq(12) irmq(13) irmq(14)
	irmq(15) irmq(16) irmq(17) irmq(18) irmq(19)
	OUT:
//	return 0;
	for(i=L;i<=N;i++)
		push_Node(i,max(0,i-R),i-L);
	make_heap(heap.begin(),heap.end());
//init
	while(K--)
	{
		re+=(LL)heap[0].data;
		LL l=heap[0].l,r=heap[0].r,j=heap[0].j,i=heap[0].i;
		pop_heap(heap.begin(),heap.end());
		heap.pop_back();
		if (l<j) 
		{
			push_Node(i,l,j-1);
			push_heap(heap.begin(),heap.end());
		}
		if (j<r)
		{
			push_Node(i,j+1,r);
			push_heap(heap.begin(),heap.end());
		}
	}
	printf("%lld\n",re);
	return 0;
}

