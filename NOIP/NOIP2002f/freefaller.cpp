/*
ID: dxmtb
PROG: NOIP2002 自由落体
TIME: 2010.5.3
STATE: Solved
MEMO: 数学方法
*/
#include <cstdio>
#include <cmath>
using namespace std;

const int MAXN=100000,g=10;
const double e=0.00001;

double H,S1,V,L,K;
int n;

void init()
{
	scanf("%lf%lf%lf%lf%lf%d",&H,&S1,&V,&L,&K,&n);
}

int main() 
{
	freopen("freefaller.in","r",stdin);
	freopen("freefaller.out","w",stdout);
	init();
	double r=S1-V*sqrt(2*(H-K)/g)+L+e;
	double l=S1-V*sqrt(2*H/g)-e;
	if (l<0)l=0;
	if (r>n-1)r=n-1;
	l=ceil(l);
	r=floor(r);
	int re=int(r-l+1);
	if (re<0)re=0;
	printf("%d\n",re);
	return 0;
}
