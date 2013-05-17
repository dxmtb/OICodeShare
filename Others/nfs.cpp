/*
ID: dxmtb
PROG: 飙车
TIME: 2010.11.8
STATE: Solved
MEMO: dp
*/
#include <iostream>
#include <cstdio>
#include <string>
using namespace std;

const int MAXN=105;

string str[MAXN];
int L,K;
int d[MAXN][MAXN],w[MAXN][MAXN];

int main()
{
	freopen("nfs.in","r",stdin);
	freopen("nfs.out","w",stdout);
	cin>>L>>K;
	for(int i=L;i;i--)
		cin>>str[i];
	for(int i=0;i<K;i++)
		d[0][i]=0;
	for(int i=1;i<=L/2;i++)
		for(int j=0;j<K;j++)
			w[i][j]=(str[i+i][j]=='1');
	for(int i=1;i<=L;i++)
		for(int j=0;j<K;j++)
		{
			d[i][j]=d[i-1][j]+w[i][j]+((i+i-1>L)?0:(str[i+i-1][j]=='1'));
			if (j>=1&&d[i][j]>d[i-1][j-1]+w[i][j])
				d[i][j]=d[i-1][j-1]+w[i][j];
			if (j+1<K&&d[i][j]>d[i-1][j+1]+w[i][j])
				d[i][j]=d[i-1][j+1]+w[i][j];
		}
	int re=d[L][0];
	for(int j=1;j<K;j++)
		if (re>d[L][j])
			re=d[L][j];
	printf("%d\n",re);
	return 0;
}
