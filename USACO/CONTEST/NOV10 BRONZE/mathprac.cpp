/*
PROG: mathprac
LANG: C++
ID: dxmtb1
*/
#include <cstdio>

int A,B;

int main()
{
	freopen("mathprac.in","r",stdin);
	freopen("mathprac.out","w",stdout);
	scanf("%d%d",&A,&B);
	for(int i=A+1;i<=62;i++)
	{
		unsigned long long j=(1ull)<<i;
		while(j>10)
			j/=10;
		if (j==B)
		{
			printf("%d\n",i);
			return 0;
		}
	}
	printf("0\n");
	return 0;
}
