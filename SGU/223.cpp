/*
ID: dxmtb
PROG: sgu 223.Little Kings 
TIME: 2010.4.17
STATE: Solved
MEMO: ×´Ì¬Ñ¹Ëõ¶¯Ì¬¹æ»®
*/
#include <iostream>
#include <cstring>
using namespace std;

const int MAXN=11,MAXS=(1<<MAXN)-1;

long long n,pn,d[2][MAXS+1][(MAXN/2)*(MAXN/2)],c[MAXS],re=0;
unsigned s[MAXS];

void dfs(int dep,unsigned state,bool is,int one)
{
	if (dep==n)
		s[++s[0]]=state,c[s[0]]=one;
	else
	{
		state*=2;
		dfs(dep+1,state,false,one);
		state+=1;
		if (is==false)dfs(dep+1,state,true,one+1);
	}
}

int main() 
{
	cin>>n>>pn;
	if(pn>((n+1)/2)*((n+1)/2)){cout<<0<<endl;return 0;}
	dfs(0,0u,false,0);
	d[0][1][0]=1;
	for(int i=1;i<=n;i++)
	{
		for(unsigned j=1;j<=s[0];j++)
			for(int k=c[j];k<=pn;k++)
				for(unsigned p=1;p<=s[0];p++)
					if (!(s[j]&s[p])&&!((s[j]<<1)&s[p])&&!((s[j]>>1)&s[p]))
						d[i&1][j][k]+=d[1-i&1][p][k-c[j]];
		memset(d[1-i&1],0,sizeof(d[1-i&1]));
	}
	for(unsigned i=1;i<=s[0];i++)
		re+=d[n&1][i][pn];
	cout<<re<<endl;
	return 0;
}
