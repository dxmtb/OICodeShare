/*
ID: dxmtb1
PROG: range
LANG: C++
*/
#include <cstdio>
using namespace std;

const int MAXN=252;
const int oo=0x7fffffff;

int n;
char g[MAXN][MAXN];
int d[MAXN][MAXN];
int num[MAXN+1];

inline int min(int a,int b)
{return a>b?b:a;}
inline int min(int a,int b,int c)
{return min(min(a,b),c);}

int main()
{
	freopen("range.in","r",stdin);
	freopen("range.out","w",stdout);
	scanf("%d\n",&n);
	for(int i=0;i<n;i++)
	{
		fgets(g[i],MAXN,stdin);
		for(int j=0;j<n;j++)
			g[i][j]-='0';
	}
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
		{
			if (g[i][j])
			if (i>=1&&j>=1) d[i][j]=min(d[i-1][j-1],d[i][j-1],d[i-1][j])+1;
			else d[i][j]=1;	
			for(int k=2;k<=d[i][j];k++)
				++num[k];
		}
	for(int k=2;k<=n;k++)
		if (num[k])
			printf("%d %d\n",k,num[k]);
	return 0;
}


