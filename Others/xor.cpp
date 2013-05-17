/*
ID: dxmtb
PROG: 有道难题资格赛一 另类的异或
TIME: 2010.5.29
STATE: Solved
MEMO: 模拟
*/
#include <cstdio>
#include <cstring>
using namespace std;

const int MAXN=1010;

int a,b,n;
char str[MAXN];
int num[2][50],len;

inline int pow(int __x,int __n)
{
	int __y = __n % 2 ? __x : 1;

	while (__n >>= 1)
	{
		__x = __x * __x;
		if (__n % 2)
			__y = __y * __x;
	}
	return __y;
}

void init()
{
	len=0;
	memset(num,0,sizeof(num));
	memset(str,0,sizeof(str));
	scanf("%d%s%d",&a,str,&b);
	n=strlen(str);
	n++;
}

void change(int nu,int i)
{
	int co=0;
	while (nu!=0)
	{
		num[i][co++]=nu%n;
		nu=nu/n;
	}
	if (co>len)
		len=co;
}


void solve()
{
	change(a,0);
	change(b,1);
	int temp[50],re=0;
	for(int i=0;i<len;i++)
	{
		temp[i]=(num[0][i]+num[1][i])%n;
		re+=(num[0][i]+num[1][i])%n*pow(n,i);
	}
	printf("%d\n",re);
}

int main() 
{
//	freopen("xor.in","r",stdin);
//	freopen("xor.out","w",stdout);
	int T;
	scanf("%d",&T);
	for(int i=0;i<T;i++)
	{
		init();
		solve();
	}
	return 0;
}
