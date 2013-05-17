/*
ID: dxmtb
PROG: 数字组合
TIME: 2010.11.9
STATE: Solved
MEMO: dp
*/
#include <cstdio>
using namespace std;

const int MAXM=10005,MAXN=105;
const int oo=0x7fffffff;

int N,M,a[MAXN];
int d[MAXM];
int main()
{
	freopen("compages.in","r",stdin);
	freopen("compages.out","w",stdout);
	scanf("%d%d",&N,&M);
	for(int i=0;i<N;i++)
		scanf("%d",a+i);
	for(int j=1;j<=M;j++)
		d[j]=-oo;
	d[0]=1;
	for(int i=0;i<N;i++)
		for(int j=M;j>=a[i];j--)
			if (d[j-a[i]]>=0)
			{
				if (d[j]<0) d[j]=d[j-a[i]];
				else d[j]+=d[j-a[i]];
			}
	printf("%d\n",d[M]);
	return 0;
}
