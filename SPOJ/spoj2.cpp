/*
ID: dxmtb
PROG: spoj2 Prime Generator
TIME: 2010.8.24
STATE: Solved
MEMO: 先找32623以内素数，再朴素
*/
#include <cstdio>
#include <cmath>

const int MAXN=1e9,MAXM=32623;

bool prime[MAXM+1];
int vec[5000],top=0;

int main()
{
	for(int i=2;i<=MAXM;i++)
		prime[i]=true;
	for(int i=2;i<=MAXM;i++)
		if (prime[i])
		{
			for(int j=i+i;j<=MAXM;j+=i)
				prime[j]=false;
			vec[top++]=i;
		}
	int T;
	scanf("%d",&T);
	while(T--)
	{
		int a,b;
		scanf("%d%d",&a,&b);
		int i,j;
		if (a<=MAXM)
		{
			for(j=0;j<top&&vec[j]<=b;j++)
				printf("%d\n",vec[j]);
			a=MAXM+1;
		}
		a=(a&1)?a:a+1;
		for(i=a;i<=b;i+=2)
		{
			int k=sqrt(i);
			for(j=0;vec[j]<=k&&j<top;j++)
				if (i%vec[j]==0)
					break;
			if (vec[j]>k||j==top)
				printf("%d\n",i);
		}
		if (T)printf("\n");
	}
	return 0;
}

