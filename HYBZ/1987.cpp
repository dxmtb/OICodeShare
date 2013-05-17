/*
 * Problem: Zju2672 Fibonacci Subsequence
 * Time: 2011.04.08
 * Author: dxmtb
 * State: Solved
 * Memo: dp+¶þ·Ö²éÕÒ
*/
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN=3005;

int N;
int d[MAXN][MAXN];
short K[MAXN][MAXN];
int a[MAXN];
pair<int,pair<int,int> > v2[MAXN];
int size1,size2;

inline int find(int x)
{
	int l=0,r=size2-1;
	while(l<r)
	{
		int mid=(l+r)>>1;
		if (v2[mid].first==x)
			return mid;
		if (v2[mid].first<x)
			l=mid+1;
		else
			r=mid-1;
	}
	if (v2[l].first==x) return l;
	return size2;
}

int main()
{
	freopen("1987.in","r",stdin);
	freopen("1987.out","w",stdout);
	scanf("%d",&N);
	for(int i=1;i<=N;i++)
		scanf("%d",a+i);
	if (N==1||N==2)
	{
		printf("%d",a[1]);
		for(int i=2;i<=N;i++)
			printf(" %d",a[i]);
		printf("\n");
	}
	for(int j=N;j>=1;j--)
	{
		vector<pair<int,pair<int,int> > > v;
		for(int k=j+1;k<=N;k++)
			v.push_back(make_pair(a[k],make_pair(d[j][k],k)));
		sort(v.begin(),v.end());
		size1=v.size(),size2=0;
		for(int k=0;k<size1;k++)
			if (k==size1-1||v[k].first!=v[k+1].first)
				v2[size2++]=v[k];
		for(int i=j-1;i>=1;i--)
		{
			d[i][j]=2;
			int it=find(a[i]+a[j]);
			if (it!=size2)
			{
				d[i][j]=v2[it].second.first+1;
				K[i][j]=v2[it].second.second;
			}
			/*
			for(int k=j+1;k<=N;k++)
				if (a[i]+a[j]==a[k])
					if (d[j][k]+1>d[i][j])
						d[i][j]=d[j][k]+1,K[i][j]=k;*/
		}
	}
	int re=0,ri=0,rj=0;
	for(int i=1;i<=N;i++)
		for(int j=i+1;j<=N;j++)
			if (d[i][j]>re)
				re=d[i][j],ri=i,rj=j;
	printf("%d\n",re);
	printf("%d %d",a[ri],a[rj]);
	for(int i=ri,j=rj,k=re-2;k>=1;k--)
	{
		int t=j;
		j=K[i][j];
		i=t;
		printf(" %d",a[j]);
	}
	printf("\n");
	return 0;
}
