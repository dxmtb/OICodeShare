/*
ID: dxmtb
PROG: 分班
TIME: 2010.11.18
STATE: Solved
MEMO: 模拟
*/
#include <stdio.h>

#define MAXN 55

int N,L,R,sum;
int a[MAXN];

int main()
{
	freopen("groupa.in","r",stdin);
	freopen("groupa.out","w",stdout);
	scanf("%d",&N);
	int i,j;
	for(i=1;i<=N;i++)
	{
		scanf("%d",a+i);
		sum+=a[i];
	}
	scanf("%d%d",&L,&R);
	if (sum<L*N||sum>R*N)
	{
		printf("-1\n");
		return 0;
	}
	int re=0;
	for(i=1;i<=N;i++)
		if (a[i]<L)
		{
			for(j=1;j<=N&&a[i]<L;j++)
				if (a[j]>R)
				{
					if (L-a[i]>a[j]-R)
					{
						a[i]+=a[j]-R;
						re+=a[j]-R;
						a[j]=R;
					}
					else
					{
						a[j]-=L-a[i];
						re+=L-a[i];
						a[i]=L;
					}
				}
		}
		else if (a[i]>R)
		{
			for(j=1;j<=N&&a[i]>R;j++)
				if (a[j]<L)
				{
					if (L-a[j]>a[i]-R)
					{
						a[j]+=a[i]-R;
						re+=a[i]-R;
						a[i]=R;
					}
					else
					{
						a[i]-=L-a[j];
						re+=L-a[j];
						a[j]=L;
					}		
				}
		}
	for(i=1;i<=N;i++)
		if (a[i]>R)
		{
			re+=a[i]-R;
		}
		else if (a[i]<L)
		{
			re+=L-a[i];
		}
	printf("%d\n",re);
	return 0;
}
