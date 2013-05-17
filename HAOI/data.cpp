/*
ID: dxmtb
PROG: HAOI2006 均分数据
TIME: 2011.03.02
STATE: Solved
MEMO: 模拟退火
*/
#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <ctime>

const int MAXN=21,MAXM=7;

inline double sqr(double a)
{
	return a*a;
}

int N,M;
int A[MAXN];
int B[MAXN];

int sum[MAXM];
double avg;

inline double getans(int B[])
{
	memset(sum,0,sizeof(sum));
	for(int i=0;i<N;i++)
		sum[B[i]]+=A[i];
	double t=0;
	for(int i=0;i<M;i++)
		if (sum[i]) t+=sqr(sum[i]-avg);
		else return 1e10;
	return t;
}

int main()
{
	freopen("data.in","r",stdin);
	freopen("data.out","w",stdout);
	scanf("%d%d",&N,&M);
	for(int i=0;i<N;i++)
	{
		scanf("%d",A+i);
		avg+=A[i];
	}
	avg/=M;
	for(int i=0;i<N;i++)
		B[i]=rand()%M;
	double ans=getans(B),best=ans;
	double T0=16,T=T0;
	int Time=1;
	while(Time<100000)
	{
		int t1=rand()%N,t2=rand()%M,t3=rand()%N,t4=rand()%M;
		int s1=B[t1],s3=B[t3];
		B[t1]=t2;
		B[t3]=t4;
		double tans=getans(B);
		if (tans<ans)
		{
			ans=tans;
			if (tans<best)
				best=tans;
			B[t1]=t2;
			B[t3]=t4;
		}
		else
		{
			double p1=rand()%10000/10000.0,
			       p2=exp((ans-tans)/T);
			if (p1<p2)
			{
				ans=tans;
				B[t1]=t2;
				B[t3]=t4;
			}
			else
				B[t1]=s1,B[t3]=s3;
		}
		T=T0/log(Time+1);
		Time++;
	//	printf("%lf %lf\n",T,best);
	}
	printf("%.2lf\n",sqrt(best/M));
	return 0;
}
