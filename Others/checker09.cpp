/*
ID: dxmtb
PROG: 跳棋
TIME: 2011.03.09
STATE: Solved
MEMO: dp
*/
#include <cstdio>
#include <queue>
using namespace std;
typedef long long s64;

const int MAXN=1005;
const s64 oo=~0ull>>1;
const s64 big=1e15;

int A[MAXN];
int N;
s64 d[MAXN];

void spfa()
{
	queue<int> q;
	for(int i=1;i<N;i++)
		if (A[i])
		{
			d[i]=1;
			q.push(i);
		}
	while(q.size())
	{
		int i=q.front();q.pop();
		if (d[i]>big)
		{
			d[i]=oo;
			continue;
		}
		if (i+1<N && d[i+1]!=oo)
		{
			if (i>=1 && d[i]+d[i+1]<d[i-1])
			{
				d[i-1]=d[i]+d[i+1];
				q.push(i-1);
			}
			if (i+2<=N && d[i+1]+d[i]<d[i+2])
			{
				d[i+2]=d[i+1]+d[i];
				q.push(i+2);
			}
		}
		if (i>=1 && d[i-1]!=oo)
		{
			if (i>=2 && d[i]+d[i-1]<d[i-2])
			{
				d[i-2]=d[i]+d[i-1];
				q.push(i-2);
			}
			if (i+1<N && d[i]+d[i-1]<d[i+1])
			{
				d[i+1]=d[i]+d[i-1];
				q.push(i+1);
			}
		}
	}

}

int main()
{
	freopen("checker09.in","r",stdin);
	freopen("checker09.out","w",stdout);
	scanf("%d",&N);
	for(int i=0;i<N;i++)
	{
		scanf("%d",A+i);
		d[i]=oo;
	}
	spfa();
	s64 re1=0,re2=0;
	for(int i=1;i<N;i+=2)
		if (d[i]==oo) re1++;
		else re2+=d[i];
	printf("%lld %lld\n",re1,re2);
	return 0;
}
