/*
ID: dxmtb
PROG: 买票
TIME: 2010.10.26
STATE: Solved
MEMO: 枚举
*/
#include <cstdio>
using namespace std;

const int MAXN=1000005;

int a[MAXN];
int n,f,m;

int main()
{
	freopen("tickets.in","r",stdin);
	freopen("tickets.out","w",stdout);
	scanf("%d%d",&n,&f);
	for(int i=0;i<n;i++)
		scanf("%d",a+i);
	for(int i=0,j=0,total=0;i<n;i++)
	{
		if (j<i)
			j=i,total=0;
		while(a[j]+total<=f&&j<n)
			total+=a[j++];
		if (j-i>m)
			m=j-i;
		total-=a[i];
	}
	printf("%d\n",m);
	return 0;
}
