/*
  ID: dxmtb1
  PROG: fact4
  LANG: C++
*/
#include <cstdio>
using namespace std;

const int MAXN=4220;

int n;

int main()
{
	freopen("fact4.in","r",stdin);
	freopen("fact4.out","w",stdout);
	scanf("%d",&n);
	int temp=1;
	for(int i=2;i<=n;i++)
	{
		temp=temp*i%1000000;
		while(temp%10==0)
			temp/=10;
	}
	printf("%d\n",temp%10);
	return 0;
}
