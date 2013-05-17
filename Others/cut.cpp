/*
ID: dxmtb
PROG: ¾ØÐÎ·Ö¸î
TIME: 2010.11.15
STATE: Solved
MEMO: Ì°ÐÄ
*/
#include <cstdio>
#include <algorithm>
using namespace std;

const int MAXN=2005;

struct Node
{
	int data,ind;
}x[MAXN],y[MAXN];

inline bool operator < (const Node &a,const Node &b)
{
	return a.data>b.data;
}

int n,m,re;
int addx=1,addy=1;
int main()
{
	freopen("cut.in","r",stdin);
	freopen("cut.out","w",stdout);
	scanf("%d%d",&n,&m);
	n--,m--;
	for(int i=0;i<n;i++)
	{
		scanf("%d",&y[i].data);
		y[i].ind=i;
	}
	sort(y,y+n);
	for(int i=0;i<m;i++)
	{
		scanf("%d",&x[i].data);
		x[i].ind=i;
	}
	sort(x,x+m);
	int i,j;
	for(i=0,j=0;i<m&&j<n;)
	{
		if (x[i].data>y[j].data)
		{
			addy++;
			re+=x[i].data*addx;
			i++;
		}
		else
		{
			addx++;
			re+=y[j].data*addy;
			j++;
		}
	}
	for(;i<m;i++)
		re+=x[i].data*addx;
	for(;j<n;j++)
		re+=y[j].data*addy;
	printf("%d\n",re);
	return 0;
}
