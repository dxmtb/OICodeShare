/*
 * Problem: [JSOI2008]魔兽地图DotR 
 * Time: 2011.05.31
 * Author: dxmtb
 * State: Solved
 * Memo: dp
*/
#include <cstdio>
#include <cstring>
//#include <cassert>

#define assert

const int MAXN=55,MAXM=2005,MAXL=105;
const int oo=~0u>>2;

inline void Max(int &a,const int &b)
{
	if (b>a)
		a=b;
}

inline void Min(int &a,const int &b)
{
	if (b<a)
		a=b;
}

int N,M;
int L[MAXN],Vt[MAXN],V[MAXN],W[MAXN],C[MAXN],need[MAXN];
int son[MAXN][MAXN];
void dfs(int u)
{
	if (C[u]==0)
	{
		Vt[u]=V[u];
		Min(L[u],M/Vt[u]);
		return ;
	}
	L[u]=oo;
	for(int i=0;i<C[u];i++)
	{
		int v=son[u][i];
		dfs(v);
		Vt[u]+=need[v]*Vt[v];
		Min(L[u],L[v]/need[v]);
	}
	Min(L[u],M/Vt[u]);
}
int d[MAXN][MAXL][MAXM];
int f[MAXN][MAXM];
int fc[MAXN][MAXL][MAXM];
bool cal[MAXN][MAXL];
bool calcu[MAXN][MAXL];
int cnt;
void dp(int i,int j)
{
	calcu[i][j]=true;
	int *g=d[i][j];
	if (C[i]==0)
	{
		if (j>L[i])
			return ;
		//int minv=j*need[i]*V[i];
		int t=0;
		for(int k=j;k<L[i];k++,t+=W[i])
		{
			for(int p=k*V[i];p<(k+1)*V[i];p++)
			{
				assert(p<=M);
				g[p]=t;
			}
		}
		for(int k=L[i]*V[i];k<=M;k++)
			g[k]=t;
		return ;
	}
	for(int p=0;j+p<=L[i];p++)
	{
		int *tf;
		if (!cal[i][j+p])
		{
			for(int k=0;k<C[i];k++)
			{
				int v=son[i][k],t=(j+p)*need[son[i][k]];
				assert (!calcu[v][t]);
					dp(v,t);
				//else
			//		cnt++;
			}
			/*for(int t=0;t<=M;t++)
			  f[0][t]=0;*/
			int minv=0;
			for(int s=0;s<C[i];s++)
			{
				int v=son[i][s],needs=(p+j)*need[v];
				int needv=needs*Vt[v];
				minv+=needv;
				assert(minv<=M);
				for(int t=0;t<minv && t<=M;t++)
					f[s+1][t]=-oo;
				for(int t=minv;t<=M;t++)
				{
					f[s+1][t]=-oo;
					for(int q=needv;q<=t;q++)
						Max(f[s+1][t],f[s][t-q]+d[v][needs][q]);
				}
			}
			for(int k=0;k<=M;k++)
				fc[i][j+p][k]=f[C[i]][k];
			cal[i][j+p]=true;
			tf=f[C[i]];
		}
		else
		{
			tf=fc[i][j+p];
		}
		for(int k=(j+p)*Vt[i];k<=M;k++)
		{
			assert(tf[k]>=0);
			Max(g[k],tf[k]+W[i]*p);
		}
	}
}

int main()
{
	freopen("1017.in","r",stdin);
	scanf("%d%d",&N,&M);
	for(int i=1;i<=N;i++)
	{
		scanf("%d",W+i);
		char kind;
		scanf(" %c",&kind);
		if (kind=='A')
		{
			scanf("%d",C+i);
			for(int j=0;j<C[i];j++)
			{
				int x;
				scanf("%d",&x);
				scanf("%d",need+x);
				son[i][j]=x;
			}
		}
		else
		{
			assert(kind=='B');
			scanf("%d%d",V+i,L+i);
		}
	}
	for(int i=1;i<=N;i++)
		for(int j=0;j<=100;j++)
			for(int k=0;k<=M;k++)
				d[i][j][k]=-oo;
	/*
	for(int i=1;i<=N;i++)
		if (need[i]==0)
		{
			dfs(i);
			break;
		}
	vector<pair<int,int> > v;
	for(int i=1;i<=N;i++)
		v.push_back(make_pair(depth[i],i));
	sort(v.begin(),v.end(),greater<pair<int,int> >());
	for(int i=0;i<N;i++)
		for(int j=0;j<=L[v[i].second];j++)
			dp(v[i].second,j);
	printf("%d\n",d[v[N-1].second][0][M]);*/
	
	for(int i=1;i<=N;i++)
		if (need[i]==0)
		{
			dfs(i);
			dp(i,0);
			printf("%d\n",d[i][0][M]);
			break;
		}
//	printf("%d\n",cnt);
	return 0;
}
