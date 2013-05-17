/*
  ID: dxmtb1
  PROG: stamps
  LANG: C++
*/
#include <cstdio>
using namespace std;

const int MAXN=50,MAXK=200;

int K,N;
int d[MAXK*10000+1];
int a[MAXN];

int main()
{
	freopen("stamps.in","r",stdin);
	freopen("stamps.out","w",stdout);
	scanf("%d%d",&K,&N);
	for(int i=0;i<N;i++)
	{
		int x;
		scanf("%d",a+i);
	}
	for(int i=1;i<MAXK*10000+1;i++)
	{
		d[i]=0x7fffffff;
		for(int j=0;j<N;j++)
			if(i>=a[j]&&d[i-a[j]]+1<d[i])
				d[i]=d[i-a[j]]+1;
		if(d[i]>K)
		{
			printf("%d\n",i-1);
			break;
		}
	}
	return 0;
}
