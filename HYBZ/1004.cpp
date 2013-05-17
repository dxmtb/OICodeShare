/*
 * Problem: [HNOI2008]Cards
 * Time: 2011.04.20
 * Author: dxmtb
 * State: Solved
 * Memo: Burnside∂®¿Ì
*/
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

const int MAXN=105;

int d[MAXN][MAXN][MAXN];
int f[MAXN];
int Sr,Sb,Sg,M,MO;
vector<int> v;

int powmod(int a,int N)
{
	int ans=1;
	for(int i=0;i<N;i++)
		ans=(ans*a)%MO;
	return ans;
}

bool used[MAXN];
void find(int u,int size)
{
	while(true)
	{
		used[u]=true;
		if (used[f[u]])
		{
			v.push_back(size);
			return ;
		}
		u=f[u];size++;
	}
}

int N,re;
int sum[MAXN];
void solve()
{
	memset(used,false,sizeof(used));
	v.clear();
	for(int i=1;i<=N;i++)
		if (!used[i])
			find(i,1);
	sum[0]=0;
	for(int i=1;i<=v.size();i++)
			sum[i]=sum[i-1]+v[i-1];
	memset(d,0,sizeof(d));
	d[0][0][0]=1;
	for(int i=1;i<=v.size();i++)
		for(int a=0;a<=Sr;a++)
			for(int b=0;b<=Sb;b++)
			{
				int c=sum[i]-a-b;
				if (c>=0 && c<=Sg)
					{
					if (v[i-1]<=a)
						d[i][a][b]=d[i-1][a-v[i-1]][b];
					if (v[i-1]<=b)
						d[i][a][b]=(d[i][a][b]+d[i-1][a][b-v[i-1]])%MO;
					if (v[i-1]<=c)
						d[i][a][b]=(d[i][a][b]+d[i-1][a][b])%MO;
					}
			}
	re=(re+d[v.size()][Sr][Sb])%MO;	
}

int main()
{
	freopen("1004.in","r",stdin);
	scanf("%d%d%d%d%d",&Sr,&Sb,&Sg,&M,&MO);
	N=Sr+Sb+Sg;
	for(int k=0;k<M;k++)
	{
		for(int i=1;i<=N;i++)
			scanf("%d",f+i);
		solve();
	}
	for(int i=1;i<=N;i++)
		f[i]=i;
	solve();
	re=(re*powmod(M+1,MO-2))%MO;
	printf("%d\n",re);
	return 0;
}
