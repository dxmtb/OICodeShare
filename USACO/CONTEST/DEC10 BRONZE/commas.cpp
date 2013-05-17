/*
ID: dxmtb1
PROG: commas
LANG: C++
*/
#include <cstdio>

int N,top;
int ans[10];

int main()
{
	freopen("commas.in","r",stdin);
	freopen("commas.out","w",stdout);
	scanf("%d",&N);
	while(N>=1000)
	{
		ans[top++]=N%1000;
		N/=1000;
	}
	printf("%d",N);
	for(int i=top-1;i>=0;i--)
	{
		printf(",");
		if (ans[i]<10)
			printf("00");
		else if (ans[i]<100)
			printf("0");
		printf("%d",ans[i]);
	}
	printf("\n");
	return 0;
}
