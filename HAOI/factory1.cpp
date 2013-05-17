/*
ID: dxmtb
PROG: HAOI2010 工厂选址
TIME: 2011.03.16
STATE: Solved
MEMO: 贪心
*/
#include <cstdio>
#include <algorithm>
using namespace std;
const int MAXN=55,MAXM=50005;

int M,B,N;
int a[MAXM],h[MAXN],c[MAXM][MAXN];

int main()
{
	freopen("factory1.in","r",stdin);
	freopen("factory1.out","w",stdout);
	scanf("%d%d%d%d",&M,&B,h,&N);
	for(int i=0;i<M;i++)
		scanf("%d",a+i);
	for(int i=1;i<=N;i++)
		scanf("%d",h+i);
	for(int i=0;i<=N;i++)
		for(int j=0;j<M;j++)
			scanf("%d",c[j]+i);
	int re=0x7fffffff,ri=0;
	for(int i=1;i<=N;i++)
	{
		int ans=h[i]+h[0],tot=0;
		pair<int,int> b[MAXM];
		for(int j=0;j<M;j++)
		{
			ans+=c[j][0]*a[j],tot+=a[j];
			b[j].second=j;
			b[j].first=c[j][i]-c[j][0];
		}
		sort(b,b+M);
		for(int j=0;j<M;j++)
			if (tot>B)
			{
				int reduce=min(tot-B,a[b[j].second]);
				tot=tot-reduce;
				ans+=b[j].first*reduce;
			}
			else break;
		if (ans<re)
			re=ans,ri=i;
	}
	printf("%d\n%d\n",ri,re);
	return 0;
}
