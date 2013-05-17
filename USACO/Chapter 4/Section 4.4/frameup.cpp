/*
ID: dxmtb1
PROG: frameup
LANG: C++
*/
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
#include <set>
using namespace std;

const int MAXN=35,MAXM=28;

int g[MAXM][MAXM];

inline void addedge(int u,int v)
{
	g[u][v]=true;
}

char ch[MAXM]={'.'};
char str[MAXN][MAXN];
int a[MAXN][MAXN];
int up[MAXM],down[MAXM],left[MAXM],right[MAXM];
bool num[255];
set<string> s;
int N,M,tot;

char buf[MAXM];
bool used[MAXM];
void dfs(int dep)
{
	if (dep==tot)
	{
		s.insert(buf);
		return ;
	}
	for(int u=1;u<=tot;u++)
		if (!used[u])
		{
			for(int v=1;v<=tot;v++)
				if (!used[v] && g[v][u])
					goto OUT;
			buf[dep]=ch[u];
			used[u]=true;
			dfs(dep+1);
			used[u]=false;
OUT:;
		}
}

int main()
{
	freopen("frameup.in","r",stdin);
	freopen("frameup.out","w",stdout);
	scanf("%d%d",&N,&M);
	for(int i=0;i<N;i++)
		scanf("%s",str[i]);
	for(int i=0;i<N;i++)
		for(int j=0;j<M;j++)
			if (str[i][j]!='.' && !num[(int)str[i][j]])
			{
				++tot;
				num[(int)str[i][j]]=tot;
				ch[tot]=str[i][j];
			}
	for(int i=1;i<=tot;i++)
		up[i]=left[i]=100;
	for(int i=0;i<N;i++)
		for(int j=0;j<M;j++)
		{
			a[i][j]=0;
			for(int k=1;k<=tot;k++)
				if (str[i][j]==ch[k])
				{
					a[i][j]=k;
					if (i<up[a[i][j]])
						up[a[i][j]]=i;
					if (i>down[a[i][j]])
						down[a[i][j]]=i;
					if (j<left[a[i][j]])
						left[a[i][j]]=j;
					if (j>right[a[i][j]])
						right[a[i][j]]=j;
					break;
				}
		}
	for(int i=1;i<=tot;i++)
	{
		int u=up[i],d=down[i],l=left[i],r=right[i];
		for(int x=u;x<=d;x++)
		{
			if (i!=a[x][l])
				addedge(i,a[x][l]);
			if (i!=a[x][r])
				addedge(i,a[x][r]);
		}
		for(int y=l+1;y<r;y++)
		{
			if (i!=a[u][y])
				addedge(i,a[u][y]);
			if (i!=a[d][y])
				addedge(i,a[d][y]);
		}
	}
	dfs(0);
	for(set<string>::iterator it=s.begin();it!=s.end();it++)
		printf("%s\n",it->c_str());
	return 0;
}
