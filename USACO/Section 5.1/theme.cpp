/*
ID: dxmtb1
PROG: theme
LANG: C++
*/
#include <cstdio>
#include <cassert>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN=5005;

int r[MAXN];
int ax[MAXN],ay[MAXN],sa[MAXN];
int sum[MAXN];

bool cmp(int *r,int a,int b,int j)
{
	return r[a]==r[b] && r[a+j]==r[b+j];
}

void da(int n,int m)
{
	int *x=ax,*y=ay;
	memset(sum,0,sizeof(sum));
	for(int i=0;i<n;i++)
	{
		sum[x[i]=r[i]]++;
		assert(x[i]<m);
	}
	for(int i=1;i<m;i++)
		sum[i]+=sum[i-1];
	for(int i=n-1;i>=0;i--)
		sa[--sum[x[i]]]=i;
	for(int p=1,j=1;p<n;j*=2,m=p)
	{
		p=0;
		for(int i=n-j;i<n;i++)
			y[p++]=i;
		for(int i=0;i<n;i++)
			if (sa[i]-j>=0)
				y[p++]=sa[i]-j;
		memset(sum,0,sizeof(sum));
		for(int i=0;i<n;i++)
			sum[x[i]]++;
		for(int i=1;i<m;i++)
			sum[i]+=sum[i-1];
		for(int i=n-1;i>=0;i--)
			sa[--sum[x[y[i]]]]=y[i];
		p=1;
		y[sa[0]]=0;
		for(int i=1;i<n;i++)
			if (cmp(x,sa[i-1],sa[i],j)) y[sa[i]]=p-1;
			else y[sa[i]]=p++;
		swap(x,y);
	}
}

int N;
int height[MAXN];
int rank[MAXN];
void calheight()
{
	for(int i=1;i<=N;i++)
		rank[sa[i]]=i;
	for(int i=0,k=0;i<N;i++)
	{
		if (k>0)
			k--;
		while(r[i+k]==r[sa[rank[i]-1]+k])
			k++;
		height[rank[i]]=k;
	}
}

bool check(int mid)
{
	for(int i=2,j=1;i<=N+1;i++)
		if (height[i]>=mid) j++;
		else
		{
			int l=N,r=0;
			for(int k=i-j;k<i;k++)
			{
				if (sa[k]>r)
					r=sa[k];
				if (sa[k]<l)
					l=sa[k];
			}
			if (r-l>mid)
				return true;
			j=1;
		}
	return false;
}

void solve()
{
	int l=1,r=N;
	while(l+1<r)
	{
		int mid=(l+r)/2;
		if (check(mid)) l=mid;
		else r=mid-1;
	}
	int ans;
	if (l==r || !check(r)) ans=l;
	else ans=r;
	if (ans<4) printf("0\n");
	else printf("%d\n",ans+1);
}

int main()
{
	freopen("theme.in","r",stdin);
	freopen("theme.out","w",stdout);
	scanf("%d",&N);
	for(int i=0;i<N;i++)
		scanf("%d",r+i);
	for(int i=0;i<N-1;i++)
		r[i]=r[i+1]-r[i];
	N--;
	r[N]=0;
	int m=200;
	for(int i=0;i<N;i++)
		if (r[i]<m)
			m=r[i];
	m--;
	for(int i=0;i<N;i++)
		r[i]-=m;
	da(N+1,199);
	calheight();
	solve();
	return 0;
}
