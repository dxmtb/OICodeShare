/*
ID: dxmtb
PROG: »­Õ¹
TIME: 2010.10.24
STATE: Solved
MEMO: Ã¶¾Ù
*/
#include <cstdio>
using namespace std;

const int MAXN=1000005,MAXM=2500;

int n,m,a[MAXN];
int use[MAXM];
int re=0x7fffffff,ri,rj;

int main()
{
	freopen("exhibit.in","r",stdin);
	freopen("exhibit.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=0;i<n;i++)
		scanf("%d",a+i);
	for(int i=0,k=m,j=-1;i<n;)
	{
		while(k)
		{
			j++;
			if (j==n) break;
			if (j<i)
				j=i;
			if (use[a[j]]==0)
				k--;
			use[a[j]]++;
		}
		if (k) break;
		if (j-i<re)
			ri=i,rj=j,re=j-i;
		use[a[i]]--;
		if (use[a[i]]==0)
			k++;
		i++;
	}
	printf("%d %d\n",ri+1,rj+1);
	return 0;
}
