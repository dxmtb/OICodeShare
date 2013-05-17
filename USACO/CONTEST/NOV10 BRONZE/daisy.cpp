/*
PROG: daisy
LANG: C++
ID: dxmtb1
*/
#include <cstdio>
using namespace std;

const int MAXN=255;

int N,M;
int father[MAXN];

inline int getfather(int u)
{
	if (father[u]==u)
		return u;
	return father[u]=getfather(father[u]);
}

inline void judge(int u,int v)
{
	int fu=getfather(u),fv=getfather(v);
	father[fv]=fu;
}

void init()
{
	for(int i=1;i<=N;i++)
		father[i]=i;
}

int main()
{
	freopen("daisy.in","r",stdin);
	freopen("daisy.out","w",stdout);
	scanf("%d%d",&N,&M);
	init();
	for(int i=0;i<M;i++)
	{
		int c1,c2;
		scanf("%d%d",&c1,&c2);
		judge(c1,c2);
	}
	bool flag=true;
	for(int i=2;i<=N;i++)
		if (getfather(i)!=getfather(1))
		{
			printf("%d\n",i);
			flag=false;
		}
	if (flag)
		printf("0\n");
	return 0;
}
