/*
ID: dxmtb
PROG: [Scoi2010]序列操作
TIME: 2011.03.22
STATE: Solved
MEMO: 随机化
*/
#include <cstdio>
#include <cmath>
#include <cstdlib>
struct Point
{
	double x,y;
	Point(){}
	Point(double _x,double _y):x(_x),y(_y){}
};

Point operator + (const Point &a,const Point &b)
{
	return Point(a.x+b.x,a.y+b.y);
}

Point operator * (const Point &a,const double &b)
{
	return Point(a.x*b,a.y*b);
}

struct Line
{
	Point a,b;
}L1,L2;

int P,Q,R;

double myrandom()
{
	return (double(rand())/RAND_MAX)*2-1;
}

double getdis(Point a,Point b)
{
	double x=a.x-b.x,y=a.y-b.y;
	return sqrt(x*x+y*y);
}

double calcu(double c1,double c2)
{
	Point a=L1.a*c1+L1.b*(1-c1),b=L2.a*c2+L2.b*(1-c2);
	return getdis(L1.a,a)/P+getdis(a,b)/R+getdis(b,L2.b)/Q;
}

int main()
{
	freopen("1857.in","r",stdin);
	scanf("%lf%lf%lf%lf",&L1.a.x,&L1.a.y,&L1.b.x,&L1.b.y);
	scanf("%lf%lf%lf%lf",&L2.a.x,&L2.a.y,&L2.b.x,&L2.b.y);
	scanf("%d%d%d",&P,&Q,&R);
	double c1=0,c2=0;
	double re=calcu(c1,c2);
	for(double e=1;e>1e-10;e/=2)
	{
		int times=1000;
		while(times--)
		{
			double nc1=c1+myrandom()*e;
			double nc2=c2+myrandom()*e;
			if (nc1>=0 && nc1<=1 && nc2>=0 && nc2<=1)
			{
				double nre=calcu(nc1,nc2);
				if (nre<re)
					re=nre,c1=nc1,c2=nc2;
			}
		}
	}
	printf("%.2lf\n",re);
	return 0;
}
