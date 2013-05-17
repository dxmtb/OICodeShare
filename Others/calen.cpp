/*
ID: dxmtb
PROG: 日历
TIME: 2010.11.9
STATE: Solved
MEMO: 模拟
*/
#include <cstdio>
const int day[12]={31,28,31,30,31,30,31,31,30,31,30,31};

int N,M;

int mod(int a,int b)
{
	a%=b;
	if (a<0)
		a+=b;
	return a;
}

bool leap(int year)
{
	if (year%4!=0)
		return false;
	if (year%100==0)
		return ((year%400)==0);
	return true;
}

int main()
{
	scanf("%d",&N);
	int week=4;
	for(int i=2010;i>N;i--)
	{
		if (mod(week-1,7)==4)
			M++;
		for(int j=11;j>=0;j--)
		{
			if (j==1)
				week=mod(week-(leap(i)?29:28),7);
			else
				week=mod(week-day[j],7);
	//		printf("%d %d\n",j,week+1);
			if (j!=2&&j!=0&&mod(week+30-day[j-1],7)==4)
				M++;
		}
	}
	printf("%d\n",M);
	return 0;
}

