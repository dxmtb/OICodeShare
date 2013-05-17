/*
  ID: dxmtb
  PROG: trouble
  TIME: 2010.6.29
  STATE: Solved
  MEMO: SRC
*/
#include <iostream>
using namespace std;

const int MAXN=20;
const int a[MAXN+1]={1,2,4,8,16,32,64,128,256,512,1024,2048,4096,8192,16384,32768,65536,131072,262144,524288,1048576};
long long b[MAXN+1]={1};

int n,m;
bool g[MAXN+1][MAXN+1];
long long d[(1<<MAXN)]={1},re;
int z[(1<<MAXN)],s[MAXN];

int main() 
{
	freopen("trouble.in","r",stdin);
	freopen("trouble.out","w",stdout);
	cin>>n>>m;
	for(int i=1;i<=m;i++)
	{
		cin>>s[i];
		s[i]+=s[i-1];
	}
	for(int i=1;i<=MAXN;i++)
		b[i]=b[i-1]*i;
	for(int i=1,t1,t2;i<=n;i++)
	{
		cin>>t1;
		while(t1--)
		{
			cin>>t2;
			for(int j=s[t2-1]+1;j<=s[t2];j++)
				g[j][i]=true;
		}
	}
	for(int i=1;i<a[n];i++)
	{
		z[i]=z[i>>1]+(i&1);
		for(int t=i,j=0;t;t>>=1,j++)
			if(t&1&&g[z[i]][j+1])
				d[i]+=d[i^a[j]];
		if (z[i]==s[m])
			re+=d[i];
	}
	for(int i=1;i<=m;i++)
		re/=b[s[i]-s[i-1]];
	cout<<re;
	return 0;
}
