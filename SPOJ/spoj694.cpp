/*
ID: dxmtb
PROG: Spoj694 Distinct Substrings
TIME: 2011.03.06
STATE: Solved
MEMO: 后缀数组
*/
#include <cstdio>
#include <cstring>

const int MAXN=1005,MAXM=300;

bool cmp(int *r,int a,int b,int l)
{
	return (r[a]==r[b]&&r[a+l]==r[b+l]);
}

int ta[MAXN],tb[MAXN],sum[MAXN],sa[MAXN];
void da(int *r,int *sa,int N,int M)
{
	int *x=ta,*y=tb,*t,i,j,p;
	memset(sum,0,sizeof(sum));
	for(i=0;i<N;i++)
		sum[x[i]=r[i]]++;
	for(i=1;i<M;i++)
		sum[i]+=sum[i-1];
	for(i=N-1;i>=0;i--)
		sa[--sum[r[i]]]=i;
	for(j=1,p=1;p<N;j*=2,M=p)
	{
		for(p=0,i=N-j;i<N;i++)
			y[p++]=i;
		for(i=0;i<N;i++)
			if (sa[i]>=j)
				y[p++]=sa[i]-j;
		memset(sum,0,sizeof(sum));
		for(i=0;i<N;i++)
			sum[x[i]]++;
		for(i=1;i<M;i++)
			sum[i]+=sum[i-1];
		for(i=N-1;i>=0;i--)
			sa[--sum[x[y[i]]]]=y[i];
		t=x;x=y;y=t;
		x[sa[0]]=0;
		for(i=1,p=1;i<N;i++)
		{
			if (cmp(y,sa[i-1],sa[i],j)) x[sa[i]]=p-1;
			else x[sa[i]]=p++;
		}
	}
}


int height[MAXN],rank[MAXN];
void calheight(int *r,int *sa,int N)
{
	for(int i=1;i<=N;i++)
		rank[sa[i]]=i;
	for(int i=0,k=0;i<N;i++)
	{
		if (k>0) 
			k--;
		int j=sa[rank[i]-1];
		while(r[i+k]==r[j+k])
			k++;
		height[rank[i]]=k;
	}
}

int r[MAXN];
char str[MAXN];
int main()
{
	int T,m,n;
	scanf("%d",&T);
	while(T--)
	{
		scanf("%s",str);
		n=strlen(str);
		for(int i=0;i<=n;i++)
			r[i]=str[i];
		m=0;
		for(int i=0;i<n;i++)
			if (r[i]>m)
				m=r[i];
		da(r,sa,n+1,m+1);
		calheight(r,sa,n);
		int ans=n*(n+1)/2;
		for(int i=1;i<=n;i++)
			ans-=height[i];
		printf("%d\n",ans);
	}
	return 0;
}
