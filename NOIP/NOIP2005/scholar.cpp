/*
ID: dxmtb
PROG: NOIP2005 谁拿了最多奖学金
TIME: 2010.8.3
STATE: Solved
MEMO: 模拟
*/
#include <cstdio>
using namespace std;

const int MAXN=100;

char name[MAXN][MAXN];

int n;
int mp=-1,now,sum;

int main()
{
	freopen("scholar.in","r",stdin);
	freopen("scholar.out","w",stdout);
	scanf("%d",&n);
	for(int i=0;i<n;i++)
	{
		int fg,cg,th,sch=0;
		char gb,wp;
		scanf("\n");
		scanf("%s",name[i]);
		scanf("%d%d",&fg,&cg);
		scanf(" %c %c",&gb,&wp);
		scanf("%d",&th);
		if (fg>80&&th>0)
			sch+=8000;
		if (fg>85&&cg>80)
			sch+=4000;
		if (fg>90)
			sch+=2000;
		if (fg>85&&wp=='Y')
			sch+=1000;
		if (cg>80&&gb=='Y')
			sch+=850;
		if (sch>mp)
			mp=sch,now=i;
		sum+=sch;
	}
	printf("%s\n%d\n%d\n",name[now],mp,sum);
	return 0;
}
