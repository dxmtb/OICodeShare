/*
ID: dxmtb
PROG: NOIP2000 方格取数
TIME: 2010.4.13
STATE: Solved
MEMO: 先搜索+后动态规划
*/
#include <cstdio>
#include <cstring>
using namespace std;

const int MAXN=100;

int n,re=-10000000,num[MAXN][MAXN],d[MAXN][MAXN],way[MAXN][MAXN];

FILE *fin=fopen("fgqs.in","r");
FILE *fout=fopen("fgqs.out","w");

void search(int x,int y,int sum)
{
	int tt=num[x][y];
	num[x][y]=0;
	if (x>=n||y>=n)return;
	if (x==n-1&&y==n-1)
	{
		memset(d,0,sizeof(d));
		d[0][0]=num[0][0];
		for(int i=1;i<n;i++)d[i][0]=num[i][0]+d[i-1][0],way[i][0]=1;
		for(int i=1;i<n;i++)d[0][i]=num[0][i]+d[0][i-1],way[i][0]=0;
		for(int i=1;i<n;i++)
			for(int j=1;j<n;j++)
				if (d[i][j-1]>d[i-1][j])
					d[i][j]=d[i][j-1]+num[i][j],way[i][j]=0;
				else
					d[i][j]=d[i-1][j]+num[i][j],way[i][j]=1;		
		if (tt+sum+d[n-1][n-1]>re)
			re=tt+sum+d[n-1][n-1];
	}
	search(x+1,y,sum+tt);
	search(x,y+1,sum+tt);
	num[x][y]=tt;
}

int main() 
{
	memset(num,0,sizeof(num));
	fscanf(fin,"%d",&n);
	{
	int a,b,c;
	fscanf(fin,"%d%d%d",&a,&b,&c);
	while (a!=0||b!=0||c!=0)
	{
		num[a-1][b-1]=c;
		fscanf(fin,"%d%d%d",&a,&b,&c);
	}
	}
	search(0,0,0);
	fprintf(fout,"%d\n",re);
    return 0;
}

