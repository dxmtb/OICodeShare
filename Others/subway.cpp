/*
ID: dxmtb
PROG: 地铁重组
TIME: 2010.7.4
STATE: Solved
MEMO: 递推
*/
#include <cstdio>
#include <cstring>
using namespace std;

const int MAXN=500,MAXP=300;

int n,p;
int d[MAXN+1][MAXP+1];

void dd(int i,int j)
{
	if (d[i][j]!=-1)return;
	if (j==p)
	{
		dd(i,p-1);
		d[i][j]=d[i][j-1];
	}
	else
		if(j==0)
		{
			dd(i-1,j+1);
			d[i][j]=d[i-1][j+1];
		}
		else
		{
			dd(i,j-1);dd(i-1,j+1);
			d[i][j]=(d[i][j-1]+d[i-1][j+1])%4096;
		}
}

int main()
{
	freopen("subway.in","r",stdin);
	freopen("subway.out","w",stdout);
	memset(d,-1,sizeof(d));
	scanf("%d%d",&n,&p);
	d[0][0]=0;
	for(int i=1;i<=p;i++)
		d[0][i]=1;
	dd(n,0);
	printf("%d\n",d[n][0]);
	return 0;
}
