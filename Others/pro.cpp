/*
ID: dxmtb
PROG: 相交的矩形
TIME: 2010.10.30
STATE: Solved
MEMO: 并查集
*/
#include <cstdio>
#include <algorithm>
using namespace std;

const int MAXN=7000;

int n,re;
int x1[MAXN],y1[MAXN],x2[MAXN],y2[MAXN];
int father[MAXN];

int getfather(int x)
{
	if (father[x]==x)return x;
	return father[x]=getfather(father[x]);
}

void Union(int x,int y)
{
	int fx=getfather(x),fy=getfather(y);
	if (fx==fy)return;
	else father[fx]=fy;
}

bool cross(int i,int j)
{
	int xx1=min(x2[i],x2[j]),yy1=min(y2[i],y2[j]);
	int xx2=max(x1[i],x1[j]),yy2=max(y1[i],y1[j]);
	if (xx1>=xx2&&yy1>=yy2)
	{
		if (xx1>xx2&&yy1>yy2)
			return true;
		if (xx1==xx2&&yy1>yy2)
			return true;
		if (xx1>xx2&&yy1==yy2)
			return true;
		return false;
	}
	else return false;
}

bool used[MAXN];
int main()
{
	freopen("pro.in","r",stdin);
	freopen("pro.out","w",stdout);
	scanf("%d",&n);
	for(int i=0;i<n;i++)
		scanf("%d%d%d%d",x1+i,y1+i,x2+i,y2+i);
	for(int i=0;i<n;i++)
		father[i]=i;
	for(int i=0;i<n;i++)
		for(int j=i+1;j<n;j++)
			if (cross(i,j))
				Union(i,j);
	for(int i=0;i<n;i++)
		getfather(i);
	for(int i=0;i<n;i++)
		if (!used[father[i]])
			re++,used[father[i]]=true;
	printf("%d\n",re);
	return 0;
}
