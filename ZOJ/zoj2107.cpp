/*
ID: dxmtb
PROG: zoj2107 Quoit Design
TIME: 2010.7.24
STATE: Solved
MEMO: 平面点对最短距离
*/
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <cstdlib>
using namespace std;

#define sqr(x) ((x)*(x))

const int MAXN=100005;
const double eps=1e-5;

struct Node{double x,y;int index;}a[MAXN],b[MAXN],c[MAXN];

int n;

inline double dis(Node a,Node b)
{
	return (sqr(a.x-b.x)+sqr(a.y-b.y));
}

void merge(Node x[],Node y[],int l,int m,int r)
{
	int i,a,b;
	for(i=l,a=l,b=m+1;a<=m&&b<=r;i++)
		if (y[a].y<y[b].y)x[i]=y[a++];
		else x[i]=y[b++];
	while(a<=m)x[i++]=y[a++];
	while(b<=r)x[i++]=y[b++];
	memcpy(y+l,x+l,sizeof(x[0])*(r-l+1));
}

double closest(Node a[],Node b[],Node c[],int l,int r)
{
	double re,r1,r2;
	if (r-l<1)exit(1);
	if (r-l==1)return dis(a[l],a[r]);
	else if (r-l==2)
	{
		re=dis(a[l],a[r]),
		r1=dis(a[l],a[l+1]),
		r2=dis(a[l+1],a[r]);
		if (r1<re)re=r1;
		if (r2<re)re=r2;
		return re;
	}
	int m=(l+r)/2;
	int i,k1,k2,k,j;
	for(i=l,k1=l,k2=m+1;i<=r;i++)
		if (b[i].index<=m) c[k1++]=b[i];
		else c[k2++]=b[i];
	re=closest(a,c,b,l,m);
	r1=closest(a,c,b,m+1,r);
	if (r1<re)re=r1;
	merge(b,c,l,m,r);
	k=l;
	for(i=l;i<=r;i++)
		if (fabs(b[i].x-b[m].x)<re)
			c[k++]=b[i];
	for(i=l;i<k;i++)
		for(j=i+1;j<k&&c[j].y-c[i].y<re;j++)
		{
			r1=dis(c[i],c[j]);
			if (r1<re)
				re=r1;
		}
	return re;
}

inline int cmpx(const void *p, const void *q){
    double temp = ((Node*)p)->x - ((Node*)q)->x;
    if (temp > 0) return 1;
    else if (fabs(temp) < eps) return 0;
    else return  - 1;
}
inline int cmpy(const void *p, const void *q){
    double temp = ((Node*)p)->y - ((Node*)q)->y;
    if (temp > 0) return 1;
    else if (fabs(temp) < eps) return 0;
    else return  - 1;
}

int main()
{
	freopen("2107.in","r",stdin);
	freopen("2107.out","w",stdout);
	scanf("%d",&n);
	while(n)
	{
		int i;
		for(i=0;i<n;i++)
			scanf("%lf%lf",&a[i].x,&a[i].y);
		qsort(a,n,sizeof(Node),cmpx);
		for(i=0;i<n;i++)
			a[i].index=i;
		memcpy(b,a,n*sizeof(a[0]));
		qsort(b,n,sizeof(Node),cmpy);
		double re=closest(a,b,c,0,n-1);
		printf("%.2f\n",sqrt(re)/2.0);
		scanf("%d",&n);
	}
	return 0;
}
