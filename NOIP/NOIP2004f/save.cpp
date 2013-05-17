/*
ID: dxmtb
PROG: NOIP2004 津津的储蓄计划
TIME: 2010.5.14
STATE: Solved
MEMO: 模拟
*/
#include <cstdio>
#include <cstdlib>
using namespace std;

int left,save;

void solve()
{
	for(int i=1;i<=12;i++)
	{
		int ys;
		scanf("%d",&ys);
		left+=300-ys;
		if (left<0)
		{
			printf("-%d\n",i);
			exit(0);
		}
		while (left>100)
			left-=100,save+=100;
	}
	printf("%0.f\n",left+1.2*save);
	
}

int main() 
{
	freopen("save.in","r",stdin);
	freopen("save.out","w",stdout);
	solve();
	return 0;
}
