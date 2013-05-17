/*
ID: dxmtb
PROG: 卫星
TIME: 2010.7.6
STATE: Solved
MEMO: 点积+叉积
*/
#include <cstdio>
#include <iostream>
#include <cmath>
using namespace std;
#define PI 3.14159265
struct Node
{
	double x,y,z;
	Node(double a=0,double b=0,double c=0):x(a),y(b),z(c){}
};
#define Vec Node

const int MAXN=50;
const double R=6400,H=400;
const double small=1e-6;

int n,m;
Node sa[MAXN],ro[MAXN];

double mo2(Vec a)
{
	return (pow(a.x,2)+pow(a.y,2)+pow(a.z,2));
}

double cross2(Vec a,Vec b)
{
	return (mo2(Node(a.y*b.z-b.y*a.z,a.z*b.x-a.x*b.z,a.x*b.y-b.x*a.y)));
}

double dj(Vec a,Vec b)
{
	return (a.x*b.x+a.y*b.y+a.z*b.z);
}

int main()
{
	freopen("satellites.in","r",stdin);
	freopen("satellites.out","w",stdout);
	cin>>n;
	for(int i=0;i<n;i++)
	{
		double a,b;
		cin>>b>>a;
		ro[i].x=(R+H)*sin(a*PI/180)*cos(b*PI/180);
		ro[i].y=(R+H)*cos(a*PI/180)*cos(b*PI/180);
		ro[i].z=(R+H)*sin(b*PI/180);
	}
	cin>>m;
	for(int i=0;i<m;i++)
	{
		double a,b,h;
		cin>>b>>a>>h;
		sa[i].x=(R+h)*sin(a*PI/180)*cos(b*PI/180);
		sa[i].y=(R+h)*cos(a*PI/180)*cos(b*PI/180);
		sa[i].z=(R+h)*sin(b*PI/180);
	}
	for(int i=0;i<n;i++)
	{
		int timer=0;
		for(int j=0;j<m;j++)
		{
			Vec a(ro[i].x-sa[j].x,a.y=ro[i].y-sa[j].y,a.z=ro[i].z-sa[j].z),
				b(-sa[j].x,-sa[j].y,-sa[j].z),
				e(-ro[i].x,-ro[i].y,-ro[i].z),
				f(sa[j].x-ro[i].x,sa[j].y-ro[i].y,sa[j].z-ro[i].z);
			double d=cross2(a,b);
			double c=mo2(a)*(small+R)*(small+R);
			if (d>=c)
				timer++;
			else
				if (dj(a,b)<=0||dj(f,e)<=0)
					timer++;
			if (timer==3)
			{
				printf("%d\n",i);
				break;
			}
		}
	}
	return 0;
}


