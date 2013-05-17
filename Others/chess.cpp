/*
ID: dxmtb
PROG: Chess
TIME: 2010.11.19
STATE: Solved
MEMO: 贪心
*/
#include <cstdio>
#include <algorithm>
using namespace std;
const int MAXN=100005;

int N,K,re;
int a[MAXN],b[MAXN];

int main()
{
	freopen("chess.in","r",stdin);
	freopen("chess.out","w",stdout);
	scanf("%d%d",&N,&K);
	for(int i=0;i<N;i++)
		scanf("%d",a+i);
	sort(a,a+N);
	for(int i=0;i<N-1;i++)
		b[i]=a[i+1]-a[i];
	sort(b,b+N-1);
	for(int i=0;i<K;i++)
		re+=b[i];
	printf("%d\n",re);
	return 0;
}
