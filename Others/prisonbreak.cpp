/*
ID: dxmtb
PROG: 越狱第1季第13集
TIME: 2010.9.15
STATE: Solved
MEMO: dp
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN=10005;

struct Node
{
	int a,b;
}s[MAXN];

int d[2][MAXN];
int re=0x7fffffff;
int n,P;

bool cmp(Node a,Node b)
{
	return a.a>b.a;
}

int main()
{
	freopen("prisonbreak.in","r",stdin);
	freopen("prisonbreak.out","w",stdout);
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d%d",&s[i].a,&s[i].b);
	sort(s+1,s+1+n,cmp);
	scanf("%d%d",&s[0].a,&P);
	for(int i=1,temp=P-(s[0].a-s[1].a);i<=n;i++)
		if (temp<0)
		{
			printf("-1\n");
			return 0;
		}
		else temp-=s[i].a-s[i+1].a,temp+=s[i].b;
	d[0][0]=P;
	for(int i=1;i<=n;i++)
	{
		memset(d[i&1],-1,sizeof(d[0]));
		for(int j=0;j<=i&&j<re;j++)
		{
			int temp=d[(i-1)&1][j]-(s[i-1].a-s[i].a);
			if (temp>=0&&temp>d[i&1][j])
				d[i&1][j]=temp;
			if (j)
			{
				temp=d[(i-1)&1][j-1]-(s[i-1].a-s[i].a);
				if (temp>=0&&temp+s[i].b>d[i&1][j])
					d[i&1][j]=temp+s[i].b;
			}
			if (d[i&1][j]-s[i].a>=0&&d[i&1][j]<re)
				re=j;
		}
	}
	printf("%d\n",re);
	return 0;
}

