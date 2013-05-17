/*
 * Problem: NOI2001 食物链
 * Time: 2011.06.02
 * Author: dxmtb
 * State: Solved
 * Memo: 并查集
*/
#include <cstdio>

const int MAXN=50005;

int lv[MAXN],edge[MAXN],father[MAXN];
int getfather(int x)
{
	if (father[x]==x)
		return x;
	int fx=getfather(father[x]);
	edge[x]=(edge[x]+edge[father[x]])%3;
	return father[x]=fx;
}

bool join(int x,int y,int d)
{
	int fx=getfather(x),fy=getfather(y);
	if (fx!=fy)
	{
		int lv1=(lv[fx]-edge[x]);
		int lv2=lv1+d;
		lv[fy]=(lv2+edge[y])%3;
		if (lv[fy]<0)
			lv[fy]+=3;
		edge[fx]=(lv[fy]-lv[fx])%3;
		if (edge[fx]<0)
			edge[fx]+=3;
		father[fx]=fy;
		return true;
	}
	else
	{
		int lv1=(lv[fx]-edge[x])%3;
		if (lv1<0)
			lv1+=3;
		int lv2=(lv[fy]-edge[y])%3;
		if (lv2<0)
			lv2+=3;
		return (lv1+d)%3==lv2;
	}
}

int N,K;
int main()
{
	freopen("eat.in","r",stdin);
	freopen("eat.out","w",stdout);
	scanf("%d%d",&N,&K);
	for(int i=1;i<=N;i++)
	{
		father[i]=i;
		lv[i]=0;
		edge[i]=0;
	}
	int ans=0;
	for(int i=0;i<K;i++)
	{
		int d,x,y;
		scanf("%d%d%d",&d,&x,&y);
		if (x>N || y>N || (d==2 && x==y))
		{
			ans++;
			continue;
		}
		d--;
		if (!join(x,y,d))
			ans++;
	}
	printf("%d\n",ans);
	return 0;
}
