/*
ID: dxmtb
PROG: 爆炸化合物
TIME: 2010.7.3
STATE: Solved
MEMO: 并查集
*/
#include <cstdio>
using namespace std;

const int MAXN=100000;

int father[MAXN];
int re;

int getfather(int a)
{
	if(father[a]==a)return a;
	return father[a]=getfather(father[a]);
}

void judge(int a,int b)
{
	int x=getfather(a),y=getfather(b);
	if(x==y)return;
	father[x]=y;
}

bool same(int a,int b)
{return getfather(a)==getfather(b);
}

int main()
{
	freopen("explosion.in","r",stdin);
	freopen("explosion.out","w",stdout);
	for(int i=0;i<MAXN;i++)
		father[i]=i;
	int a,b;
	while(scanf("%d%d",&a,&b)==2)
		if(same(a,b))re++;
		else judge(a,b);
	printf("%d\n",re);
	return 0;
}
