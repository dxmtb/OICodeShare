/*
ID: dxmtb
PROG: 相似基因
TIME: 2010.11.9
STATE: Solved
MEMO: dp
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN=105;
const int oo=0x7fffffff;
const int w[5][5]={{5,-1,-2,-1,-3},
		   {-1,5,-3,-2,-4},
		   {-2,-3,5,-2,-2},
		   {-1,-2,-2,5,-1},
		   {-3,-4,-2,-1,-oo}};
const int blank=4;

int l1,l2;
int d[MAXN][MAXN];
char s1[MAXN],s2[MAXN];

int main()
{
	freopen("gene.in","r",stdin);
	freopen("gene.out","w",stdout);
	scanf("%d%s",&l1,s1+1);
	scanf("%d%s",&l2,s2+1);
	for(int i=0;i<=l1;i++)
		for(int j=0;j<=l2;j++)
			d[i][j]=-oo;
	for(int i=1;i<=l1;i++)
	{
		switch (s1[i])
		{
			case 'A':s1[i]=0;break;
			case 'C':s1[i]=1;break;
			case 'G':s1[i]=2;break;
			case 'T':s1[i]=3;break;
			default:printf("wrong!!\n");
		}
	}
	for(int i=1;i<=l2;i++)
	{
		switch (s2[i])
		{
			case 'A':s2[i]=0;break;
			case 'C':s2[i]=1;break;
			case 'G':s2[i]=2;break;
			case 'T':s2[i]=3;break;
			default:printf("wrong!!\n");
		}
	}
	d[0][0]=0;
	for(int i=0;i<=l1;i++)
		for(int j=0;j<=l2;j++)
		{
			if (i&&j) d[i][j]=max(d[i][j],d[i-1][j-1]+w[s1[i]][s2[j]]);
			if (i) d[i][j]=max(d[i][j],d[i-1][j]+w[blank][s1[i]]);
			if (j) d[i][j]=max(d[i][j],d[i][j-1]+w[blank][s2[j]]);
		}
	printf("%d\n",d[l1][l2]);
	return 0;
}
