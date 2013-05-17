/*
ID: dxmtb
PROG: [CQOI2009]中位数图
TIME: 2011.03.30
STATE: Solved
MEMO: 区间和
*/
#include <cstdio>
#include <iostream>
using namespace std;

const int MAXN=100005;

int N,B,pos;
int a[MAXN],b[2][MAXN];

int main()
{
	freopen("1303.in","r",stdin);
	scanf("%d%d",&N,&B);
	for(int i=1;i<=N;i++)
	{
		scanf("%d",a+i);
		if (a[i]==B)
			pos=i;
	}
	b[0][0]=1;
	int t1=0,t2=0;
	for(int i=1;i<pos;i++)
	{
		if (a[i]<B) t1++;
		else t2++;
		if (t1<=t2)
			b[0][t2-t1]++;
		else 
			b[1][t1-t2]++;
	}
	long long re=0;
	for(int i=pos;i<=N;i++)
	{
		if (i!=pos)
		{
			if (a[i]<B) t1++;
			else t2++;	
		}
		if (t1<=t2)
			re+=b[0][t2-t1];
		else
			re+=b[1][t1-t2];
	}
	cout<<re<<endl;
	return 0;
}	
