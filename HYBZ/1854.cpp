/*
ID: dxmtb
PROG: Scoi2010 游戏 
TIME: 2011.03.21
STATE: Solved
MEMO: 并查集
*/
#include <cstdio>
#include <algorithm>
using namespace std;
const int MAXN=10005;

int N,M;
int father[MAXN];
bool all[MAXN];
int getfather(int x)
{
	if (father[x]==x)
		return x;
	return father[x]=getfather(father[x]);
}

void join(int x,int y)
{
	int fx=getfather(x),fy=getfather(y);
	if (fx==fy) all[fx]=true;
	else
	{
		if (fx>fy) swap(fx,fy);
		father[fx]=fy;
		all[fy]=(all[fy]|all[fx]);
	}
}

int main()
{
	freopen("1854.in","r",stdin);
	M=10000;
	scanf("%d",&N);
	for(int i=1;i<=M+1;i++)
		father[i]=i;
	for(int i=0;i<N;i++)
	{
		int a,b;
		scanf("%d%d",&a,&b);
		join(a,b);
	}
	for(int i=1;i<=M+1;i++)
		if (getfather(i)==i && !all[i])
		{
			printf("%d\n",i-1);
			return 0;
		}
}
