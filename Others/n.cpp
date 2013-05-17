/*
ID: dxmtb
PROG: ×´Ì¬Ñ¹ËõÁ·Ï° n!
TIME: 2010.3.28
STATE: Solved
MEMO: Î»ÔËËã ×´Ì¬Ñ¹ËõµİÍÆ
*/
#include <cstdio>
#include <string>
using namespace std;

const int MAXN=20;

int n,d[1<<MAXN];

int main() 
{
	scanf("%d",&n);
	memset(d,0,sizeof(d));
	int ms=1<<n; 
	d[0]=1;
	for(int i=1;i<ms;i++)
		for(int j=i;j;j-=j&-j)
			d[i]+=d[i^(j&-j)];
	printf("%d\n",d[ms-1]);
	int i;scanf("%d",&i);
    return 0;
}

