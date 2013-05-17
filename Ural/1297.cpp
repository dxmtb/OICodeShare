/*
ID: dxmtb
PROG: Ural1297 Palindrome
TIME: 2011.03.03
STATE: Solved
MEMO: New LCP
*/
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;

typedef long long s64;

const int MAXN=1005;
const int Pow[11]={1,2,4,8,16,32,64,128,256,512,1024};
const s64 oo=~0ull>>1;

int N;
char str1[MAXN],str2[MAXN];
int Ra[MAXN];
int Log[MAXN];
s64 X1[MAXN][11],X2[MAXN][11];

void init(s64 X[][11],char str[])
{
	for(int i=N-1;i>=0;i--)
	{
		X[i][0]=Ra[int(str[i])];
		for(int j=1;i+Pow[j]-1<N;j++)
			X[i][j]=((X[i][j-1]*Ra[j])^X[i+Pow[j-1]][j-1])&oo;
	}
}

inline int LOG2(int a)
{
	return Log[a];
}

inline int lcp(int a,int b)
{
	int re=0;
	for(int k=LOG2(N-max(a,b));k>=0;k--)
		if (a+Pow[k]-1<N && b+Pow[k]-1<N && X1[a][k]==X2[b][k])
			a+=Pow[k],b+=Pow[k],re+=Pow[k];
	return re;
}

inline void Max(int &a,int b)
{
	if (b>a)
		a=b;
}

int main()
{
	scanf("%s",str1);
	N=strlen(str1);
	for(int i=0;i<N;i++)
		str2[i]=str1[N-1-i];
	for(int i=0;i<255;i++)
		Ra[i]=rand();
	for(int i=2;i<N;i++)
		Log[i]=Log[i/2]+1;
	init(X1,str1);
	init(X2,str2);
	int re=1,ri=0;
	for(int i=0;i<N;i++)
	{
		int t;
		if (i!=0 && i!=N-1 && (t=lcp(i+1,N-i))*2+1>re)
			re=t*2+1,ri=i-t;
		if (i!=0 && (t=lcp(i,N-i))*2>re)
			re=t*2,ri=i-t;
	}
	for(int i=ri;i<ri+re;i++)
		printf("%c",str1[i]);
	printf("\n");
//	printf("%d\n",re);
	return 0;
}
