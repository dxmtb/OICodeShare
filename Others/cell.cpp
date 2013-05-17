/*
ID: dxmtb
PROG: 细胞分裂
TIME: 2010.9.28
STATE: Solved
MEMO: 数论
*/
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;

int fm1[175],fm2[175],ftop;
int n,m1,m2;
int re=-1;

int prime[6000],ptop;
void init()
{
	bool flag[50000+1];
	for(int i=2;i<=50000;i++)
		flag[i]=true;
	for(int i=2;i<=50000;i++)
	{
		if (flag[i])
			prime[ptop++]=i;
		for(int j=0;j<ptop&&i*prime[j]<=50000;j++)
		{
			flag[i*prime[j]]=false;
			if (i%prime[j]==0)
				break;
		}
	}
}

void getfactor(int num,int fac[],int mul[],int &top)
{
	top=0;
	memset(fac,0,sizeof(fac));
	memset(mul,0,sizeof(mul));
	int k=sqrt(num);
	for(int i=0;i<ptop&&k>=prime[i];i++)
		if (num%prime[i]==0)
		{
			num/=prime[i],
			fac[top++]=prime[i],
			mul[top-1]=1;
			while (num%prime[i]==0)
				num/=prime[i],
				mul[top-1]++;
		}
	if (num!=1)
	{
		fac[top++]=num;
		mul[top-1]=1;
		return ;
	}
}

void solve()
{
	int s;
	scanf("%d",&s);
	int ft1[6000],ft2[6000],ft;
	getfactor(s,ft1,ft2,ft);
	int temp=-1;
	for(int i=0,j=0;i<ftop;)
	{
		if (ft1[j]<fm1[i])
			j++;
		else if (ft1[j]>fm1[i])
			return ;
		else temp=max(temp,int(ceil(fm2[i]/double(ft2[j])))),j++,i++;
		if (j>=ft&&i<ftop)
			return ;
	}
	if (temp!=-1&&(temp<re||re==-1))
		re=temp;
}

int main()
{
	freopen("cell.in","r",stdin);
	freopen("cell.out","w",stdout);
	scanf("%d%d%d",&n,&m1,&m2);
	init();
	if (m1==1&&m2==1)
	{
		printf("0\n");
		return 0;
	}
	getfactor(m1,fm1,fm2,ftop);
	for(int i=0;i<ftop;i++)
		fm2[i]*=m2;
	for(int i=0;i<n;i++)
		solve();
	printf("%d\n",re);
	return 0;
}
