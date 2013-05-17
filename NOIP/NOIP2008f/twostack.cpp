/*
ID: dxmtb
PROG: NOIP2008 双栈排序
TIME: 2010.8.30
STATE: Solved
MEMO: 判断二分图+构造
*/
#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;

#define noanswer {printf("0\n");exit(0);}
const int MAXN=2000;

int n,total;
int a[MAXN];
int s1[MAXN],s2[MAXN],t1,t2;
char way[MAXN*3];
int color[MAXN+1];
int d[MAXN];
bool against[MAXN+1][MAXN+1];

void draw(int now,int to)
{
	color[now]=to;
	for(int i=0;i<n;i++)
		if (against[now][i])
		{
			if (color[i]==to)
				noanswer
			if (!color[i])
				draw(i,3-to);
		}
}

void judgeit()
{
	d[n-1]=a[n-1];
	for(int i=n-2;i>=0;i--)
		d[i]=min(d[i+1],a[i]);
	for(int i=0;i<n;i++)
		for(int j=i+1;j<n-1;j++)
			if (a[i]<a[j]&&d[j+1]<a[i])
				against[i][j]=against[j][i]=true;
	for(int i=0;i<n;i++)
		if (!color[i])
			draw(i,1);
}

void solve()
{
	for(int i=0,now=1;i<n;i++)
	{
		if (i)printf(" ");
		if (color[i]==1)
		{
			s1[t1++]=a[i];
			printf("a");
		}
		else
		{
			s2[t2++]=a[i];
			printf("c");
		}
		while(s1[t1-1]==now||s2[t2-1]==now)
		{
			if (s1[t1-1]==now)
			{
				t1--;printf(" b");now++;
			}
			if (s2[t2-1]==now)
			{
				t2--;printf(" d");now++;
			}
		}
	}
}

int main()
{
	freopen("twostack.in","r",stdin);
	freopen("twostack.out","w",stdout);
	scanf("%d",&n);
	for(int i=0;i<n;i++)
		scanf("%d",a+i);
	judgeit(); 
	solve();
	return 0;
}
