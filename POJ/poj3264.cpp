/*
ID: dxmtb
PROG: poj3264 Balanced Lineup
TIME: 2010.7.22
STATE: Solved
MEMO: RMQ
*/
#include <cstdio>
using namespace std;

const int MAXN=50005,MAXQ=200000;
const int MAXF=17;

int vi[MAXN][MAXF],va[MAXN][MAXF];
int two[MAXF]={1};

int N,Q;

inline int min(int a,int b)
{return a>b?b:a;}
inline int max(int a,int b)
{return a>b?a:b;}

int main()
{
	freopen("lineup.in","r",stdin);
	freopen("lineup.out","w",stdout);
	scanf("%d%d",&N,&Q);
	for(int i=1;i<MAXF;i++)
		two[i]=two[i-1]<<1;
	for(int i=0;i<N;i++)
	{
		scanf("%d",vi[i]);
		va[i][0]=vi[i][0];
	}
	for(int j=1;two[j]<=N;j++)
	for(int i=0;i+two[j]<=N;i++)
			vi[i][j]=min(vi[i][j-1],vi[i+two[j-1]][j-1]),
			va[i][j]=max(va[i][j-1],va[i+two[j-1]][j-1]);
	for(int i=0,l,r;i<Q;i++)
	{
		scanf("%d%d",&l,&r);
		l--;
		int d=r-l,f;
		for(f=0;two[f]<=d;f++);
		--f;
		printf("%d\n",max(va[l][f],va[r-two[f]][f])-
			min(vi[l][f],vi[r-two[f]][f]));
	}
	return 0;
}

