/*
ID: dxmtb
PROG: HAOI2010 计数
TIME: 2011.03.16
STATE: Solved
MEMO: 排列组合
*/
#include <cstdio>
#include <cstring>
#include <cmath>

typedef long long s64;

const int MAXN=55;

char str[MAXN];

int sum[MAXN],tot[MAXN][10];
int factor[MAXN][MAXN];

void getfact(int n)
{
	int m=n;
	for(int i=2;i<=m;i++)
	{
		while (n%i==0)
		{
			n/=i;
			factor[m][i]++;
		}
		factor[m][i]+=factor[m-1][i];
	}
}

s64 frac(int n,int t[10])
{
	int fa[MAXN];
	memset(fa,0,sizeof(fa));
	for(int j=2;j<=n;j++)
		fa[j]+=factor[n][j];
	for(int i=0;i<10;i++)
		if (t[i]>=2)
		for(int j=2;j<=t[i];j++)
			fa[j]-=factor[t[i]][j];
	s64 ans=1;
	for(int j=2;j<=n;j++)
		ans*=pow(j,fa[j]);
	return ans;
}

int N;
s64 getans(int dep)
{
	if (sum[dep]==1)
	{
		if (str[dep]=='0') return getans(dep+1);
		else return (N-dep);
	}
	s64 ans=0;
	for(int i=0;i<str[dep]-'0';i++)
	if (tot[dep][i])
	{
		tot[dep][i]--;
		ans+=frac(N-dep,tot[dep]);
		tot[dep][i]++;
	}
	ans+=getans(dep+1);
	return ans;
}

int main()
{
	freopen("perm.in","r",stdin);
	freopen("perm.out","w",stdout);
	scanf("%s",str);
	N=strlen(str)-1;
	for(int i=N;i>=0;i--)
	{
		sum[i]=sum[i+1]+(str[i]!='0');
		for(int j=0;j<=9;j++)
			tot[i][j]=tot[i+1][j];
		tot[i][str[i]-'0']++;
	}
	factor[2][2]=1;
	for(int i=3;i<=N;i++)
		getfact(i);
	printf("%lld\n",getans(0));
	return 0;
}
