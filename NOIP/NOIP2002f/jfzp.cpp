/*
ID: dxmtb
PROG: NOIP2002 均分纸牌
TIME: 2010.5.2
STATE: Solved
MEMO: 数学方法
*/
#include <cstdio>
#include <cmath>
using namespace std;

const int MAXN=100;

int n,m,a[MAXN],re;

void init()
{
	scanf("%d",&n);
	for(int i=0;i<n;m+=a[i++])
		scanf("%d",&a[i]);
	m=m/n;
}

int change(int l,int r)
{
	if (l>=r)return 0;
	int max=-1,j;
	for(int i=l;i<=r;i++)
		if (a[i]>max)max=a[i],j=i;
	int nl=0,nr=0;
	for(int i=l;i<j;i++)
		nl+=m-a[i];
	for(int i=j+1;i<=r;i++)
		nr+=m-a[i];
	a[j-1]+=nl;
	a[j+1]+=nr;
	bool b1=nl,b2=nr;
	return(change(l,j-1)+change(j+1,r)+b1+b2);
}

int main() 
{
	freopen("jfzp.in","r",stdin);
	freopen("jfzp.out","w",stdout);
	init();
	printf("%d\n",change(0,n-1));
	return 0;
}
