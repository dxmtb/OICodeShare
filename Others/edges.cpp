#include <cstdio>

int n,m;

int main()
{
	freopen("edges.in","r",stdin);
	freopen("edges.out","w",stdout);
	scanf("%d%d",&n,&m);
	printf("%d\n",m-n+1);
	return 0;
}
