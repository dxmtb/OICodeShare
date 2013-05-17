/*
ID: dxmtb
PROG: HAOI2007 理想的正方形
TIME: 2011.03.16
STATE: Solved
MEMO: dp 单调队列
*/
#include <cstdio>
#include <deque>
using namespace std;

const int MAXN=1005;

int N,M,K;
int a[MAXN][MAXN];
deque<pair<int,int> > b1[MAXN],b2[MAXN];

int main()
{
	freopen("square.in","r",stdin);
	freopen("square.out","w",stdout);
	scanf("%d%d%d",&N,&M,&K);
	for(int i=1;i<=N;i++)
		for(int j=1;j<=M;j++)
			scanf("%d",a[i]+j);
	for(int i=1;i<=N;i++)
	{
		if (K>=1)
		{
			b1[i].push_front(make_pair(K-1,a[i][K-1]));//max
			b2[i].push_front(make_pair(K-1,a[i][K-1]));//min
		}
		for(int j=K-2;j;j--)
		{
			if (a[i][j]>b1[i].front().second)
				b1[i].push_front(make_pair(j,a[i][j]));
			if (a[i][j]<b2[i].front().second)
				b2[i].push_front(make_pair(j,a[i][j]));
		}
	}
	int re=0x7fffffff;
	for(int i=1;i+K-1<=M;i++)
	{
		for(int j=1;j<=N;j++)
		{
			while(b1[j].size() && b1[j].back().second<a[j][i+K-1]) b1[j].pop_back();
			b1[j].push_back(make_pair(i+K-1,a[j][i+K-1]));
			while(b2[j].size() && b2[j].back().second>a[j][i+K-1]) b2[j].pop_back();
			b2[j].push_back(make_pair(i+K-1,a[j][i+K-1]));
			if(b1[j].front().first<i) b1[j].pop_front();
			if(b2[j].front().first<i) b2[j].pop_front();
		}
		deque<pair<int,int> > q1,q2;
		if (K>=1)
		{
			q1.push_front(make_pair(K-1,b1[K-1].front().second));
			q2.push_front(make_pair(K-1,b2[K-1].front().second));
		}
		for(int j=K-2;j;j--)
		{
			if (b1[j].front().second>q1.front().second)
				q1.push_front(make_pair(j,b1[j].front().second));
			if (b2[j].front().second<q2.front().second)
				q2.push_front(make_pair(j,b2[j].front().second));
		}
		for(int j=K;j<=N;j++)
		{
			while(q1.size() && b1[j].front().second>q1.back().second) q1.pop_back();
			q1.push_back(make_pair(j,b1[j].front().second));
			while(q2.size() && b2[j].front().second<q2.back().second) q2.pop_back();
			q2.push_back(make_pair(j,b2[j].front().second));
			if (q1.front().first<=j-K) q1.pop_front();
			if (q2.front().first<=j-K) q2.pop_front();
			if(q1.front().second-q2.front().second<re)
				re=q1.front().second-q2.front().second;
		}
	}
	printf("%d\n",re);
	return 0;
}
