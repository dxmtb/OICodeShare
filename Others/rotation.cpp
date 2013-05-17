/*
ID: dxmtb
PROG: The Rotation Game
TIME: 2010.10.20
STATE: Solved
MEMO: 迭代加深搜索+剪枝
*/
#include <cstdio>
#include <string>
using namespace std;

const int MAXN=24;
const int ex[8][7]={
				{22,20,15,11,6,2,0},
				{23,21,17,12,8,3,1},
				{4,5,6,7,8,9,10},
				{13,14,15,16,17,18,19},
				{1,3,8,12,17,21,23},
				{0,2,6,11,15,20,22},
				{19,18,17,16,15,14,13},
				{10,9,8,7,6,5,4},
				};
const int same[8]={6,7,8,11,12,15,16,17};
const int op[8]={5,4,7,6,1,0,3,2};

string begin;

bool findbool;
inline int final(const string &now,int &sa)
{
	int _count[3]={0,0,0};
	sa=now[same[0]]-'0';
	for(int i=0;i<8;i++)
		_count[now[same[i]]-'1']++;
	return 8-max(max(_count[0],_count[1]),_count[2]);
}

int maxdep;

char now[30];
inline void move(int i)
{
	int temp=now[ex[i][6]];
	for(int j=6;j;j--)
		now[ex[i][j]]=now[ex[i][j-1]];
	now[ex[i][0]]=temp;
}

char way[20];
void dfs(int dep)
{
	if (dep>maxdep||findbool==true)
		return ;
	int sa;
	for(int i=0;i<8&&!findbool;i++)
	{
		way[dep]='A'+i;
		move(i);
		int w=final(now,sa);
		if (!w)
		{
			findbool=true;
			for(int i=0;i<=dep;i++)
				printf("%c",way[i]);
			printf("\n%d\n",sa);
			return ;
		}
		if (w+dep<=maxdep) dfs(dep+1);
		move(op[i]);
	}
}

void solve()
{
	int sa,w;
	w=final(now,sa);
	if (!w)
	{
		printf("No moves needed\n%d\n",sa);
		return;
	}
	maxdep=w;
	findbool=false;
	while(!findbool)
	{
		dfs(0);
		maxdep++;
	}
}

int main()
{
	freopen("rotation.in","r",stdin);
	freopen("rotation.out","w",stdout);
	scanf("%d",now);
	while(now[0])
	{
		now[0]+='0';
		for(int i=1;i<MAXN;i++)
		{
			scanf("%d",now+i);
			now[i]+='0';
		}
		solve();
		scanf("%d",now);
	}
	return 0;
}
