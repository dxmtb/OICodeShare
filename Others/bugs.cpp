#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

const int MAXN=21,MAXM=200,MAXINT=0x7fffffff;

int n,m;
int t[MAXM];
char s1[MAXM][MAXN],s2[MAXM][MAXN];
int dis[1<<(MAXN+1)];
bool in[1<<(MAXN+1)];
vector<int> v;

bool comp(int a,int b)
{return dis[a]>dis[b];}

void init()
{
	scanf("%d%d",&n,&m);	
	for(int i=0;i<m;i++)
		scanf("%d%s%s",&t[i],s1[i],s2[i]);
	for(int i=0;i<1<<n;i++)dis[i]=MAXINT;
}

int spfa()
{
	queue<int>q;
	q.push((1<<n)-1);
	in[(1<<n)-1]=true;
	dis[(1<<n)-1]=0;
	while (!q.empty())
	{
		int now=q.front();
		q.pop();
		in[now]=false;
		for(int i=0;i<m;i++)
		{
			int j;
			for(j=0;j<n;j++)
				if (s1[i][j]=='+'&&!(now>>(n-j-1)&1))
					break;
				else if (s1[i][j]=='-'&&(now>>(n-j-1)&1))
					break;
			if (j<n)continue;
			int cur=now;
			for(int j=0;j<n;j++)
				if (s2[i][j]=='+')
					cur=cur|(1<<(n-j-1));
				else if (s2[i][j]=='-'&&(now>>(n-j-1))&1)
					cur=cur^(1<<(n-j-1));
			if (dis[cur]>dis[now]+t[i])
			{
				dis[cur]=dis[now]+t[i];
				if (!in[cur])
				{
					q.push(cur);
					in[cur]=true;
				}
			}
		}
	}
	if (dis[0]==MAXINT)return -1;
	else return dis[0];
}

int main()
{
	freopen("bugs.in","r",stdin);
	freopen("bugs.out","w",stdout);
	init();
	printf("%d\n",spfa());
	return 0;
}
