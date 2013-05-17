/*
ID: dxmtb
PROG: uva10498 Happiness
TIME: 2011.02.10
STATE: Solved
MEMO: 线性规划单纯形算法
*/
#include <cstdio>
#include <cmath>
#include <cstring>
const int MAXN=100;

double A[MAXN][MAXN],b[MAXN],c[MAXN],v;

bool SetB[MAXN],SetN[MAXN];

int N,M,tot;

void pivot(const int &l,const int &e)
{
	double tmp=1/A[l][e];

	SetN[e]=false;
	SetB[l]=false;

	b[e]=b[l]*tmp;
	A[e][l]=tmp;
	for(int j=1;j<=tot;j++)
		if (SetN[j])
			A[e][j]=A[l][j]*tmp;
	for(int i=1;i<=tot;i++)
		if (SetB[i])
		{
			b[i]-=A[i][e]*b[e];
			A[i][l]=-A[i][e]*A[e][l];
			for(int j=1;j<=tot;j++)
				if (SetN[j])
					A[i][j]-=A[i][e]*A[e][j];
		}
	v+=c[e]*b[e];
	c[l]=-c[e]*tmp;
	for(int i=1;i<=tot;i++)
		if (SetN[i])
			c[i]-=c[e]*A[e][i];
	SetN[l]=true;
	SetB[e]=true;
}

void opt()
{
	while(true)
	{
		int l,e=0;
		for(int i=1;i<=tot;i++)
			if (SetN[i]&&c[i]>0)
			{
				e=i;
				break;
			}
		if (e==0)
			return ;
		double delta=1e18,tmp;
		for(int i=1;i<=tot;i++)
			if (SetB[i]&&A[i][e]>0&&(tmp=b[i]/A[i][e])<delta)
			{
				delta=tmp;
				l=i;
			}
		if (delta==1e18)
		{
			v=1e18;
			return ;
		}
		pivot(l,e);
	}
}

int main()
{
//	freopen("uva10498.in","r",stdin);
	while(scanf("%d%d",&N,&M)!=EOF)
	{
#define clear(x) memset((x),0,sizeof((x)))
		clear(A);clear(b);clear(c);
		clear(SetB);clear(SetN);
#undef clear
		v=0;
		tot=N+M;
		for(int i=1;i<=N;i++)	
		{
			scanf("%lf",c+i);
			SetN[i]=true;
		}
		for(int i=N+1;i<=N+M;i++)
		{
			for(int j=1;j<=N;j++)
				scanf("%lf",A[i]+j);
			scanf("%lf",b+i);
			SetB[i]=true;
		}
		opt();
		printf("Nasa can spend %d taka.\n",int(ceil(v*M)));
	}
	return 0;
}
