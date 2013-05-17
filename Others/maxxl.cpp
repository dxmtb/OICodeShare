/*
ID: dxmtb
PROG: 渡轮问题
TIME: 2010.10.12
STATE: Solved
MEMO: dp
*/
#include <cstdio>
using namespace std;

const int MAXN=10000;

int f[MAXN],d[MAXN],K[MAXN];
int n,re,ri;

int main()
{
	freopen("maxxl.in","r",stdin);
	freopen("maxxl.out","w",stdout);
	scanf("%d",&n);
	for(int i=0;i<n;i++)
		scanf("%d",f+i);
	for(int i=n-1;i>=0;i--)
	{
		d[i]=1;
		K[i]=-1;
		for(int j=i+1;j<n;j++)
			if (f[i]<=f[j]&&d[j]+1>d[i])
				d[i]=d[j]+1,K[i]=j;
	}
	for(int i=0;i<n;i++)
		if (d[i]>re)
			re=d[i],ri=i;
	printf("%d\n",re);
	bool out=false;
	do
	{
		if (out) printf(" ");
		else out=true;
		printf("%d",f[ri]);
		ri=K[ri];
	}while(ri!=-1);
	printf("\n");
	return 0;
}


