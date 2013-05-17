/*
ID: dxmtb1
PROG: cowcycle
LANG: C++
*/
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
using namespace std;
const int MAXR=10;

#define sqr(x) ((x)*(x))

int N[2],S[2],T[2];

int way[2][MAXR];
int wayc[2][MAXR];
double re=1e19;

void calcu()
{
	double temp[MAXR*MAXR];
	if (way[0][N[0]-1]*way[1][N[1]-1]<way[0][0]*way[1][0]*3)
	{
	//	printf("wrong");
		return ;
	}
/*	for(int i=0;i<N[0];i++)
		printf("%d ",way[0][i]);
	printf("\n");
	for(int i=0;i<N[1];i++)
		printf("%d ",way[1][i]);
	printf("\n");*/
	for(int i=0,timer=0;i<N[0];i++)
		for(int j=0;j<N[1];j++,timer++)
			temp[timer]=double(way[0][i])/way[1][j];
	sort(temp,temp+N[0]*N[1]);
	double sum=0;
	for(int i=0;i<N[0]*N[1]-1;i++)
		temp[i]=temp[i+1]-temp[i],
		sum+=temp[i];
	sum/=(N[0]*N[1]-1);
	double r=0;
	for(int i=0;i<N[0]*N[1]-1;i++)
		r+=sqr(temp[i]-sum);
	if (r<re)
	{
		re=r;
		memcpy(wayc[0],way[0],sizeof(int)*N[0]);
		memcpy(wayc[1],way[1],sizeof(int)*N[1]);
	}
}

void search(int now,int dep,int s)
{
	if (now==1&&dep>0)
		if (way[0][N[0]-1]*T[1]<3*way[0][0]*way[1][0])
			return ;
	if (dep==N[now])
	{
		if (now==0) search(1,0,S[1]);
		else calcu();
		return ;
	}
	for(int i=s;i<=T[now];i++)
	{
		way[now][dep]=i;
		search(now,dep+1,i+1);
	}
}

int main()
{
	freopen("cowcycle.in","r",stdin);
	freopen("cowcycle.out","w",stdout);
	scanf("%d%d%d%d%d%d",N,N+1,S,T,S+1,T+1);
	search(0,0,S[0]);
	printf("%d",wayc[0][0]);
	for(int i=1;i<N[0];i++)
		printf(" %d",wayc[0][i]);
	printf("\n%d",wayc[1][0]);
	for(int i=1;i<N[1];i++)
		printf(" %d",wayc[1][i]);
	printf("\n");
//	printf("%lf",re);
	return 0;
}

