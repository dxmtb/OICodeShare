/*
ID: dxmtb
PROG: 打鼹鼠
TIME: 2010.9.26
STATE: Solved
MEMO: dp
*/
#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;

const int MAXN=10005;

int d[MAXN],x[MAXN],y[MAXN],t[MAXN];
int n,m,re;

int main()
{
	freopen("mouse.in","r",stdin);
	freopen("mouse.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=0;i<m;i++)
	{
		scanf("%d%d%d",t+i,x+i,y+i);
		d[i]=1;
		for(int j=0;j<i;j++)
			if (d[j]+1>d[i]&&abs(x[i]-x[j])+abs(y[i]-y[j])<=t[i]-t[j])
				d[i]=d[j]+1;
		if (d[i]>re)
			re=d[i];
	}
	printf("%d\n",re);
	return 0;
}

