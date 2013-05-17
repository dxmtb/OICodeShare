/*
 * Problem: poj2185 Milking Grid
 * Time: 2011.04.08
 * Author: dxmtb
 * State: Solved
 * Memo: KMP
*/
#include <cstdio>

const int MAXR=10005,MAXC=80;

inline int gcd(int a,int b)
{
	int c;
	while(b)
	{
		c=b;
		b=a%b;
		a=c;
	}
	return a;
}

inline int lcm(int a,int b)
{
	return a*b/gcd(a,b);
}

int next[MAXR];
char str[MAXR][MAXC];
int R,C;

int main()
{
	freopen("poj2185.in","r",stdin);
	scanf("%d%d",&R,&C);
	for(int i=0;i<R;i++)
		scanf(" %s",str[i]);
	int re1=1,re2=1;
	for(int x=0;x<R;x++)
	{
		next[0]=-1;
		for(int i=1,j=-1;i<C;i++)
		{
			while(j>=0 && str[x][i]!=str[x][j+1]) 
				j=next[j];
			if (str[x][i]==str[x][j+1])
				j++;
			next[i]=j;
		}
		re1=lcm(re1,C-next[C-1]-1);
		if (re1>=C)
		{
			re1=C;
			break;
		}
	}
	for(int y=0;y<C;y++)
	{
		next[0]=-1;
		for(int i=1,j=-1;i<R;i++)
		{
			while(j>=0 && str[i][y]!=str[j+1][y]) 
				j=next[j];
			if (str[i][y]==str[j+1][y])
				j++;
			next[i]=j;
		}
		re2=lcm(re2,R-next[R-1]-1);
		if (re2>=R)
		{
			re2=R;
			break;
		}
	}
	printf("%d\n",re1*re2);
	return 0;
}
