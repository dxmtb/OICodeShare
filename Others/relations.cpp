#include <fstream>
using namespace std;

const int MAXN=20000;

ifstream fin ("relations.in");
ofstream fout ("relations.out");

int n,m,father[MAXN+1];

void judge(int ,int);
bool same(int ,int);
int getfather(int);

int main()
{
	fin>>n>>m;
	memset(father,0,sizeof(father));
	for(int i=1;i<=n;i++)
		father[i]=i;
	for(int i=1;i<=m;i++)
	{
		int x,y;
		fin>>x>>y;
		judge(x,y);
	}
	int q;
	fin>>q;
	for(int i=1;i<=q;i++)
	{
		int x,y;
		fin>>x>>y;
		if (same(x,y))
			fout<<"Yes"<<endl;
		else fout<<"No"<<endl;
	}
	return 0;
}

int getfather(int x)
{
	if (x==father[x])
		return x;
	father[x]=getfather(father[x]);
	return father[x];
}

void judge(int x,int y)
{
	int fx=getfather(x),fy=getfather(y);
	if (fx==fy)return;
	father[fx]=fy;
}

bool same(int x,int y)
{
	return (getfather(x)==getfather(y));
}
