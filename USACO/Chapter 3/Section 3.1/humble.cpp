/*
ID: dxmtb1
PROG: humble
LANG: C++
*/
#include <cstdio>

using namespace std;

const int MAXN=100010,MAXK=105;

int n,k;
int num[MAXK];
int re[MAXN+1],cord[MAXK];

void init()
{
	scanf("%d%d",&k,&n);
	for(int i=0;i<k;i++)
		scanf("%d",&num[i]);
}

void solve()
{
	int now=0;
	re[0]=1;
	while (now<n)
	{
		int min=0x7fffffff;
		int u;
		for(int i=0;i<k;i++)
				if (num[i]*re[cord[i]]<min)
				{
					u=i;
					min=num[i]*re[cord[i]];
				}
		++cord[u];
		re[++now]=min;
		for(int i=0;i<k;i++)
			if (num[i]*re[cord[i]]==min)
				cord[i]++;
	}
	printf("%d\n",re[n]);
}

int main() 
{
	freopen("humble.in","r",stdin);
	freopen("humble.out","w",stdout);
	init();
	solve();
	return 0;
}
