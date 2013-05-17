/*
ID: dxmtb
PROG: 移动骷髅
TIME: 2010.11.9
STATE: Solved
MEMO: bfs
*/
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <set>
#include <queue>
using namespace std;
const int way[4][2]={{-1,0},{1,0},{0,-1},{0,1}};
const int co[5]={10000,1000,100,10,1};
const int MO=1741013;
int ran[5][5];

struct Node
{
	bool map[5][5];
	int x,y,dep;
}begin;

struct HashNode
{
	bool map[5][5];
	int x,y;
	HashNode(const Node &no)
	{
		memcpy(map,no.map,sizeof(map));
		x=no.x;y=no.y;
	}
};

inline bool operator < (const HashNode &a,const HashNode &b)
{
	if (a.x!=b.x)
		return a.x<b.x;
	if (a.y!=b.y)
		return a.y<b.y;
	for(int i=0;i<5;i++)
		for(int j=0;j<5;j++)
			if (a.map[i][j]!=b.map[i][j])
				return a.map[i][j]<b.map[i][j];
	return false;
};

int top,N;

set<HashNode> hash[MO];

int gethash(const Node &no)
{
	int has=0;
	for(int x=0;x<5;x++)
		for(int y=0;y<5;y++)
		{
			has+=ran[x][y]*(no.map[x][y]+(x==no.x&&y==no.y));
			has%=MO;
		}
	return has;
}
void insert(const Node &no)
{
	int has=gethash(no);
	HashNode ne(no);
	hash[has].insert(ne);
}
bool find(const Node &no)
{
	int has=gethash(no);
	HashNode ne(no);
	return hash[has].find(ne)!=hash[has].end();
}
void bfs(int level)
{
	queue<Node> q;	
	q.push(begin);
	while(q.size())
	{
		Node now=q.front();q.pop();
		for(int x=0;x<5;x++)
		for(int y=0;y<5;y++)
		if (now.map[x][y])
		{
			for(int j=0;j<4;j++)
			{
				Node expand=now;
				expand.dep++;
				expand.map[x][y]=false;
				int xx=x,yy=y;
				while(true)
				{
					xx+=way[j][0];
					yy+=way[j][1];
					if (xx>=0&&xx<5&&yy>=0&&yy<5)
					{
					if (expand.map[xx][yy])
					{
						xx-=way[j][0];
						yy-=way[j][1];
						expand.map[xx][yy]=true;
						if (x==expand.x&&y==expand.y)
							expand.x=xx,
							expand.y=yy;
						if (!find(expand))
						{
							if (expand.x==2&&expand.y==2)
							{
								printf("level %d:\n%d\n",level,expand.dep);
								return ;
							}
							insert(expand);
							q.push(expand);
						}
						break;
					}
					}
					else break;
				}
			}
		}
	}
	printf("No solution!\n");
}
int main()
{
	freopen("klgame.in","r",stdin);
	freopen("klgame.out","w",stdout);
	srand(MO);
	for(int x=0;x<5;x++)
		for(int y=0;y<5;y++)
			ran[x][y]=random()%MO;
	scanf("%d",&N);
	int map[5];
	for(int i=1;i<=N;i++)
	{
		for(int x=0;x<5;x++)
		{
			scanf("%d",map+x);
			for(int y=0;y<5;y++)
			{
				int num=map[x]/co[y]%10;
				begin.map[x][y]=num;
				if (num==2)
					begin.x=x,begin.y=y;
			}
		}
		bfs(i);
	}
	return 0;
}
