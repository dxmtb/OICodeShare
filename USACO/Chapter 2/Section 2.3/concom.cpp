/*
ID: dxmtb1
PROG: concom
LANG: C++
*/
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

const int MAXN=101;

struct Node
{
	int x,y,add;
};

int m,rate[MAXN][MAXN];

void change(int,int,int);

int main()
{
	queue<Node> q;
	memset(rate,0,sizeof(rate));
	freopen("concom.in","r",stdin);
	freopen("concom.out","w",stdout);
	scanf("%d",&m);
	for(int i=0;i<m;i++)
	{
		int x,y,z;
		scanf("%d%d%d",&x,&y,&z);
		rate[x][y]+=z;
		Node temp={x,y,z};
		q.push(temp);
	}
	while (!q.empty())
	{
		Node temp=q.front();
		q.pop();
		for(int i=1;i<MAXN;i++)
			if (rate[i][temp.x]>50&&i!=temp.x&&rate[i][temp.y]<100)
			{
				rate[i][temp.y]+=temp.add;
				Node now={i,temp.y,temp.add};
				q.push(now);
			}
	}
	for(int i=1;i<MAXN;i++)
		for(int j=1;j<MAXN;j++)
			if (i!=j&&rate[i][j]>50)
				printf("%d %d\n",i,j);
	return 0;
}
