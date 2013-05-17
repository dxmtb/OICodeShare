/*
ID: dxmtb
PROG: BLAST
TIME: 2010.10.20
STATE: Solved
MEMO: dp
*/
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
using namespace std;

const int MAXN=2005;

int d[MAXN][MAXN];
char str1[MAXN],str2[MAXN];
int K;

int main()
{
	freopen("blast.in","r",stdin);
	freopen("blast.out","w",stdout);
	scanf("%s\n%s\n%d",str1,str2,&K);
	int len1=strlen(str1),len2=strlen(str2);
	for(int i=1;i<=len1;i++)
		d[i][0]=i*K;
	for(int i=1;i<=len2;i++)
		d[0][i]=i*K;
	for(int i=1;i<=len1;i++)
		for(int j=1;j<=len2;j++)
			d[i][j]=min(min(d[i-1][j]+K,d[i][j-1]+K),d[i-1][j-1]+abs(str1[i-1]-str2[j-1]));
	printf("%d\n",d[len1][len2]);
	return 0;
}
