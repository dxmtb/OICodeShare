/*
ID: dxmtb
PROG: NOIP2008 火柴棒等式
TIME: 2010.8.28
STATE: Solved
MEMO: 暴搜
*/
#include <cstdio>
using namespace std;

//#define _DEBUG

const int MAXN=24;
const int match[10]={6,2,5,5,4,5,6,3,7,6};
const int oo=0x7fffffff;

int n,re;
int t[2];

void search(int now,int dep,int need)
{
//	printf("%d %d %d %d %d\n",now,dep,need,t[0],t[1]);
	if (need>n)return;
	if (t[0]>oo/10||t[1]>oo/10)return ;
	if (now==2)
	{
		int x=t[0]+t[1];
		do
		{
			need+=match[x%10];
			x/=10;
		}while(x!=0);
		if (need==n)
		{
			re++;
//			printf("%d %d = %d need %d\n",t[0],t[1],t[0]+t[1],need);
		}
		return;
	}
	int i=dep?0:1;
	if (dep!=0)search(now+1,0,need);
	else search(now+1,0,need+match[0]);
	for(;i<10;i++)
	{
		t[now]=t[now]*10+i;
		search(now,dep+1,need+match[i]);
		t[now]/=10;
	}
}

int main()
{
	freopen("matches.in","r",stdin);
#ifndef _DEBUG
	freopen("matches.out","w",stdout);
#endif
	scanf("%d",&n);
	n-=4;
	search(0,0,0);
	printf("%d\n",re);
	return 0;
}
