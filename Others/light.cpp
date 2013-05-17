#include <cstdio>

int main()
{
	freopen("light.in","r",stdin);
	freopen("light.out","w",stdout);
	int n;
	scanf("%d",&n);
	long long re=0;
	for(int i=0;i<n;i++)
	{
		double a;
		int t;
		scanf("%lf%d",&a,&t);
		for(int j=1;j<=t;j++)
			re^=(long long)(a*j);
	}
	printf("%lld\n",re);
	return 0;
}