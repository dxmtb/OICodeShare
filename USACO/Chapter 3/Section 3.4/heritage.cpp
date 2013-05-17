/*
ID: dxmtb1
PROG: heritage
LANG: C++
*/
#include <cstdio>
#include <cstring>
using namespace std;

const int MAXN=28;

char in[MAXN],pre[MAXN];
int n;

void solve(int l1,int r1,int l2,int r2)
{
	if (r1<l1||r2<l2)return ;
	char mid=pre[l2];
	for(int i=l1;i<=r1;i++)
		if (in[i]==mid)
		{
			solve(l1,i-1,l2+1,l2+i-l1);
			solve(i+1,r1,l2+i-l1+1,r2);
			printf("%c",mid);
			break;
		}
}

int main()
{
	freopen("heritage.in","r",stdin);
	freopen("heritage.out","w",stdout);
	fgets(in,sizeof(in),stdin);
	scanf("\n");
	fgets(pre,sizeof(pre),stdin);
	n=strlen(in)-1;
	solve(0,n-1,0,n-1);
	printf("\n");
	return 0;
}
