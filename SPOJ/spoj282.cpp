/*
ID: dxmtb
PROG: spoj282 Muddy Fields
TIME: 2010.8.22
STATE: Solved
MEMO: 二分图最小覆盖建模
*/
#include <cstdio>
#include <cstring>
using namespace std;

const int MAXN=50,MAXM=MAXN*MAXN;

struct Node
{
	int v;
	Node *next;
	Node(int a,Node *b):v(a),next(b){}
};

int R,C;
char map[MAXN][MAXN+10];
int r[MAXN][MAXN],c[MAXN][MAXN];
int mr,mc;
Node *g[MAXM];

void add(int a,int b)
{
	g[a]=new Node(b,g[a]);
}

void build()
{
	memset(r,-1,sizeof(r));
	memset(c,-1,sizeof(c));
	int timer=0;
	for(int i=0;i<R;i++)
	{
		int j;
		for(j=0;j<C;j++)
			if (map[i][j]=='*')
				if (j==0||map[i][j-1]=='.')
					r[i][j]=timer++;
				else r[i][j]=timer-1;
	}
	mr=timer;
	timer=0;
	for(int i=0;i<C;i++)
	{
		int j;
		for(j=0;j<R;j++)
			if (map[j][i]=='*')
				if (j==0||map[j-1][i]=='.')
					c[j][i]=timer++;
				else c[j][i]=timer-1;
	}
	mc=timer;
	for(int i=0;i<R;i++)
		for(int j=0;j<C;j++)
			if (map[i][j]=='*')
				add(r[i][j],c[i][j]);
}

int mat[MAXM],match;
bool used[MAXM];

bool find(int u)
{
	for(Node *p=g[u];p;p=p->next)
	{
		int i=p->v;
		if (!used[i])
		{
			used[i]=true;
			if (mat[i]==-1||find(mat[i]))
			{
				mat[i]=u;
				return true;
			}
		}
	}
	return false;
}

void hungary()
{
	memset(mat,-1,sizeof(mat));
	match=0;
	for(int i=0;i<mr;i++)
	{
		memset(used,false,sizeof(used));
		if (find(i))
			match++;
	}
}

int main()
{
	int t;
	scanf("%d\n",&t);
	for(int i=0;i<t;i++)
	{
		memset(map,0,sizeof(map));
		memset(g,0,sizeof(g));
		scanf("%d%d\n",&R,&C);
		for(int j=0;j<R;j++)
			scanf("%s\n",map[j]);
		build();
		hungary();
		printf("%d\n",match);
	}
	return 0;
}
