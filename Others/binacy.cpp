/*
ID: dxmtb
PROG: Binacy
TIME: 2010.11.19
STATE: Solved
MEMO: dp
*/
#include <cstdio>
const int MAXN=1000005;

int f[MAXN],N;

int main()
{
	freopen("binacy.in","r",stdin);
	freopen("binacy.out","w",stdout);
	scanf("%d",&N);
	f[1]=1;f[2]=2;
	for(int i=3;i<=N;i++)
		f[i]=(f[i-1]+f[i-2])%15746;
	printf("%d\n",f[N]);
	return 0;
}
