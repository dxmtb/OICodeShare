/*
ID: dxmtb
PROG: 阶梯教室设备利用
TIME: 2010.9.19
STATE: Solved
MEMO: dp
*/
#include <cstdio>
#include <algorithm>
using namespace std;

const int MAXN=10005;

struct Node
{
	int p,k;
}lect[MAXN];

bool operator < (Node a,Node b)
{
	return a.p<b.p||(a.p==b.p&&a.k<b.k);
}

int d[MAXN+1];
int n,re;

int main()
{
	freopen("rez.in","r",stdin);
	freopen("rez.out","w",stdout);
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d%d",&lect[i].p,&lect[i].k);
	lect[0].p=0;lect[0].k=0;
	sort(lect+1,lect+1+n);
	for(int i=1;i<=n;i++)
	{
		int time=lect[i].k-lect[i].p;
		for(int j=0;j<i;j++)
			if (lect[j].k<=lect[i].p&&d[i]<d[j]+time)
				d[i]=d[j]+time;
	}
	re=0;
	for(int i=1;i<=n;i++)
		if (re<d[i])
			re=d[i];
	printf("%d\n",re);
	return 0;
}
