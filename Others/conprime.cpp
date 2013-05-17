/*
ID: dxmtb
PROG: 连续素数和
TIME: 2010.9.16
STATE: Solved
MEMO: 枚举
*/
#include <cstdio>
using namespace std;

const int MAXN=10005;

int prime[MAXN],top=1;
int re[MAXN],s[MAXN];

void init()
{
	bool flag[MAXN];
	for(int i=2;i<10000;i++)
		flag[i]=true;
	for(int i=2;i<10000;i++)
		if (flag[i])
		{
//			printf("%d\n",i);
			prime[top++]=i;
			for(int j=i+i;j<10000;j+=i)
				flag[j]=false;
		}
}

int main()
{
	init();
	freopen("conprime.in","r",stdin);
	freopen("conprime.out","w",stdout);
	for(int i=1;i<top;i++)
		s[i]=s[i-1]+prime[i];
	for(int i=0;i<top;i++)
		for(int j=i+1;j<top;j++)
			if (s[j]-s[i]<=10000)
			re[s[j]-s[i]]++;
	int n;
	scanf("%d",&n);;
	while(n)
	{
		printf("%d\n",re[n]);
		scanf("%d",&n);
	}
	return 0;
}
