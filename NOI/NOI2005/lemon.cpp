/*
 * Problem: NOI2005 月下柠檬树
 * Time: 2011.06.23
 * Author: dxmtb
 * State: Solved
 * Memo: 自适应simpson法
*/
#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;

const int MAXN=505;
const double PI=3.1415926535897932384626433832795029;
const double eps=1e-7;
#define sqr(x) ((x)*(x))

struct Line
{
	double l,r,k,b,y1,y2;
}line[MAXN],*back=line;

struct Circle
{
	double H,R;
}C[MAXN];

inline int sgn(double a)
{
	if (fabs(a)<eps)
		return 0;
	if (a>0) return 1;
	return -1;
}

inline int sgn(double &a,double &b)
{
	return sgn(a-b);
}

int N;

inline void addline(const Circle &a,const Circle &b)
{
	if (b.H-a.H<fabs(a.R-b.R))
		return ;
	double d=b.H-a.H,sub=b.R-a.R;
	double cosalpha=sub/d;
	double sinalpha=sqrt(1.0-cosalpha*cosalpha);
	double l=a.H-a.R*cosalpha,r=b.H-b.R*cosalpha;
	double k=sub*sinalpha/(r-l);
	back->k=k;
	back->b=a.R*sinalpha-k*l;
	back->l=l,back->r=r;
	back++;
	back->y1=sqrt(sqr(a.R)-sqr(a.H-l));
	back->y2=sqrt(sqr(b.R)-sqr(b.H-r));
}

void init()
{
	double alpha;
	scanf("%d%lf",&N,&alpha);
	for(int i=0;i<=N;i++)
		scanf("%lf",&C[i].H);
	for(int i=0;i<N;i++)
		scanf("%lf",&C[i].R);
	C[N].R=0;
	for(int i=1;i<=N;i++)
		C[i].H+=C[i-1].H;
	alpha=1.0/tan(alpha);
	for(int i=0;i<=N;i++)
		C[i].H=C[i].H*alpha;
}

inline void Max(double &a,double b)
{
	if (b>a)
		a=b;
}

double getf(double x)
{
	double y=0;
	for(int i=0;i<=N;i++)
		Max(y,sqr(C[i].R)-sqr(x-C[i].H));
	y=sqrt(y);
	for(Line *i=line;i<back;i++)
		if (sgn(i->l,x)<=0 && sgn(x,i->r)<=0)
			Max(y,i->k*x+i->b);
	return y;
}

double simpson(double l,double r)
{
	return (getf(l)+getf(r)+4.0*getf((l+r)/2))/6.0*(r-l);
}

double rsimpson(double l,double r)
{
	double mid=(l+r)/2;
	double s1=simpson(l,r),s2=simpson(l,mid),s3=simpson(mid,r);
	if (fabs(s1-s2-s3)<eps*15)
		return s1;
	return rsimpson(l,mid)+rsimpson(mid,r);
}

int main()
{
	freopen("lemon.in","r",stdin);
	freopen("lemon.out","w",stdout);
	init();
	for(int i=0;i<N;i++)
		addline(C[i],C[i+1]);
	double l=10000,r=-10000;
	for(int i=0;i<N;i++)
	{
		if (C[i].H-C[i].R<l)
			l=C[i].H-C[i].R;
		if (C[i].H+C[i].R>r)
			r=C[i].H+C[i].R;
	}
	for(Line *i=line;i<back;i++)
	{
		if (i->l<l)
			l=i->l;
		if (i->r>r)
			r=i->r;
	}
	printf("%.2lf\n",rsimpson(l,r)*2);
	return 0;
}
