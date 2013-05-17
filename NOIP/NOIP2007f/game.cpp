/*
ID: dxmtb
PROG: NOIP2007 矩阵取数游戏
TIME: 2010.7.23
STATE: Solved
MEMO: dp + 高精度
*/
#include <cstdio>
#include <cstring>
using namespace std;

const int MAXN=80,MAXL=100,br=10000;

struct High
{
	int a[10],len;
	High () {memset(a,0,sizeof(a));len=1;}
	void operator = (int num)
	{
		len=0;
		do
		{
			a[len++]=num%br;
			num/=br;
		}while(num);
	}
};
	
High operator + (High a,High b)
{
	High temp;
	temp.len=a.len>b.len?a.len:b.len;
	for(int i=0;i<temp.len;i++)
		temp.a[i]+=a.a[i]+b.a[i],
		temp.a[i+1]=temp.a[i]/br,
		temp.a[i]%=br;
	if (temp.a[temp.len])temp.len++;
	return temp;
}

High operator * (High a,int b)
{
	High temp;temp.len=a.len;
	for(int i=0;i<a.len;i++)
		temp.a[i]+=a.a[i]*b,
		temp.a[i+1]=temp.a[i]/br,
		temp.a[i]%=br;
	while (temp.a[temp.len])
		temp.a[temp.len+1]=temp.a[temp.len]/br,
		temp.a[temp.len++]%=br;
	return temp;
}

bool operator < (High a,High b)
{
	if (a.len<b.len)return true;
	else if (a.len>b.len)return false;
	for(int i=a.len-1;i>=0;i--)
		if (a.a[i]<b.a[i])return true;
		else if (a.a[i]>b.a[i])return false;
	return false;
}

int n,m;
int sq[MAXL];

High d[MAXL][MAXL],re;
High two[MAXL];
High w[MAXL][MAXL];
	
void solve()
{
	for(int i=0;i<m;i++)
		w[i][m-1]=sq[i]*2;
	for(int j=m-2;j>=0;j--)
		for(int i=0;i<m;i++)
			w[i][j]=w[i][j+1]*2;
	for(int j=1;j<m;j++)
		for(int i=0;i+j<m;i++)
		{
			d[i][j]=d[i][j-1]+w[i+j][j];
			if (d[i][j]<d[i+1][j-1]+w[i][j])
				d[i][j]=d[i+1][j-1]+w[i][j];
		}
	re=re+d[0][m-1];
}

void out(High num)
{
	printf("%d",num.a[num.len-1]);
	for(int i=num.len-2;i>=0;i--)
	{
		int temp=num.a[i];
		if (temp<10)printf("000");
		else if (temp<100)printf("00");
		else if (temp<1000)printf("0");
		printf("%d",temp);
	}
	printf("\n");
}

int main() 
{
	freopen("game.in","r",stdin);
	freopen("game.out","w",stdout);
	scanf("%d%d",&n,&m);
	two[0]=2;
	for(int i=1;i<m;i++)
		two[i]=two[i-1]*2;
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<m;j++)
		{
			scanf("%d",sq+j);
			d[j][0]=two[m-1]*sq[j];
		}
		solve();
	}
//	printf("%d\n",re);
	out(re);
	return 0;
}
