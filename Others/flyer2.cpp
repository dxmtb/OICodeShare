/*
ID: dxmtb
PROG: 搭配飞行员
TIME: 2010.4.10
STATE: Solved
MEMO: 匈牙利算法
*/
#include <cstdio>
#include <cstring>
using namespace std;

const int MAXN=100;

int n,n1,match=0,adj[MAXN+1][MAXN],mat[MAXN+1];
bool used[MAXN+1];

FILE *fin=fopen("flyer.in","r");
FILE *fout=fopen("flyer.out","w");

void init()
{
	fscanf(fin,"%d%d",&n,&n1);
	int a,b;
	while(fscanf(fin,"%d%d",&a,&b)!=EOF)
		adj[a][++adj[a][0]]=b;
}

bool find(int x)
{
	for(int i=1;i<=adj[x][0];i++)
	{
		int j=adj[x][i];
		if (!used[j])
		{
			used[j]=true;
			if (mat[j]==0||find(mat[j]))
			{
				mat[j]=x;
				return true;
			}
		}
	}
	return false;
}

int main() 
{
	init();
	for(int i=1;i<=n;i++)
		{
			memset(used,0,sizeof(used));
			if (find(i))
				match++;
		}
	fprintf(fout,"%d\n",match);
    return 0;
}
