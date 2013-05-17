/*
ID: dxmtb
PROG: APIO2010 信号覆盖
TIME: 2010.7.25
STATE: Solved
MEMO: 计算几何
*/
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <iostream>
using namespace std;

struct Point
{
	long long x,y;
};

const int MAXN=1505;

int n;
Point p[MAXN],q[MAXN*2];

long long cross(Point a,Point b)
{
	return a.x*b.y-a.y*b.x;
}

long long C(long long  a,int b)
{
	if (b==3)return a*(a-1)*(a-2)/6;
	else if (b==4) return a*(a-1)*(a-2)*(a-3)/24;
	return 0;
}

bool operator < (Point a,Point b)
{
	if ((a.y>0)^(b.y>0)) return cross(a,b)>0?true:false;
	else return a.y>b.y;
}

int cmp(const void *a,const void *b)
{
	return (cross(*((Point*)a),*((Point*)b))>0)?1:-1;
}

void qsort(int l,int r)
{
 int i=l,j=r;
 Point mid=q[(l+l+r)/3];
 while (i<=j)
 {
  while ((q[i].x*mid.y-q[i].y*mid.x)>0)i++;
  while ((q[j].x*mid.y-q[j].y*mid.x)<0)j--;
  if(i<=j)swap(q[i++],q[j--]);
 }
 if(i<r)qsort(i,r);
 if(l<j)qsort(l,j);
}

long long get(int now)
{
	int i,j;
	for(i=0;i<now;i++)
		q[i].x=p[i].x-p[now].x,
		q[i].y=p[i].y-p[now].y;
	for(i=now+1;i<n;i++)
		q[i-1].x=p[i].x-p[now].x,
		q[i-1].y=p[i].y-p[now].y;
	qsort(0,n-2);
	memcpy(q+n-1,q,sizeof(Point)*(n-1));
	long long ret=0;
	for(i=0,j=1;i<n-1;i++)
	{
		while(cross(q[i],q[j])>0)j++;
		if (j-i>=3)
			ret+=(j-i-1)*(j-i-2)/2;
	}
	return ret;
}
								
int main()
{
	freopen("signaling.in","r",stdin);
	freopen("signaling.out","w",stdout);
	scanf("%d",&n);
	for(int i=0;i<n;i++)
		cin>>p[i].x>>p[i].y;
	long long p=0;
	for(int i=0;i<n;i++)
		p+=get(i);
	printf("%lf\n",double(2*C(n,4)-n*C(n-1,3)+p)/C(n,3)+3);
	return 0;
}

