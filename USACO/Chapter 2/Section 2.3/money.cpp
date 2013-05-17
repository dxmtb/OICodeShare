/*
ID: dxmtb1
PROG: money
LANG: C++
*/
#include <cstdio>
#include <cstring>
using namespace std;

const int MAXN=10000;

long long d[MAXN+1];
int V,N;

FILE *fin=fopen("money.in","r");
FILE *fout=fopen("money.out","w");

int main()
{
	memset(d,0,sizeof(d));
	fscanf(fin,"%d%d",&V,&N);
	d[0]=1;
	for(int i=1;i<=V;i++)
	{
		int x;
		fscanf(fin,"%d",&x);
		for(int j=x;j<=N;j++)
			d[j]+=d[j-x];
	}
	fprintf(fout,"%lld\n",d[N]);
	return 0;
}


