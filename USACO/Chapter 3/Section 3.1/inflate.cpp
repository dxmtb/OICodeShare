/*
ID: dxmtb1
PROG: inflate
LANG: C++
*/
#include <cstdio>
using namespace std;

const int MAXN=10010;

int n,m;

int d[MAXN];
int w[MAXN],v[MAXN];

inline int max(int a,int b)
{
	if (a>b)return a;
	return b;
}

void init()
{
	scanf("%d%d",&m,&n);
	for(int i=0;i<n;i++)
		scanf("%d%d",&w[i],&v[i]);
}

void dp()
{
	for(int i=0;i<n;i++)
		for(int j=v[i];j<=m;j++)
			d[j]=max(d[j],d[j-v[i]]+w[i]);
	printf("%d\n",d[m]);
}

int main() 
{
	freopen("inflate.in","r",stdin);
	freopen("inflate.out","w",stdout);
	init();
	dp();
	return 0;
}
