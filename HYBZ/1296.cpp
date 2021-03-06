/*
ID: dxmtb
PROG: [SCOI2009]粉刷匠 
TIME: 2011.03.24
STATE: Solved
MEMO: dp
*/
#include <cstdio>
#include <algorithm>
using namespace std;

const int MAXN=55,MAXT=2505;
const int oo=0x7fffffff/2;

char str[MAXN][MAXN];
int size[MAXN];
int d[MAXN*MAXN][MAXT][3];
int w[MAXN*MAXN][2];
int N,M,T;

inline void Max(int &a,const int &b)
{
	if (b>a)
		a=b;
}

int main()
{
	freopen("1296.in","r",stdin);
	scanf("%d%d%d",&N,&M,&T);
	for(int i=0,tot=0;i<N;i++)
	{
		scanf(" %s",str[i]);
		for(int j=1,k=1;j<=M;j++)
		{
			if (str[i][j]!=str[i][j-1])
			{
				if (str[i][j-1]=='0') w[tot][0]=k;
				else w[tot][1]=k;
				tot++;
				size[i]++;
				k=1;
			}
			else k++;
		}
	}
	for(int i=0,tot=0;i<N;i++)
	{
		for(int j=tot;j<tot+size[i];j++)
			for(int k=0;k<=T;k++)
				d[j][k][0]=d[j][k][1]=-oo;
		tot+=size[i];
	}
	int tot=0;
	for(int i=0;i<N;i++)
	{
		if (tot)
		{
			for(int k=1;k<=T;k++)
			{
				d[tot][k][0]=d[tot][k][1]=max(max(d[tot-1][k-1][0],d[tot-1][k-1][1]),d[tot-1][k-1][2]);
				d[tot][k][0]+=w[tot][0];
				d[tot][k][1]+=w[tot][1];
				d[tot][k][2]=max(max(d[tot-1][k][0],d[tot-1][k][1]),d[tot-1][k][2]);
			}
		}
		else 
			for(int k=1;k<=T;k++)
			{
				d[0][k][0]=w[0][0];
				d[0][k][1]=w[0][1];
			}
		for(int j=tot+1;j<tot+size[i];j++)
		{
			for(int k=1;k<=T;k++)
			{
				d[j][k][0]=d[j-1][k][0]+w[j][0];
				if (k)
					Max(d[j][k][0],d[j-1][k-1][1]+w[j][0]);
				d[j][k][1]=d[j-1][k][1]+w[j][1];
				if (k)
					Max(d[j][k][1],d[j-1][k-1][0]+w[j][1]);
				d[j][k][2]=max(max(d[j-1][k][0],d[j-1][k][1]),d[j-1][k][2]);
			}
		}
		tot+=size[i];
	}
	printf("%d\n",max(max(d[tot-1][T][0],d[tot-1][T][1]),d[tot-1][T][2]));
	return 0;
}
