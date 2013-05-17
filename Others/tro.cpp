/*
ID: dxmtb
PROG: 单色三角形
TIME: 2011.02.22
STATE: Solved
MEMO: 数学方法
*/
#include <cstdio>

const int MAXN=1000;

int N,sum;
int red[MAXN],black[MAXN];

int main()
{
	freopen("tro.in","r",stdin);
	freopen("tro.out","w",stdout);
	scanf("%d",&N);
	int M;
	scanf("%d",&M);
	while(M--)
	{
		int p,k;
		scanf("%d%d",&p,&k);
		red[p]++,red[k]++;
		black[p]--,black[k]--;
	}
	for(int i=1;i<=N;i++)
	{
		black[i]+=N-1;
		sum+=red[i]*black[i];
	}
	printf("%d",N*(N-1)*(N-2)/6-sum/2);
	return 0;
}
