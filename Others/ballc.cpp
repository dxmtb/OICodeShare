#include <cstdio>
#include <cmath>
using namespace std;
const int MAXN=1000000;

int n,x[MAXN],y[MAXN],w[MAXN];
double re;

int main()
{
	freopen("ballc.in","r",stdin);
	freopen("ballc.out","w",stdout);
	scanf("%d",&n);
	for(int i=0;i<n;i++)
		scanf("%d",w+i);
	for(int i=0;i<n;i++)
		scanf("%d%d",x+i,y+i);
	double xx=x[0],yy=y[0],ww=w[0];
	for(int i=1;i<n;i++)
	{
		xx=xx+w[i]*(x[i]-xx)/double(w[i]+ww);
		yy=yy+w[i]*(y[i]-yy)/double(w[i]+ww);
		ww+=w[i];
	}
//	printf("%lf %lf\n",xx,yy);
	for(int i=0;i<n;i++)
		re+=w[i]*(fabs(xx-x[i])+abs(yy-y[i]));
	printf("%.2lf\n",re);
	return 0;
}
