/*
  ID: dxmtb1
  PROG: kimbits
  LANG: C++
*/
#include <cstdio>
#include <cstring>
using namespace std;

const int MAXN=31;

long long d[MAXN+1][MAXN+1];
long long N,L,I;

int main()
{
	freopen("kimbits.in","r",stdin);
	freopen("kimbits.out","w",stdout);
	scanf("%lld%lld%lld",&N,&L,&I);
	for(int i=0;i<=L;i++)
		d[0][i]=1;
	for(int i=1;i<=N;i++)
	{
		d[i][0]=1;
		for(int j=1;j<=L;j++)
			d[i][j]=d[i-1][j]+d[i-1][j-1];
	}
	int t1=L;
	for(int i=N;i>0&&I;i--)
		if(d[i-1][t1]<I)
			printf("1"),I-=d[i-1][t1--];
		else
			printf("0");
	printf("\n");
	return 0;
}
