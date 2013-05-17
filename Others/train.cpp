/*
ID: dxmtb
PROG: 火车进站(火车调度)
TIME: 2010.10.31
STATE: Solved
MEMO: 分情况dp
*/
#include <cstdio>
#include <algorithm>
using namespace std;

const int MAXN=105;

struct Node
{
	int s,t;
}tr[MAXN];

bool operator < (const Node &a,const Node &b)
{
	return (a.s<b.s||(a.s==b.s&&a.t<b.t));
}

int N,M,re;

int d1[MAXN];
void solve1()
{
	for(int i=0;i<N;i++)
	{
		d1[i]=1;
		for(int j=0;j<i;j++)
			if (tr[j].t<=tr[i].s&&d1[i]<d1[j]+1)
				d1[i]=d1[j]+1;
		if (d1[i]>re)
			re=d1[i];
	}
}

int d2[MAXN][MAXN];
void solve2()
{
	for(int i=0;i<N;i++)
		for(int j=i+1;j<N;j++)
			if (tr[i].s<=tr[j].s&&tr[i].t<=tr[j].t)
			{
				d2[i][j]=2;
				for(int k=0;k<i;k++)
					if (d2[k][i]&&tr[k].t<=tr[j].s
							&&d2[i][j]<d2[k][i]+1)
						d2[i][j]=d2[k][i]+1;
				if (d2[i][j]>re)
					re=d2[i][j];
			}

}

int d3[MAXN][MAXN][MAXN];
void solve3()
{
	for(int i=0;i<N;i++)
		for(int j=i+1;j<N;j++)
			if (tr[i].s<=tr[j].t&&tr[i].t<=tr[j].t)
				for(int k=j+1;k<N;k++)
					if (tr[j].s<=tr[k].s&&tr[j].t<=tr[k].t)
					{
						d3[i][j][k]=3;
						for(int a=0;a<i;a++)
							if (d3[a][i][j]&&tr[a].t<=tr[k].s
									&&d3[i][j][k]<d3[a][i][j]+1)
								d3[i][j][k]=d3[a][i][j]+1;
						if (d3[i][j][k]>re)
							re=d3[i][j][k];
					}
}

int main()
{
	freopen("train.in","r",stdin);
	freopen("train.out","w",stdout);
	scanf("%d%d",&N,&M);
	N+=M;
	tr[0].s=-3000;tr[0].t=-2500;
	tr[1].s=-2000;tr[1].t=-1500;
	tr[2].s=-1000;tr[2].t=-500;
	for(int i=M;i<N;i++)
		scanf("%d%d",&tr[i].s,&tr[i].t);
	sort(tr,tr+N);	
	switch(M)
	{
		case 1:solve1();break;
		case 2:solve2();break;
		case 3:solve3();break;
		default:printf("wrong!!\n");
	}
	printf("%d\n",re-M);
	return 0;
}
