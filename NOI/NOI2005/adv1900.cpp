/*
ID: dxmtb
PROG: NOI2005 瑰丽华尔兹
TIME: 2011.03.01
STATE: Solved
MEMO: dp
*/
#include <cstdio>
#include <deque>
using namespace std;

const int MAXN=205;
const int oo=0x7fffffff;

int d[MAXN][MAXN];
int N,M,K;
int L[MAXN];
char g[MAXN][MAXN];
int Dt[MAXN];

int main()
{
	freopen("adv1900.in","r",stdin);
	freopen("adv1900.out","w",stdout);
	int x,y;
	scanf("%d%d%d%d%d",&N,&M,&x,&y,&K);
	x--,y--;
	for(int i=0;i<N;i++)
		scanf("%s",g[i]);
	for(int i=1;i<=K;i++)
	{
		int s,t;
		scanf("%d%d%d",&s,&t,Dt+i);
		L[i]=t-s+1;
	}
	for(int i=0;i<N;i++)
		for(int j=0;j<M;j++)
			d[i][j]=-oo;
	d[x][y]=0;
	deque<pair<int,int> > q;
	int tmp;
	for(int k=1;k<=K;k++)
	{
		switch (Dt[k])
		{
			case 1:
				for(int j=0;j<M;j++)
				{
					q.clear();
					for(int i=N-1;i>=0;i--)
						if (g[i][j]!='x')
						{
							if (d[i][j]>=0)
							{
								tmp=d[i][j]+i;
								while(q.size() && q.back().second<=tmp)
									q.pop_back();
								q.push_back(make_pair(i,tmp));
							}
							while(q.size()&&q.front().first>i+L[k])
								q.pop_front();
							if (q.size())
								d[i][j]=q.front().second-i;
							else d[i][j]=-oo;
						}
						else q.clear();
				}
				break;
			case 2:
				for(int j=0;j<M;j++)
				{
					q.clear();
					for(int i=0;i<N;i++)
						if (g[i][j]!='x')
						{
							if (d[i][j]>=0)
							{
								tmp=d[i][j]-i;
								while(q.size() && q.back().second<=tmp)
									q.pop_back();
								q.push_back(make_pair(i,tmp));
							}
							while(q.size() && q.front().first<i-L[k])
								q.pop_front();
							if (q.size())
								d[i][j]=q.front().second+i;
							else d[i][j]=-oo;
						}
						else q.clear();
				}
				break;
			case 3:
				for(int i=0;i<N;i++)
				{
					q.clear();
					for(int j=M-1;j>=0;j--)
						if (g[i][j]!='x')
						{
							if (d[i][j]>=0)
							{
								tmp=d[i][j]+j;
								while(q.size() && q.back().second<=tmp)
									q.pop_back();
								q.push_back(make_pair(j,tmp));
							}
							while(q.size() && q.front().first>j+L[k])
								q.pop_front();
							if (q.size())
								d[i][j]=q.front().second-j;
							else d[i][j]=-oo;
						}
						else q.clear();
				}
				break;
			case 4:
				for(int i=0;i<N;i++)
				{
					q.clear();
					for(int j=0;j<M;j++)
						if (g[i][j]!='x')
						{
							if (d[i][j]>=0)
							{
								tmp=d[i][j]-j;
								while(q.size() && q.back().second<=tmp)
									q.pop_back();
								q.push_back(make_pair(j,tmp));
							}
							while(q.size() && q.front().first<j-L[k])
								q.pop_front();
							if (q.size())
								d[i][j]=q.front().second+j;
							else d[i][j]=-oo;
						}
						else q.clear();
				}
				break;
		}
	}
	int re=0;
	for(int i=0;i<N;i++)
		for(int j=0;j<M;j++)
			if (d[i][j]>re)
				re=d[i][j];
	printf("%d\n",re);
	return 0;
}
