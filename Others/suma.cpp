/*
ID: dxmtb
PROG: Sum
TIME: 2010.11.19
STATE: Solved
MEMO: 平衡树
*/
#include <cstdio>
#include <set>
using namespace std;
const int MAXN=100005;

int N,K,P;
int a[MAXN],sum[MAXN];
set<int> s;

int main()
{
	freopen("suma.in","r",stdin);
	freopen("suma.out","w",stdout);
	scanf("%d%d%d",&N,&K,&P);
	for(int i=1;i<=N;i++)
	{
		scanf("%d",a+i);
		sum[i]=sum[i-1]+a[i];
		sum[i]%=P;
	}
	int re=P;
	s.insert(0);	
	for(int i=1;i<=N&&re!=K;i++)
	{
		set<int>::iterator it;
		it=s.upper_bound(sum[i]-K);
		it--;
		if (sum[i]-*it>=K&&sum[i]-*it<re)
			re=sum[i]-*it;
		it=s.upper_bound(sum[i]-P+K);
		it--;
		if (*it-sum[i]>=K&&sum[i]-*it+P<re)
			re=sum[i]-*it+P;
		s.insert(sum[i]);
	}
	printf("%d\n",re);
	return 0;
}
