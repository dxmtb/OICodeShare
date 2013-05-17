/*
ID: dxmtb
PROG: [Scoi2010]股票交易 
TIME: 2011.03.21
STATE: Solved
MEMO: dp+单调队列
*/
#include <cstdio>
#include <deque>
using namespace std;
const int MAXN=5005;
const int oo=0x7fffffff/2;

int N,P,W;
int AP[MAXN],BP[MAXN],AS[MAXN],BS[MAXN];
int d[MAXN][MAXN];

int main()
{
	freopen("1855.in","r",stdin);
	scanf("%d%d%d",&N,&P,&W);
	for(int i=1;i<=N;i++)
		scanf("%d%d%d%d",AP+i,BP+i,AS+i,BS+i);
	for(int i=1;i<=P;i++)
		d[1][i]=-oo;
	for(int i=2;i<=N+W+1;i++)
	{
		int *f=d[i],*g=d[i-W-1];
		for(int j=0;j<=P;j++)
			f[j]=d[i-1][j];
		if (i-W-1>=1)
		{
			const int &buy=AP[i-W-1],&blim=AS[i-W-1];
			deque<pair<int,int> > q;
			q.push_back(make_pair(g[0],0));
			for(int j=1;j<=P;j++)
			{
				while(q.size() && j-q.front().second>blim)
					q.pop_front();
				f[j]=max(f[j],q.front().first-j*buy);
				while(q.size() && q.back().first<g[j]+j*buy)
					q.pop_back();
				q.push_back(make_pair(g[j]+j*buy,j));
			}
			const int &sell=BP[i-W-1],&slim=BS[i-W-1];
			q.clear();
			q.push_back(make_pair(g[P]+P*sell,P));
			for(int j=P-1;j>=0;j--)
			{
				while(q.size() && q.front().second-j>slim)
					q.pop_front();
				f[j]=max(f[j],q.front().first-j*sell);
				while(q.size() && q.back().first<g[j]+j*sell)
					q.pop_back();
				q.push_back(make_pair(g[j]+j*sell,j));
			}
		}
	}
	printf("%d\n",d[N+W+1][0]);
	return 0;
}
