/*
ID: dxmtb1
PROG: fence4
LANG: C++
*/
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
using namespace std;

#define sqr(x) ((x)*(x))

const int MAXN=200;
const int oo=1050;
const double precision=1e-7;
const double small=0.01;

struct Node
{
	double x,y;
}p[MAXN],s,pc[MAXN];

inline double dis(Node a,Node b)
{
	return sqr(a.x-b.x)+sqr(a.y-b.y);
}

inline double det(double x1,double y1,double x2,double y2)
{
	return x1*y2-x2*y1;
}

inline double cross(Node a,Node b,Node c)
{
	return det(b.x-a.x,b.y-a.y,c.x-a.x,c.y-a.y);
}

inline int dblcmp(double d)
{
	if (fabs(d)<precision)
		return 0;
	return d>0?1:-1;
}

int segcross(Node a,Node b,Node c,Node d,Node &p)
{
	int d1,d2,d3,d4;
	double s1,s2,s3,s4;
	d1=dblcmp(s1=cross(a,b,c));
	d2=dblcmp(s2=cross(a,b,d));
	d3=dblcmp(s3=cross(c,d,a));
	d4=dblcmp(s4=cross(c,d,b));
	if ((d1^d2)==-2&&(d3^d4)==-2)
	{
		p.x=(c.x*s2-d.x*s1)/(s2-s1);
		p.y=(c.y*s2-d.y*s1)/(s2-s1);
		return 1;
	}

	return 0;
}

bool operator < (Node a,Node b)
{
	return cross(s,a,b)>0?true:false;
}

bool operator > (Node a,Node b)
{
	return !(a<b);
}

void qsort(Node q[],int l,int r)
{
 int i=l,j=r;
 Node mid=q[(l+l+r)/3];
 while (i<=j)
 {
  while (((q[i].x-s.x)*(mid.y-s.y)-(q[i].y-s.y)*(mid.x-s.x))>0)i++;
  while (((q[j].x-s.x)*(mid.y-s.y)-(q[j].y-s.y)*(mid.x-s.x))<0)j--;
  if(i<=j)swap(q[i++],q[j--]);
 }
 if(i<r)qsort(q,i,r);
 if(l<j)qsort(q,l,j);
}

int n,sum;
bool vis[MAXN];

inline int mo(int d)
{
	return (d+n)%n;
}

int main()
{
	freopen("fence4.in","r",stdin);
	freopen("fence4.out","w",stdout);
	scanf("%d",&n);
	scanf("%lf%lf",&s.x,&s.y);
	for(int i=0;i<n;i++)
		scanf("%lf%lf",&p[i].x,&p[i].y);
	memcpy(pc,p,n*sizeof(Node));
	qsort(pc,0,n-1);
	for(int i=0;i<n;i++)
	{
		double mdis=1e30;
		int now=n;
		Node temp={(pc[i].x+pc[mo(i+1)].x)/2+small,
			(pc[i].y+pc[mo(i+1)].y)/2+small};
		Node t;
		t.x=temp.x>s.x?oo:-oo;
		if (temp.x==s.x)t.x=s.x,t.y=temp.y>s.y?oo:-oo;
		else t.y=(t.x-s.x)*(temp.y-s.y)/(temp.x-s.x)+s.y;
		for(int j=0;j<n;j++)
			if (segcross(s,t,p[j],p[mo(j+1)],temp)==1)
			{
				double t_dis=dis(s,temp);
				if (t_dis<mdis)
				{
					mdis=t_dis;
					now=j;
				}
			}
		if (now!=n&&!vis[now]) vis[now]=true,sum++;
	}
	for(int i=0;i<n;i++)
	{
		double mdis=1e30;
		int now=n;
		Node temp={(pc[i].x+pc[mo(i+1)].x)/2-small,
			(pc[i].y+pc[mo(i+1)].y)/2-small};
		Node t;
		t.x=temp.x>s.x?oo:-oo;
		if (temp.x==s.x)t.x=s.x,t.y=temp.y>s.y?oo:-oo;
		else t.y=(t.x-s.x)*(temp.y-s.y)/(temp.x-s.x)+s.y;
		for(int j=0;j<n;j++)
			if (segcross(s,t,p[j],p[mo(j+1)],temp)==1)
			{
				double t_dis=dis(s,temp);
				if (t_dis<mdis)
				{
					mdis=t_dis;
					now=j;
				}
			}
		if (now!=n&&!vis[now]) vis[now]=true,sum++;
	}
	printf("%d\n",sum);
	for(int i=0;i<n-2;i++)
		if (vis[i])
			printf("%d %d %d %d\n",int(p[i].x),int(p[i].y),
					int(p[i+1].x),int(p[i+1].y));
	if (vis[n-1])
		printf("%d %d %d %d\n",int(p[0].x),int(p[0].y),
				int(p[n-1].x),int(p[n-1].y));
	if (vis[n-2])
		printf("%d %d %d %d\n",int(p[n-2].x),int(p[n-2].y),
				int(p[n-1].x),int(p[n-1].y));
	return 0;
}
