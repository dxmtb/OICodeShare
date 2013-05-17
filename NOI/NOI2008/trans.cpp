/*
 * Problem: NOI2008 奥运物流
 * Time: 2011.06.13
 * Author: dxmtb
 * State: Solved
 * Memo: dp
*/
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

const int MAXN=65;

int N,M;
int S[MAXN];
double C[MAXN];

vector<int> son[MAXN];
double Pow[MAXN];
double d[MAXN][MAXN][MAXN];
bool calcu[MAXN][MAXN];
double f[MAXN][MAXN];
bool in[MAXN];
void dp(int i,int j)
{
	if (calcu[i][j]) 
		return ;
	calcu[i][j]=true;
	if (son[i].size()==0)
	{
		d[i][j][0]=Pow[j]*C[i];
		for(int k=1;k<=M;k++)
			d[i][j][k]=Pow[1]*C[i];
		return ;
	}
	for(int p=0;p<(int)son[i].size();p++)
		dp(son[i][p],j+1);
	memset(f,0,sizeof(f));
	for(int p=0;p<(int)son[i].size();p++)
	{
		for(int v=0;v<=M;v++)
			for(int q=0;q<=v;q++)
			{
				double nf=f[p][v-q]+d[son[i][p]][j+1][q];
				if (f[p+1][v]<nf)
					f[p+1][v]=nf;
			}
	}
	for(int v=0;v<=M;v++)
		d[i][j][v]=f[son[i].size()][v]+Pow[j]*C[i];
	if (!in[i])
	{
		for(int p=0;p<(int)son[i].size();p++)
			dp(son[i][p],1+1);
		memset(f,0,sizeof(f));
		for(int p=0;p<(int)son[i].size();p++)
		{
			for(int v=0;v<=M-1;v++)
				for(int q=0;q<=v;q++)
				{
					double nf=f[p][v-q]+d[son[i][p]][1+1][q];
					if (f[p+1][v]<nf)
						f[p+1][v]=nf;
				}
		}
		for(int v=1;v<=M;v++)
		{
			double nd=f[son[i].size()][v-1]+Pow[1]*C[i];
			if (nd>d[i][j][v])
				d[i][j][v]=nd;
		}
	}
}

int circle[MAXN],size;
void findcircle()
{
	int u=1;
	size=0;
	do
	{
		circle[size++]=u;
		u=S[u];
	}while(u!=1);
}

double re;
int depth[MAXN];
void getans()
{
	memset(in,false,sizeof(in));
	for(int i=0;i<size;i++)
		in[circle[i]]=true;
	for(int u=1;u<=N;u++)
		son[u].clear();
	for(int u=1;u<=N;u++)
		if (!in[u])
			son[S[u]].push_back(u);
	memset(d,0,sizeof(d));
	memset(calcu,false,sizeof(calcu));
	depth[1]=0;
	for(int i=size-1;i>0;i--)
		depth[circle[i]]=size-i;
	for(int i=0;i<size;i++)
	{
		int u=circle[i];
		dp(u,depth[u]);
	}
	memset(f,0,sizeof(f));
	for(int i=0;i<size;i++)
	{
		int u=circle[i];
		for(int j=0;j<=M;j++)
			for(int k=0;k<=j;k++)
			{
				double nf=f[i][j-k]+d[u][depth[u]][k];
				if (nf>f[i+1][j])
					f[i+1][j]=nf;
			}
	}
	double ans=f[size][M]/(1.0-Pow[size]);
	if (ans>re)
		re=ans;
}

int csize;
void solve()
{
	findcircle();
	getans();
	csize=size;
	M--;
	for(int i=1;i<csize;i++)
	{
		int u=circle[i];
		int t=S[u];
		S[u]=1;
		size=i+1;
		getans();
		S[u]=t;
	}
}

double K;
int main()
{
	freopen("trans.in","r",stdin);
	freopen("trans.out","w",stdout);
	scanf("%d%d%lf",&N,&M,&K);
	for(int i=1;i<=N;i++)
		scanf("%d",S+i);
	for(int i=1;i<=N;i++)
		scanf("%lf",C+i);
	Pow[0]=1;
	for(int i=1;i<=N;i++)
		Pow[i]=Pow[i-1]*K;
	solve();
	printf("%.2lf\n",re);
	return 0;
}
