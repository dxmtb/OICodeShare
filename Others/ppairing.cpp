/*
ID: dxmtb
PROG: 珍珠分对
TIME: 2010.10.20
STATE: Solved
MEMO: 贪心+调整
*/
#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN=100005;

int C[MAXN];
int N,c;
int ans[MAXN/2][2],t;

int main()
{
	freopen("ppairing.in","r",stdin);
	freopen("ppairing.out","w",stdout);
	scanf("%d%d",&N,&c);
	for(int i=0;i<c;i++)
		scanf("%d",C+i);
	for(int i=0,j=c-1;N;)
	{
		while(C[i]==0)
			++i;
		while(C[j]==0)
			--j;
		if (i==j&&C[i]!=0)
		{
			for(int k=0;k<t&&C[i];k++)
				if (ans[k][0]!=i&&ans[k][1]!=j)
					ans[t][0]=i,ans[t][1]=ans[k][0],t++,
					ans[k][0]=i,C[i]-=2,N-=2;
			if (N!=0)cerr<<"wrong\n";
			break;
		}
		else if (i>j) cerr<<"wrong!\n";
		int k=min(C[i],C[j]);
		C[i]-=k;
		C[j]-=k;
		N-=(k<<1);
		while(k--)
			ans[t][0]=i,
			ans[t][1]=j,
			t++;
	}
	for(int i=0;i<t;i++)
		printf("%d %d\n",ans[i][0]+1,ans[i][1]+1);
	return 0;
}
	
