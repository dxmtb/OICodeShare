/*
ID: dxmtb
PROG: 纸
TIME: 2010.11.16
STATE: Solved
MEMO: 杂
*/
#include <cstdio>
#include <stack>
using namespace std;
const int MAXN=1005;

char map[MAXN][MAXN];
int tot[MAXN],d[MAXN][MAXN];
int n,m;
long long re;

int main()
{
	freopen("rectangle.in","r",stdin);
	freopen("rectangle.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
		tot[i]=tot[i-1]+i;
	for(int i=1;i<=n;i++)
	{
		scanf("%s",map[i]+1);
		for(int j=1;j<=m;j++)
		{
			if (map[i][j]=='*') d[i][j]=0;
			else d[i][j]=d[i-1][j]+1;
		}
	}
	for(int i=1;i<=n;i++)
	{
		stack<pair<int,int> >s;
		s.push(make_pair(0,0));
		for(int j=1;j<=m+1;j++)
		{
			while(!s.empty()&&d[i][j]<s.top().first)
			{
				pair<int,int> now=s.top();s.pop();
				if (!s.empty()&&d[i][j]>s.top().first)
				{
					re+=tot[j-now.second]*
					    (now.first-d[i][j]);
					now.first=d[i][j];
					s.push(now);
				}
				else
				{
					re+=tot[j-now.second]*
					    (now.first-s.top().first);
				}
			}
			if (d[i][j]>s.top().first)
				s.push(make_pair(d[i][j],j));
		}
	}
	printf("%lld\n",re);
	return 0;
}
			 
