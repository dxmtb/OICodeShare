/*
ID: dxmtb
PROG: 质数取石子
TIME: 2010.9.19
STATE: Solved
MEMO: dp
*/
#include <cstdio>
#include <algorithm>
using namespace std;

const int MAXN=20005;
const int oo=0x7fffffff>>1;

int prime[MAXN],top;
bool flag[20000+1];

void getprime()
{
	for(int i=2;i<=20000;i++)
		flag[i]=true;
	for(int i=2;i<=20000;i++)
	{
		if (flag[i]) prime[top++]=i;
		for(int j=0;j<top;j++)
		{
			if (i*prime[j]<=20000)flag[i*prime[j]]=false;
			if (!(i%prime[j]))
				break;
		}
	}
//	for(int i=0;i<top;i++)
//		printf("%d\n",prime[i]);
}

int N;
int dd[MAXN+1],mm[MAXN+1];
void solve()
{
	for(int i=0;i<=N;i++)
	{
		if (flag[i]) dd[i]=1;
		else dd[i]=oo;
		for(int j=0;j<top&&dd[i]!=1;j++)
		{
			if (i<prime[j]) break;
			dd[i]=min(dd[i],mm[i-prime[j]]+1);
		}
		if (flag[i]) mm[i]=oo;
		else mm[i]=0;
		for(int j=0;j<top&&mm[i]<N;j++)
		{
			if (i<prime[j]) break;
			mm[i]=max(mm[i],dd[i-prime[j]]+1);
		}
	}
	if (dd[N]>=N)printf("-1\n");
	else printf("%d\n",dd[N]);
}

int main()
{
	freopen("stonegame.in","r",stdin);
	freopen("stonegame.out","w",stdout);
	getprime();
	int T;
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&N);
		solve();
	}
	return 0;
}
