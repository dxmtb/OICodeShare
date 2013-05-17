/*
ID: dxmtb1
PROG: nocows
LANG: C++
*/
#include <cstdio>
#include <cstring>
using namespace std;

const int MAXN=199,MAXK=99;

FILE *fin=fopen("nocows.in","r");
FILE *fout=fopen("nocows.out","w");

int N,K,d[MAXK][MAXN];

int main()
{
	memset(d,0,sizeof(d));
	fscanf(fin,"%d%d",&N,&K);
	d[1][1]=1;
	for(int i=2;i<=K;i++)
		for(int j=3;j<=N;j+=2)
			for(int k=1;k<=j-1;k+=2)
			{
				for(int a=1;a<i-1;a++)
				{
					d[i][j]+=2*d[i-1][k]*d[a][j-k-1];
					d[i][j]%=9901;
				}
				d[i][j]+=d[i-1][j-k-1]*d[i-1][k];
			}
	fprintf(fout,"%d\n",d[K][N]);
}
