/*
ID: dxmtb
PROG: NOIP2006 2^k进制数
TIME: 2010.9.3
STATE: Solved
MEMO: dp+高精度
*/
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
using namespace std;

const int MAXK=9,MAXW=30000;

class High
{
	public:
		High(){reset();}
		void reset(){memset(a,0,sizeof(a));len=1;}
		int a[205],len;
};

void print(High a)
{
	for(int i=a.len-1;i>=0;i--)
		printf("%d",a.a[i]);
}
High operator + (High a,High b)
{
	High temp;
	temp.len=max(a.len,b.len);
	for(int i=0;i<temp.len;i++)
		temp.a[i]+=a.a[i]+b.a[i],
		temp.a[i+1]=temp.a[i]/10,
		temp.a[i]%=10;
	if (temp.a[temp.len])
		temp.len++;
//	print(a);printf("+");print(b);printf("=");print(temp);printf("\n");
	return temp;
}


int n,m,K,W;
int f[(1<<MAXK)];
High d[2][(1<<MAXK)];
High re;

int main()
{
	freopen("digital.in","r",stdin);
	freopen("digital.out","w",stdout);
	scanf("%d%d",&K,&W);
	n=ceil(W/3.0);
	f[0]=f[1]=1;
	for(int i=2;i<(1<<K);i++)
		f[i]=f[i/2]+1;
	for(int i=0;i<(1<<K);i++)
		d[1][i].len=1,d[1][i].a[0]=1;
	for(int i=2;i<=min(n,(1<<K)-1);i++)
	{
		for(int j=(1<<K)-2;j>=1;j--)
			d[(i&1)][j].reset();
		for(int j=(1<<K)-i;j>=1;j--)
		{
			d[(i&1)][j]=d[1-(i&1)][j+1]+d[(i&1)][j+1];
			if (i>=2&&((i-1)*K+f[j])<=W)
				re=re+d[(i&1)][j];
		}
	}
/*	for(int i=1;i<=n;i++)
	{
		for(int j=0;j<(1<<K);j++)
			printf("%d ",d[i][j]);
		printf("\n");
	}*/
	print(re);
	printf("\n");
	return 0;
}
