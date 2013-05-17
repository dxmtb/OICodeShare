/*
ID: dxmtb
PROG: 波浪数
TIME: 2010.11.9
STATE: Solved
MEMO: 枚举
*/
#include <stdio.h>

const int MAXN=1e7+1;

int w[MAXN],b1,b2,s,t,wave,i,a,b,num,k;

int main()
{
	freopen("num.in","r",stdin);
	freopen("num.out","w",stdout);
	scanf("%d%d%d%d%d",&b1,&b2,&s,&t,&wave);
	for(i=b1;i<=b2;i++)
	{
		for(a=0;a<i;a++)
			for(b=1;b<i;b++)
				if (a!=b)
				{
					k=num=0;
					while(1)
					{
						num*=i;
						if (k&1) num+=a;
						else num+=b;
						if (num>t) break;
						w[num]++;
						k++;
					}
				}
	}
	for(i=s;i<=t;i++)
		if (w[i]==wave)
			printf("%d\n",i);
	return 0;
}
