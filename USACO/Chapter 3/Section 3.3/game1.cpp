/*
ID: dxmtb1
PROG: game1
LANG: C++
*/
#include <cstdio>
using namespace std;

#define min(a,b) ((a)>(b)?(b):(a))

const int MAXN=102;
const int next[2]={1,0};

int s[MAXN],d[MAXN][MAXN];
int n;

void cal(int player,int l,int r)
{
	if (d[l][r])return ;
	cal(next[player],l+1,r);
	cal(next[player],l,r-1);
	d[l][r]=s[r]-s[l-1]-min(d[l+1][r],d[l][r-1]);
}

int main()
{
	freopen("game1.in","r",stdin);
	freopen("game1.out","w",stdout);
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",s+i);
		d[i][i]=s[i];
		s[i]+=s[i-1];
	}
	cal(0,1,n);
	printf("%d %d\n",d[1][n],min(d[2][n],d[1][n-1]));
	return 0;
}
