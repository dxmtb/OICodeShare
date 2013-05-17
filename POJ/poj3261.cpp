/*
 * Problem: poj3261 Milk Patterns
 * Time: 2011.04.10
 * Author: dxmtb
 * State: Solved
 * Memo: 后缀数组+二分答案
*/
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAXN=20005;

int str[MAXN];
int *x,*y;
int ax[MAXN],ay[MAXN];
int sa[MAXN];

inline bool cmp(const int &a,const int &b)
{
	return x[a]<x[b];
}

inline bool same(int *r,int a,int b,int j)
{
	return r[a]==r[b] && r[a+j]==r[b+j];
}

void da(int N)
{
	x=ax,y=ay;
	for(int i=0;i<N;i++)
		x[i]=str[i],sa[i]=i;
	stable_sort(sa,sa+N,cmp);
	for(int j=1,p=1;p<N;j*=2)
	{
		p=0;
		for(int i=N-j;i<N;i++)
			y[p++]=i;
		for(int i=0;i<N;i++)
			if (sa[i]-j>=0)
				y[p++]=sa[i]-j;
		memcpy(sa,y,sizeof(sa));
		stable_sort(sa,sa+N,cmp);
		y[sa[0]]=0;
		p=1;
		for(int i=1;i<N;i++)
			if (same(x,sa[i-1],sa[i],j)) y[sa[i]]=p-1;
			else y[sa[i]]=p++;
		int *t=x;
		x=y;y=t;
	}
}

int N,K;

int rank[MAXN],height[MAXN];
void calheight()
{
	for(int i=1;i<=N;i++)
		rank[sa[i]]=i;
	for(int i=0,k=0;i<N;i++)
	{
		int j=sa[rank[i]-1];
		if (k) k--;
		while(str[i+k]==str[j+k])
			k++;
		height[rank[i]]=k;
	}	
}

bool judge(int mid)
{
	for(int i=2,j=1;i<=N;i++)
	{
		if (height[i]>=mid) j++;
		else j=1;
		if (j>=K)
			return true;
	}
	return false;
}

int main()
{
	freopen("poj3261.in","r",stdin);
	scanf("%d%d",&N,&K);
	for(int i=0;i<N;i++)
	{
		scanf("%d",str+i);
		str[i]++;
	}
	da(N+1);
	calheight();
	int l=0,r=N;
	while(l+1<r)
	{
		int mid=(l+r)/2;
		if (judge(mid))
			l=mid;
		else 
			r=mid-1;
	}
	if (l==r) printf("%d\n",l);
	else if (judge(r)) printf("%d\n",r);
	else printf("%d\n",l);
	return 0;
}
