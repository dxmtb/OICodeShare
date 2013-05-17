/*
 * Problem: [HNOI2008]GT考试
 * Time: 2011.05.04
 * Author: dxmtb
 * State: Solved
 * Memo: dp + 矩阵乘法
*/
#include <cstdio>
#include <cstring>

const int MAXM=25;

struct Matrix
{
	int R;
	int a[MAXM][MAXM];
	Matrix()
	{
		memset(a,0,sizeof(a));
	}
}A,B;

int K,M;

Matrix operator * (const Matrix &a,const Matrix &b)
{
	Matrix c;
	c.R=a.R;
	for(int i=0;i<c.R;i++)
		for(int j=0;j<M;j++)
			for(int k=0;k<M;k++)
				c.a[i][j]=(c.a[i][j]+a.a[i][k]*b.a[k][j])%K;
	return c;
}

Matrix pow(Matrix a,int n)
{
	while(!(n&1))
	{
		a=a*a;
		n>>=1;
	}
	Matrix b=a;
	n>>=1;
	a=a*a;
	while(n)
	{
		if (n&1)
			b=b*a;
		n>>=1;
		a=a*a;
	}
	return b;
}

int N;
char str[MAXM];

int to[MAXM][10];
void init()
{
	char s[MAXM];
	memset(s,0,sizeof(s));
	for(int i=0;i<M;i++)
	{
		for(int j=0;j<i;j++)
			s[j]=str[j+1];
		for(int j=0;j<=9;j++)
		{
			s[i]='0'+j;
			to[i][j]=0;
			for(int k=i+1;k>=1;k--)
			{
				for(int p=1;p<=k;p++)
					if (s[i-k+p]!=str[p])
						goto OUT;
				to[i][j]=k;
				break;
				OUT:;
			}
		}
	}
	B.R=M;
	for(int j=0;j<M;j++)
		for(int k=0;k<10;k++)
			if (to[j][k]!=M)
				B.a[j][to[j][k]]++;
	A.R=1;
	A.a[0][0]=1;
}

int main()
{
	freopen("1009.in","r",stdin);
	scanf("%d%d%d",&N,&M,&K);
	scanf(" %s",str+1);
	init();
	/*
	d[0][0]=1;
	for(int i=0;i<N;i++)
	{
		for(int j=0;j<M;j++)
			if (d[i][j])
				for(int k=0;k<10;k++)
					d[i+1][to[j][k]]+=d[i][j];
	}*/
	Matrix C=A*pow(B,N);
	int ans=0;
	for(int j=0;j<M;j++)
		ans=(ans+C.a[0][j])%K;
	printf("%d\n",ans);
	return 0;
}
