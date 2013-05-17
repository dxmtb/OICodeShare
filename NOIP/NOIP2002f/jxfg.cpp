/*
ID: dxmtb
PROG: NOIP2002 矩形覆盖
TIME: 2010.7.27
STATE: Solved
MEMO: 搜索+枚举分割线
*/
#include <cstdio>
#include <algorithm>
using namespace std;

const int MAXN=50;
const int oo=0x7fffffff;

struct Node
{
	int x,y;
}p[MAXN];

bool cmpx(Node a,Node b)
{
	return a.x<b.x;
}

bool cmpy(Node a,Node b)
{
	return a.y<b.y;
}

int n,m;

int get(int k,int l,int r)
{
	if (r-l+1<=k)return 0;
	if (k==1)
	{
		int ax=0,ix=oo;
		int ay=0,iy=oo;
		for(int i=l;i<=r;i++)
		{
			if (p[i].y<iy)
				iy=p[i].y;
			if (p[i].y>ay)
				ay=p[i].y;
			if (p[i].x<ix)
				ix=p[i].x;
			if (p[i].x>ax)
				ax=p[i].x;

		}
		return (ax-ix)*(ay-iy);
	}
	else
	{
		int re=oo;
		sort(p+l,p+r+1,cmpx);
		for(int i=l;i<r;i++)
			for(int j=1;j<k;j++)
			{
				int t1=get(j,l,i);
				int t2=get(k-j,i+1,r);
				if (t1+t2<re)
					re=t1+t2;
			}
		sort(p+l,p+r+1,cmpy);
		for(int i=l;i<r;i++)
			for(int j=1;j<k;j++)
			{
				int t1=get(j,l,i);
				int t2=get(k-j,i+1,r);
				if (t1+t2<re)
					re=t1+t2;
			}
		sort(p+l,p+r+1,cmpx);
		return re;
	}
}	

int main()
{
	freopen("jxfg.in","r",stdin);
	freopen("jxfg.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=0;i<n;i++)
		scanf("%d%d",&p[i].y,&p[i].x);
	printf("%d\n",get(m,0,n-1));
	return 0;
}
