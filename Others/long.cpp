/*
ID: dxmtb
PROG: Å£¹¬
TIME: 2010.11.15
STATE: Solved
MEMO: Ã¶¾Ù+¶þ·Ö
*/
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long LL;

const int MAXN=205;

int n,m,re;
LL sumx[MAXN][MAXN],sum[MAXN];
int a[MAXN][MAXN];

inline int max(int a,int b)
{
	return a>b?a:b;
}

int main()
{
	freopen("long.in","r",stdin);
	freopen("long.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
				scanf("%d",a[i]+j);
	for(int j=1;j<=m;j++)
		for(int i=1;i<=n;i++)
			sumx[j][i]=sumx[j][i-1]+a[i][j];
	for(int i=1;i<=n;i++)
		for(int j=i+1;j<=n;j++)
		{
			int x=j-i+1;
			for(int k=1;k<=m;k++)
				sum[k]=sumx[k][j]-sumx[k][i-1]+sum[k-1];
		/*	for(int k=1;k<=m;k++)
				for(int p=0;p<k;p++)
					if (sum[k]-sum[p]>0)
						if ((k-p)*x>re)
						{
							printf("%d %d %d %d\n",i,j,p+1,k);
							re=(k-p)*x;
						}*/
			vector<LL> v1,v2;
			v1.push_back(0);v2.push_back(0);
			for(int k=1;k<=m;k++)
			{
				int 
				j=upper_bound(v1.begin(),v1.end(),-sum[k])-
					v1.begin();
				if (j!=v1.size())
				{
					int tmp=x*(k-v2[j]);
					if (tmp>re)
						re=tmp;
				}
				if (-sum[k]>v1.back())
				{
					v1.push_back(-sum[k]);
					v2.push_back(k);
				}
			}
		}
	printf("%d\n",re);
	return 0;
}