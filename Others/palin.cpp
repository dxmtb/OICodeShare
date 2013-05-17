#include <cstdio>
#include <iostream>
#include <assert.h>
using namespace std;
const int MAXN=5005;
const int oo=int(2e9);

char str1[MAXN],str2[MAXN];
int N;
int d[MAXN][MAXN];

int main()
{
	freopen("palin.in","r",stdin);
	freopen("palin.out","w",stdout);
	cin>>N;
	cin>>str1+1;
	for(int i=1;i<=N;i++)
		str2[i]=str1[N-i+1];
	for(int i=0;i<=N;i++)
		for(int j=0;j<=N;j++)
			d[i][j]=oo;
	d[0][0]=0;
	for(int i=0;i<=N;i++)
		for(int j=0;j<=N;j++)
		{
			if (i&&j&&str1[i]==str2[j]) d[i][j]=d[i-1][j-1];
			if (i) d[i][j]=min(d[i][j],d[i-1][j]+1);
			if (j) d[i][j]=min(d[i][j],d[i][j-1]+1);
		}
	int re=N;
	for(int i=1;i+1<=N;i++)
		if (d[i][N-i]<re)
			re=d[i][N-i];
	for(int i=1;i+2<=N;i++)
		if (d[i][N-i-1]<re)
			re=d[i][N-i-1];
	cout<<re<<endl;
	return 0;
}
