/*
ID: dxmtb1
PROG: subset
LANG: C++
*/
#include <cstdio>

using namespace std;

const int MAXN=39;

int n,total,d[MAXN+1][(MAXN+1)*MAXN/4+1];

FILE *fin=fopen("subset.in","r");
FILE *fout=fopen("subset.out","w");

int main() 
{
	fscanf(fin,"%d",&n);
	total=(1+n)*n/2;
	if (total%2!=0) 
	{
		fprintf(fout,"0\n");
		return 0;
	}
	d[1][1]=1;
	for(int i=2;i<=n;i++)
		for(int j=1;j<=total/2;j++)
			d[i][j]=d[i-1][j-i]+d[i-1][j];
	fprintf(fout,"%d\n",d[n][total/2]);
	return 0;
}
