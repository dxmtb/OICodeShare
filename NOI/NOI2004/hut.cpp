/*
 * Problem: NOI2004 小 H 的小屋
 * Time: 2011.06.16
 * Author: dxmtb
 * State: Solved
 * Memo: dp+利用函数的凸性决策单调（直观无证明）
*/
#include <cstdio>

const int MAXN=105;
const int oo=~0u>>2;

inline void Min(double &a,double b)
{
	if (b<a)
		a=b;
}

double f[MAXN][MAXN];
double d[MAXN][MAXN][MAXN];
double K1,K2;
int M,N;

inline double getD(int i,int j,int k,int a,int b)
{
	if (d[i-1][j-a][k-b]==oo)
		return oo;
	return d[i-1][j-a][k-b]+b*b*K1+f[a][b];
}
int main()
{
	freopen("hut.in","r",stdin);
	freopen("hut.out","w",stdout);
	scanf("%lf%lf%d%d",&K1,&K2,&M,&N);
	for(int i=0;i<=100;i++)
		for(int j=0;j<=100;j++)
			f[i][j]=oo;
	f[0][0]=0;
	for(int i=1;i<=N;i++)
		for(int j=i;j<=100;j++)
		{
			int x=j%i,c=j/i;
			int nf=c*c*(i-x)+(c+1)*(c+1)*x;
			f[i][j]=K2*nf;
		}
	for(int i=0;i<=M;i++)
		for(int j=0;j<=N;j++)
			for(int k=0;k<=100;k++)
				d[i][j][k]=oo;
	d[0][0][0]=0;
	for(int i=1;i<=M;i++)
		for(int j=i;j<=N;j++)
			for(int k=j;k<=100;k++)
			{
				int last=1;
				for(int a=1;a<=j;a++)
				{
					while(last+1<=k && getD(i,j,k,a,last+1)<=getD(i,j,k,a,last))
						last++;
					Min(d[i][j][k],getD(i,j,k,a,last));
				}
			}
	printf("%.1lf\n",d[M][N][100]);
	return 0;
}
