/*
ID: dxmtb
PROG: 拯救
TIME: 2010.11.17
STATE: Solved
MEMO: dp
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int MAXN=1005;

typedef long long LL;

struct High
{
	int len,a[400];
	High(){reset();}
	void reset(){memset(a,0,sizeof(a));len=1;}
};

High operator + (High a,const int &num)
{
	if (num==1)
	{
		a.a[0]+=1;
		int i;
		for(i=0;a.a[i]>=10;i++)
		{
			a.a[i+1]+=1;
			a.a[i]-=10;
		}
		if (a.a[i]&&i+1>a.len)
			a.len=i+1;
	}
	else printf("wrong!\n");
	return a;
}

High operator + (const High &a,const High &b)
{	
	High ans;
	ans.len=max(a.len,b.len);
	for(int i=0;i<ans.len;i++)
	{
		ans.a[i]+=a.a[i]+b.a[i];
		ans.a[i+1]=ans.a[i]/10;
		ans.a[i]%=10;
	}
	if (ans.a[ans.len])
		ans.len++;
	return ans;
}

int a[MAXN];
int N;
High d[MAXN][2],g[MAXN],f[MAXN];

void print(const High a)
{
	for(int i=a.len-1;i>=0;i--)
		printf("%d",a.a[i]);
	printf("\n");
}

void print(const LL a)
{
	printf("%lld\n",a);
}

int main()
{
	freopen("savey.in","r",stdin);
	freopen("savey.out","w",stdout);
	scanf("%d",&N);
	for(int i=1;i<=N;i++)
		scanf("%d",a+i);
	for(int i=1;i<=N;i++)
	{
		g[i]=g[i-1]+1+g[i-1];
//		print(g[i]);
	}
	if (a[1]) d[1][0].a[0]=1;
	else d[1][1].a[0]=1;
//	if (a[1]) d[1][0]=1;
//	else d[1][1]=1;
	for(int i=1;i<=N;i++)
	{
		if (a[i])
			d[i][0]=d[i-1][1]+1+g[i-1],
			d[i][1]=d[i-1][0];
		else 
			d[i][0]=d[i-1][0],
			d[i][1]=d[i-1][1]+1+g[i-1];
	}
	print(d[N][0]);
//	printf("%lld\n",d[N][0]);
	return 0;
}
