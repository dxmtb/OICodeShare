/*
 * Problem: 1670: [Usaco2006 Oct]Building the Moat护城河的挖掘 
 * Time: 2011.07.08
 * Author: dxmtb
 * State: Solved
 * Memo: 凸包
*/
#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;

const int MAXN=5005;

struct Point
{
	int x,y;
	Point(){}
	Point(int _x,int _y):x(_x),y(_y){}
}P[MAXN];

bool operator < (const Point &a,const Point &b)
{
	return a.y<b.y || (a.y==b.y && a.x<b.x);
}

Point operator - (const Point &a,const Point &b)
{
	return Point(b.x-a.x,b.y-a.y);
}

long long operator * (const Point &a,const Point &b)
{
	return (long long)a.x*b.y-(long long)a.y*b.x;
}

long long sqr(long long x)
{
	return x*x;
}

double getdis(const Point &a,const Point &b)
{
	return sqrt(sqr(a.x-b.x)+sqr(a.y-b.y));
}

Point *sta[MAXN];
int size;
int N;
void solve()
{
	sort(P,P+N);
	sta[0]=&P[0];
	sta[1]=&P[1];
	size=2;
	for(int i=2;i<N;i++)
	{
		while(size>1 && (P[i]-*sta[size-2])*(*sta[size-1]-*sta[size-2])>0)
			size--;
		sta[size++]=&P[i];
	}
	int tmp=size;
	sta[size++]=&P[N-1];
	for(int i=N-2;i>=0;i--)
	{
		while(size>tmp && (P[i]-*sta[size-2])*(*sta[size-1]-*sta[size-2])>0)
			size--;
		sta[size++]=&P[i];
	}
	double re=0;
	for(int i=0;i<size-1;i++)
		re+=getdis(*sta[i],*sta[i+1]);
	printf("%.2lf\n",re);
}

int main()
{
	scanf("%d",&N);
	for(int i=0;i<N;i++)
		scanf("%d%d",&P[i].x,&P[i].y);
	solve();
	return 0;
}
