/*
ID: dxmtb
PROG: 排序工作量
TIME: 2010.10.14
STATE: Solved
MEMO: 枚举
*/
#include <cstdio>
using namespace std;

const int MAXN=10005;

int N,re;
double a[MAXN];

int main()
{
	freopen("sortt.in","r",stdin);
	freopen("sortt.out","w",stdout);
	scanf("%d",&N);
	for(int i=0;i<N;i++)
		scanf("%lf",a+i);
	for(int i=0;i<N;i++)
		for(int j=i+1;j<N;j++)
			if (a[i]>a[j])
				re++;
	printf("%d\n",re);
	return 0;
}
