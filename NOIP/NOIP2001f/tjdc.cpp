/*
ID: dxmtb
PROG: NOIP2001 统计单词个数
TIME: 2010.5.4
STATE: Solved
MEMO: dp
*/
#include <cstdio>
#include <string>
#include <iostream>
using namespace std;

const int MAXN=201,MAXK=45;

int n,m,s;
string str;
string word[7];
int d[MAXN+1][MAXK+1];
bool can[MAXN];
int L[MAXN];
int W[MAXN][MAXN];

int w(int i,int j)
{
	if (W[i][j]!=-1)
		return W[i][j];
	W[i][j]=0;
	for(int k=i;k<=j;k++)
		if (can[k]&&k+L[k]-1<=j)
			W[i][j]+=1;
	return W[i][j];
}

void init()
{
	memset(W,-1,sizeof(W));
	memset(d,0,sizeof(d));
	memset(L,0,sizeof(L));
	memset(can,false,sizeof(can));
	str="";
	for(int i=0;i<6;i++)
		word[i]="";
	n=0;
	cin>>n>>m;
	string temp;
	for(int i=0;i<n;i++)
	{
		cin>>temp;
		str+=temp;
	}
	n=n*20;
	cin>>s;
	for(int i=0;i<s;i++)
		cin>>word[i];
}

void dp()
{
	for(int i=0;i<s;i++)
	{
		size_t j;
		j=str.find(word[i]);
		int len=word[i].length();
		while (j!=str.npos)
		{ 
			if (!can[j+1])
			{
				can[j+1]=true;
				L[j+1]=len;
			}
			else if(len<L[j+1])
				L[j+1]=len;
			j=str.find(word[i],j+1);
		}
	}
	for(int j=1;j<=m;j++)
		for(int i=1;i<=n;i++)
			for(int k=max(j-1,0);k<i;k++)
				d[i][j]=max(d[i][j],d[k][j-1]+w(k+1,i));	
}

void print()
{
	cout<<d[n][m]<<endl;
}

void doit()
{
	init();
	dp();
	print();
}

int main() 
{
	freopen("tjdcgs.in","r",stdin);
	freopen("tjdcgs.out","w",stdout);
	int ti;
	scanf("%d",&ti);
	for(int i=0;i<ti;i++)
		doit();
	return 0;
}

