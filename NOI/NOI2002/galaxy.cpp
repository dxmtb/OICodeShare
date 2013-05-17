/*
ID: dxmtb
PROG: NOI2002 银河英雄传说
TIME: 2011.02.23
STATE: Solved
MEMO: 并查集
*/
#include <cstdio>
#include <cstdlib>
const int MAXN=30000;

int father[MAXN+1];
int before[MAXN+1];
int size[MAXN+1];

inline int getfather(int i)
{
	if (father[i]==i)
		return i;
	int fi=getfather(father[i]);
	before[i]=before[i]+before[father[i]];
	return father[i]=fi;
}

inline void judge(int i,int j)
{
	int fi=getfather(i),fj=getfather(j);
	father[fi]=fj;
	before[fi]=size[fj];
	size[fj]+=size[fi];
}

int main()
{
	for(int i=1;i<=MAXN;i++)
		father[i]=i,size[i]=1;
	freopen("galaxy.in","r",stdin);
	freopen("galaxy.out","w",stdout);
	int T;
	scanf("%d",&T);
	while(T--)
	{
		char ch;
		int i,j;
		do {scanf("%c",&ch);}while(ch!='M'&&ch!='C');
		scanf("%d%d",&i,&j);
		if (ch=='M')
			judge(i,j);
		else 
		{
			if (getfather(i)==getfather(j))
				printf("%d\n",abs(before[i]-before[j])-1);
			else printf("-1\n");
		}
	}
	return 0;	
}
