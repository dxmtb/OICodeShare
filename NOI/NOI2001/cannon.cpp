/*
ID: dxmtb
PROG: NOI2001 ÅÚ±øÕóµØ
TIME: 2010.4.18
STATE: Solved
MEMO: ×´Ì¬Ñ¹Ëõ¶¯Ì¬¹æ»®
*/
#include <cstdio>
using namespace std;

const int MAXN=100,MAXM=10,MAXS=(1<<MAXM)-1;

int n,m,d[2][MAXS+1][MAXS+1],line[MAXN],s[MAXS]={0},c[MAXS],re=0;

void dfs(int dep,int one,int state,bool f1,bool f2)
{
	if (dep==m)
		s[++s[0]]=state,c[s[0]]=one;
	else
	{
		dfs(dep+1,one,state*2,f2,false);
		if (!(f1||f2))
		dfs(dep+1,one+1,state*2+1,f2,true);
	}
}

inline int max(int a,int b)
{return a>b?a:b;}

int main() 
{
	freopen("cannon.in","r",stdin);
	freopen("cannon.out","w",stdout);
	scanf("%d%d",&n,&m);
	dfs(0,0,0,false,false);
	int i,j,k,p;
	char tmp[MAXM+1];
	for(i=1;i<=n;i++)
	{
		scanf("%s",tmp+1);
		for(j=1;j<=m;j++)
			line[i]=line[i]*2+(tmp[j]=='H');		
		for(j=1;j<=s[0];j++)
			if (!(s[j]&line[i]))
			for(k=1;k<=s[0];k++)
				if (!(s[j]&s[k])&&!(s[k]&line[i-1]))
				for(p=1;p<=s[0];p++)
					if (!(s[p]&line[i-2])&&!(s[j]&s[p])&&!(s[k]&s[p]))
					if (d[1-i&1][k][p]+c[j]>d[i&1][j][k])
					d[i&1][j][k]=d[1-i&1][k][p]+c[j],
					re=max(re,d[i&1][j][k]);
	}
	printf("%d\n",re);
	return 0;
}
