/*
ID: dxmtb1
PROG: fc
LANG: C++
*/
#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;

const int MAXN=10005;

struct Point
{
	double x,y;
	Point(){}
	Point(double _x,double _y):x(_x),y(_y){}
}P[MAXN];

bool operator < (const Point &a,const Point &b)
{
	return a.y<b.y || (a.y==b.y && a.x<b.x);
}

double operator * (const Point &a,const Point &b)
{
	return a.x*b.y-a.y*b.x;
}

Point operator - (const Point &a,const Point &b)
{
	return Point(a.x-b.x,a.y-b.y);
}

double getdis(const Point &a,const Point &b)
{
	return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}

int N;

void graham()
{
	sort(P,P+N);
	Point *sta[MAXN]={P,P+1};
	int size=2;
	for(int i=2;i<N;i++)
	{
		while(size>=2 && (*sta[size-1]-*sta[size-2])*(P[i]-*sta[size-1])<=0)
			size--;
		sta[size++]=P+i;
	}
	int ns=size;
	sta[size++]=P+N-2;
	for(int i=N-3;i>=0;i--)
	{
		while(size>ns && (*sta[size-1]-*sta[size-2])*(P[i]-*sta[size-1])<=0)
			size--;
		sta[size++]=P+i;
	}
	double re=0;
	for(int i=0;i<size-1;i++)
		re+=getdis(*sta[i],*sta[i+1]);
	printf("%.2lf\n",re);
}

int main()
{
	freopen("fc.in","r",stdin);
	freopen("fc.out","w",stdout);
	scanf("%d",&N);
	for(int i=0;i<N;i++)
		scanf("%lf%lf",&P[i].x,&P[i].y);
	if (N<=1)
		printf("0.00\n");
	else if (N==2)
		printf("%.2lf\n",getdis(P[0],P[1])*2);
	else graham();
	return 0;
}
