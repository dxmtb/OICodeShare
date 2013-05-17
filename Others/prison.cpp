/*
ID: dxmtb
PROG: prison
TIME: 2010.11.2
STATE: Solved
MEMO: dp
*/
#include <cstdio>
#include <algorithm>
using namespace std;

const int MAXP=1005,MAXQ=105;
const int oo=0x7fffffff;

int P,Q;
int rel[MAXQ],d[MAXQ][MAXQ],K[MAXQ][MAXQ];

int main()
{
	freopen("prison.in","r",stdin);
	freopen("prison.out","w",stdout);
	scanf("%d%d",&P,&Q);
	for(int i=1;i<=Q;i++)
		scanf("%d",rel+i);
	rel[0]=0;rel[Q+1]=P+1;
	for(int i=1;i<=Q;i++)
		d[i][i]=rel[i+1]-rel[i-1]-2;
	for(int add=1;add<Q;add++)
		for(int i=1;i+add<=Q;i++)
		{
			int j=i+add;
			d[i][j]=oo;
			for(int k=i;k<=j;k++)
			{
				int temp=d[i][k-1]+d[k+1][j]+rel[j+1]-rel[i-1]-2;
				if (d[i][j]>temp)
					d[i][j]=temp,K[i][j]=k;
			}
		}
	printf("%d\n",d[1][Q]);
	return 0;
}
