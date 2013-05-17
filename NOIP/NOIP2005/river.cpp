/*
ID: dxmtb
PROG: NOIP2005 ¹ýºÓ
TIME: 2010.8.3
STATE: Solved
MEMO: dp+ÀëÉ¢»¯
*/
#include <cstdio>
#include <algorithm>
using namespace std;

const int MAXM=100,MAXT=10,MAXN=MAXM*MAXT*10;
const int oo=0x7fffffff;

int s,t,m,L,sub,re=oo;
int d[MAXN];
int pos[MAXN];
bool is[MAXN];

int main()
{
	freopen("river.in","r",stdin);
	freopen("river.out","w",stdout);
	scanf("%d%d%d%d",&L,&s,&t,&m);
	m+=2;
	pos[0]=0;
	pos[m-1]=L;
	for(int i=1;i<=m;i++)
		scanf("%d",pos+i);
	sort(pos,pos+m);
	is[pos[0]]=true;
	for(int i=1,temp;i<m;i++)
	{
		pos[i]-=sub;
		temp=(pos[i]-pos[i-1])/t;
		if (temp>1)temp--,temp*=t,pos[i]-=temp,sub+=temp;
		is[pos[i]]=true;
	}
	L-=sub;
	for(int i=1;i<=L+t;i++)
		d[i]=oo;
	d[0]=0;
	is[L]=false;
	for(int i=0;i<L;i++)
		if (d[i]!=oo)
		for(int j=i+s;j<=i+t;j++)
		{
				d[j]=min(d[j],d[i]+is[j]);
				if (j>=L&&d[j]<re)
					re=d[j];
		}
	printf("%d\n",re);
	return 0;
}
