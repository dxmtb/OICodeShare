/*
ID: dxmtb
PROG: 排排坐
TIME: 2010.11.9
STATE: Solved
MEMO: 搜索
*/
#include <cstdio>
using namespace std;
const int MAXN=15;

int N,re=0x7fffffff;
int sta[MAXN];
int targ[MAXN];

void dfs(int dep,int click)
{
	if (click>re)
		return ;
	if (dep==N)
	{
		for(int i=0;i<N;i++)
			if (sta[i]!=targ[i])
				return ;
		re=click;
		return ;
	}
	sta[dep]^=1;
	if (dep) sta[dep-1]^=1;
	sta[dep+1]^=1;
	dfs(dep+1,click+1);
	sta[dep]^=1;
	if (dep) sta[dep-1]^=1;
	sta[dep+1]^=1;
	dfs(dep+1,click);
}

int main()
{
	scanf("%d",&N);
	for(int i=0;i<N;i++)
		scanf("%d",sta+i);
	for(int i=0;i<N;i++)
		scanf("%d",targ+i);
	dfs(0,0);
	printf("%d\n",re);
	return 0;
}
