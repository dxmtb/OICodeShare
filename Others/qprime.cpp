/*
ID: dxmtb
PROG: 有限制的素数
TIME: 2010.9.18
STATE: Solved
MEMO: 模拟
*/
#include <cstdio>
#include <cmath>
using namespace std;

int A,B,D;
int prime[400],top;

void init()
{
	bool flag[2001];
	for(int i=2;i<=2000;i++)
		flag[i]=true;
	for(int i=2;i<=2000;i++)
	{
		if (flag[i]) prime[top++]=i;
		for(int j=0;j<top&&i*prime[j]<=2000;j++)
		{
			flag[i*prime[j]]=false;
			if (i%prime[j]==0)
				break;
		}
	}
//	for(int i=0;i<top;i++)
//		printf("%d\n",prime[i]);
}

int main()
{
	freopen("qprime.in","r",stdin);
	freopen("qprime.out","w",stdout);
	scanf("%d%d%d",&A,&B,&D);
	init();
	int re=0;
	if (A<=2&&D==2)re=1;
	if (A<=2)A=3;
	else if (!(A&1)) A+=1;
	for(int i=A;i<=B;i+=2)
	{
		int t=i;
		do
		{
			if (t%10==D)
			{
				int k=sqrt(i);
				bool flag=true;
				for(int j=0;j<top&&prime[j]<=k;j++)
					if (i%prime[j]==0)
					{
						flag=false;
						break;
					}
				re+=flag;
				break;
			}
			else t/=10;
		}while(t);
	}
	printf("%d\n",re);
	return 0;
}

