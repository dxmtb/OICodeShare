/*
 * Problem: NOI2003 智破连环阵
 * Time: 2011.06.13
 * Author: dxmtb
 * State: Solved
 * Memo: 搜索
*/
#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN=105;
const int oo=~0u>>2;
const int d1=RAND_MAX/2,d2=RAND_MAX*(5.0/6);
int MAXT=10000000;

inline int getdis(int x,int y)
{
	return x*x+y*y;
}

int N,M,K,re;
int X[MAXN],Y[MAXN],U[MAXN],V[MAXN];
bool used[MAXN];
vector<int> can[MAXN],rcan[MAXN],only[MAXN];

vector<int> ans,way;
int TOT;
void dfs(int dep,int right)
{
	if (dep+1>re)
		return ;
	TOT++;
	if (TOT>MAXT)
		return ;
	int nr[MAXN];
	vector<pair<int,int> > v;
	for(int i=0;i<N;i++)
		if (!used[i])
		{
			nr[i]=right;
			for(int j=0;j<(int)can[i].size();j++)
				if (can[i][j]>nr[i])
				{
					if (can[i][j]==nr[i]+1)
						nr[i]++;
					else
						break;
				}
			if (nr[i]!=right)
			{
				if (nr[i]==M-1)
				{
					if (dep+1<re)
					{
						re=dep+1;
						cerr<<"get "<<re<<endl;
						ans=way;
						ans.push_back(i);
					}
					return ;
				}
				for(int j=0;j<(int)only[i].size();j++)
					if (only[i][j]>nr[i])
					{
						nr[i]=right;
						break;
					}
				if (nr[i]!=right)
					v.push_back(make_pair(nr[i],i));
			}
		}
	sort(v.begin(),v.end(),greater<pair<int,int> >());
	for(int j=0;j<(int)v.size() && TOT<MAXT;j++)
	{
		int i=v[j].second;
		used[i]=true;
		way.push_back(i);
		dfs(dep+1,nr[i]);	
		used[i]=false;
		way.pop_back();
	}
}

int main()
{
	freopen("zplhz.in","r",stdin);
	freopen("zplhz.out","w",stdout);
	scanf("%d%d%d",&M,&N,&K);
	for(int i=0;i<M;i++)
		scanf("%d%d",X+i,Y+i);
	for(int i=0;i<N;i++)
		scanf("%d%d",U+i,V+i);
	for(int i=0;i<N;i++)
		for(int j=0;j<M;j++)
			if (getdis(X[j]-U[i],Y[j]-V[i])<=K*K)
			{
				can[i].push_back(j);
				rcan[j].push_back(i);
			}
	for(int i=0;i<M;i++)
		if (rcan[i].size()==1)
			only[rcan[i][0]].push_back(i);
	re=N+1;
	MAXT/=N;
	dfs(0,-1);
	printf("%d\n",re);
	if (re==N+1)
		cerr<<"No ans"<<endl;
	for(int i=0;i<re;i++)
	{
		if (i) printf(" ");
		printf("%d",ans[i]+1);
	}
	printf("\n");
	return 0;
}
