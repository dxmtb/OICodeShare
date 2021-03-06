/*
 * Problem: [Balkan2007]Cipher
 * Time: 2011.04.06
 * Author: dxmtb
 * State: Solved
 * Memo: 字符串hash
*/
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;

const int MAXN=2005;
const int Seed=131;
const int MO=1741013,MO2=174101;

char str[MAXN][MAXN];
int th[MAXN];
int th2[MAXN];
int N,M,X,Y;
vector<pair<int,pair<int,int> > > v[MO];

int main()
{
	scanf("%d%d\n",&N,&M);
	for(int i=0;i<N;i++)
		fgets(str[i],sizeof(str[0]),stdin);
	scanf("%d%d",&X,&Y);
	for(int i=0;i<M;i++)
		for(int j=0;j<X-1;j++)
			th[i]=(th[i]*Seed+str[j][i])%MO;
	for(int i=0;i<M;i++)
		for(int j=0;j<X-1;j++)
			th2[i]=(th2[i]*Seed+str[j][i])%MO2;
	int SeedMulX=1,SeedMulY=1;
	int SeedMulX2=1,SeedMulY2=1;
	for(int i=0;i<X-1;i++)
		SeedMulX=SeedMulX*Seed%MO;
	for(int i=0;i<Y-1;i++)
		SeedMulY=SeedMulY*Seed%MO;
	for(int i=0;i<X-1;i++)
		SeedMulX2=SeedMulX2*Seed%MO2;
	for(int i=0;i<Y-1;i++)
		SeedMulY2=SeedMulY2*Seed%MO2;
	for(int i=X-1;i<N;i++)
	{
		for(int j=0;j<M;j++)
		{
			th[j]=(th[j]*Seed+str[i][j])%MO;
			th2[j]=(th2[j]*Seed+str[i][j])%MO2;
		}
		int nh=0,nh2=0;
		for(int j=0;j<Y-1;j++)
		{
			nh=(nh*Seed+th[j])%MO;
			nh2=(nh2*Seed+th2[j])%MO2;
		}
		for(int j=Y-1;j<M;j++)
		{
			nh=(nh*Seed+th[j])%MO;
			nh2=(nh2*Seed+th2[j])%MO2;
			v[nh].push_back(make_pair(nh2,make_pair(i,j)));
			nh=((long long)nh-(long long)th[j-Y+1]*SeedMulY)%MO;
			nh2=((long long)nh2-(long long)th2[j-Y+1]*SeedMulY2)%MO2;
			if (nh<0)
				nh+=MO;
			if (nh2<0)
				nh2+=MO2;
		}
		for(int j=0;j<M;j++)
		{
			th[j]=((long long)th[j]-(long long)str[i-X+1][j]*SeedMulX)%MO;
			th2[j]=((long long)th2[j]-(long long)str[i-X+1][j]*SeedMulX2)%MO2;
			if (th[j]<0)
				th[j]+=MO;
			if (th2[j]<0)
				th2[j]+=MO2;
		}
	}
	int re=0,ri,rj;
	for(int i=0;i<MO;i++)
		if (int(v[i].size())>re)
		{
			sort(v[i].begin(),v[i].end());
			for(int j=0,k=0;j<(int)v[i].size();j++)
			{
				if (j==0 || v[i][j].first!=v[i][j-1].first)
					k=1;
				else k++;
				if (k>re)
					ri=i,rj=j-k+1,re=k;
			}
		}
	printf("%d %d\n",X,Y);
	for(int x=v[ri][rj].second.first,i=x-X+1;i<=x;i++)
	{
		for(int y=v[ri][rj].second.second,j=y-Y+1;j<=y;j++)
			printf("%c",str[i][j]);
		printf("\n");
	}
	printf("%d\n",re);
	for(int i=rj;i<rj+re;i++)
		printf("%d %d\n",v[ri][i].second.first-X+2,v[ri][i].second.second-Y+2);
	return 0;
}
