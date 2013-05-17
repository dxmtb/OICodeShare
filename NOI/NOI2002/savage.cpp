/*
 * Problem: NOI2002 荒岛野人
 * Time: 2011.06.13
 * Author: dxmtb
 * State: Solved
 * Memo: 枚举 + 判断
*/
#include <cstdio>

const int MAXN=20;
const int MAXM=1000000;

inline int ext_gcd(int a,int b,int &x,int &y)
{
	if (b==0)
	{
		x=1,y=0;
		return a;
	}
	int xt,yt;
	int d=ext_gcd(b,a%b,xt,yt);
	x=yt;
	y=xt-a/b*yt;
	return d;
}

inline int mod(int x,int m)
{
	x=x%m;
	if (x<0)
		x+=m;
	return x;
}

int N,C[MAXN],P[MAXN],L[MAXN];

int main()
{
	freopen("savage.in","r",stdin);
	freopen("savage.out","w",stdout);
	scanf("%d",&N);
	int minm=1;
	for(int i=0;i<N;i++)
	{
		scanf("%d%d%d",C+i,P+i,L+i);
		if (C[i]>minm)
			minm=C[i];
		C[i]--;
	}
	for(int &M=minm;M<=MAXM;M++)
	{
		bool flag=true;
		for(int i=0;i<N && flag;i++)
			for(int j=i+1;j<N;j++)
			{
				int x,y;
				int d=ext_gcd(mod(P[i]-P[j],M),M,x,y);
				if ((C[j]-C[i])%d==0)
				{
					x=mod(x*(C[j]-C[i])/d,M/d);
					if (x<=L[i] && x<=L[j])
					{
						flag=false;
						break;
					}
				}
			}
		if (flag)
		{
			printf("%d\n",M);
			break;
		}
	}
	return 0;
}
