/*
ID: dxmtb
PROG: 秘密组织
TIME: 2010.7.9
STATE: Solved
MEMO: 递推+高精度
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN=100,MAXS=900,MAXL=202;

struct High
{
	int len;
	int a[MAXL];
	High(){len=1;memset(a,0,sizeof(a));}
	void reset(){len=1;memset(a,0,sizeof(a));}
};

High operator + (High a,High b)
{
	High temp;
	int len=max(a.len,b.len);
	for(int i=0;i<len;i++)
		temp.a[i]+=a.a[i]+b.a[i],
		temp.a[i+1]=temp.a[i]/1000,
		temp.a[i]%=1000;
	if (temp.a[len])len++;
	temp.len=len;
	return temp;
}

High operator * (High a,High b)
{
	High temp;
	for(int i=0;i<MAXL;i++)
		temp.a[i]=0;
	int len1=a.len,len2=b.len;
	for(int i=0;i<len1;i++)
		for(int j=0;j<len2;j++)
			temp.a[i+j]+=a.a[i]*b.a[j];
	for(int i=0;i<MAXL;i++)
	{
		temp.a[i+1]+=temp.a[i]/1000,
		temp.a[i]%=1000;
		if (temp.a[i]&&i+1>temp.len)
			temp.len=i+1;
	}
	return temp;
}

void put(High a)
{
	for(int i=a.len-1;i>=0;i--)
	{
		if (i!=a.len-1)
		{
			if (a.a[i]<10)
				printf("00");
			else if (a.a[i]<100)
				printf("0");
		}
		printf("%d",a.a[i]);
	}
	printf("\n");
}

High d[2][MAXS+1];
int n,S;

int main()
{
	freopen("secret.in","r",stdin);
	freopen("secret.out","w",stdout);
	scanf("%d%d",&n,&S);
	if (S%2)
	{
		printf("0\n");
		return 0;
	}
	d[0][0].a[0]=1;
	for(int i=1;i<=n;i++)
		for(int j=0;j<=S/2;j++)
		{
			d[i&1][j].reset();
			for(int k=0;k<=9&&k<=j;k++)
				d[i&1][j]=d[i&1][j]+d[(i-1)&1][j-k];
//			put(d[i&1][j]);
		}
	High re=d[n&1][S/2]*d[n&1][S/2];
	put(re);
	return 0;
}
