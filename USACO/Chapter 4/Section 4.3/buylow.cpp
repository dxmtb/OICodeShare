/*
ID: dxmtb1
PROG: buylow
LANG: C++
*/
#include <cstdio>
#include <set>
#include <cstring>
using namespace std;

const int MAXN=5001;
const int BASE=1000;

struct High
{
	int a[200],len;
	High(){reset();}
	void reset(){len=1;memset(a,0,sizeof(a));}
};

void out(High a)
{
	printf("%d",a.a[a.len-1]);
	for(int i=a.len-2;i>=0;i--)
	{
		if (a.a[i]<10)
			printf("00");
		else if(a.a[i]<100)
			printf("0");
		printf("%d",a.a[i]);
	}
}

High operator + (High a,High b)
{
	High temp;
	temp.len=max(a.len,b.len);
	for(int i=0;i<temp.len;i++)
		temp.a[i]+=a.a[i]+b.a[i],
		temp.a[i+1]=temp.a[i]/BASE,
		temp.a[i]%=BASE;
	if (temp.a[temp.len])
		temp.len++;
//	out(a);printf(" + ");out(b);printf(" = ");out(temp);printf("\n");
	return temp;
}

int N,a[MAXN];
int d[MAXN];
int cot[MAXN];
High sum[MAXN];
//int sum[MAXN];

int main()
{
	freopen("buylow.in","r",stdin);
	freopen("buylow.out","w",stdout);
	scanf("%d",&N);
	for(int i=0;i<N;i++)
		scanf("%d",a+i);
	d[N++]=0;
	for(int i=0;i<N;i++)
	{
		cot[i]=0x7fffffff;
		for(int j=i+1;j<N;j++)
			if (a[i]==a[j])
			{
				cot[i]=j;
				break;
			}
//		printf("%d ",cot[i]);
	}
//	printf("\n");
	for(int i=0;i<N;i++)
	{
		d[i]=1;sum[i].reset();sum[i].len=1,sum[i].a[0]=1;
		//sum[i]=1;
		for(int j=0;j<i;j++)
			if (cot[j]>i)
			if (a[j]>a[i])
			{
				if (d[j]+1>d[i]) 
				{
					d[i]=d[j]+1;
					sum[i]=sum[j];
				}
				else if (d[j]+1==d[i])
					sum[i]=sum[i]+sum[j];
			}
	}
/*	for(int i=0;i<N;i++)
		printf("%d ",d[i]);
	printf("\n");
	for(int i=0;i<N;i++)
	{
		out(sum[i]);
		printf("%d",sum[i]);
		printf(" ");
	}
	printf("\n");*/
	printf("%d ",d[N-1]-1);
	out(sum[N-1]);
//	printf("%d",sum[N-1]);
	printf("\n");
	return 0;
}
