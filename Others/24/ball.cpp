/*
ID: dxmtb
PROG: 线性规划与网络流24题 魔术球问题
TIME: 2010.7.11
STATE: Solved
MEMO: 最短路径覆盖
*/
#include <cstdio>
#include <cmath>
#include <cstring>
#include <vector>
using namespace std;

const int MAXN=102,MAXM=5200;

struct Node
{
	int v;
	Node *next;
	Node (int a,Node *b):v(a),next(b){}
};

int N;
vector<int>can[MAXM+1];
int mat[MAXM+1];
bool used[MAXM+1];

inline double sqr(double x)
{return x*x;}

bool find(int u,int m)
{
	for(vector<int>::iterator p=can[u].begin();
			p!=can[u].end()&&*p<=m;p++)
		if(!used[*p])
		{
			used[*p]=true;
			if (!mat[*p]||find(*p,m))
			{
				mat[*p]=u;
				return true;
			}
		}
		return false;
}

int solve(int m)
{
	int match=0;
	memset(mat,0,sizeof(mat));
	for(int i=1;i<=m;i++)
	{
		memset(used,false,sizeof(used));
		if (find(i,m))
			match++;
	}
	return	m-match;
}

int main()
{
	freopen("ball.in","r",stdin);
	freopen("ball.out","w",stdout);
	scanf("%d",&N);
	if (N==0)
	{
		printf("0\n");
		return 0;
	}
	int l=1,r=MAXM;
	for(int i=1;i<=MAXM;i++)
		for(int j=i+1;j<=MAXM;j++)
			if (sqr(int(sqrt(i+j)))==i+j)
				can[i].push_back(j);
//	for(int i=1;i<=MAXM;i++)
//		printf("%d\n",solve(i));
	while(l+1<r)
	{
		int mid=(l+r)/2;
		int x=solve(mid);
		if (x<=N)l=mid;
		else r=mid;
	}
	if (l+1==r)
	{
		int x=solve(r);
		if (x<=N)printf("%d\n",r);
		else printf("%d\n",l);
	}
	else printf("%d\n",r);
	return 0;
}
