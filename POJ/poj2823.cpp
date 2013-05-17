/*
ID: dxmtb
PROG: poj2823 Sliding Window
TIME: 2010.6.3
STATE: Solved
MEMO: dp 单调队列
*/
#include <cstdio>
#include <deque>
#include <cstring>
using namespace std;

const int MAXN=1000005;

int n,k;
int a[MAXN];

inline void put(int x){
	if(x< 0){
		putchar('-');
		x = -x;
	}
	if(x == 0){
		putchar('0');
		return;
	}
	char s[20];
	int bas = 0;
	for(;x;x/=10)s[bas++] = x%10+'0';
	for(;bas--;)putchar(s[bas]);
	return;
}


int main()
{
	scanf("%d%d\n",&n,&k);
	for (int p=getchar(),f=1,i=0;p!='\n';p=getchar())
		if (p == ' ')
			a[i]*=f,a[++i]=0,f=1;
		else
			if (p=='-')
				f=-1;
			else 
				if (p>='0'&&p<='9')a[i] = a[i] * 10 + p - '0';
	deque<int> q;
	for(int i=0;i<n;i++)
	{
		while (!q.empty()&&a[i]<=a[q.back()])
			q.pop_back();
		q.push_back(i);
		if(i-q.front()>=k)
			q.pop_front();
		if (i>=k)
			putchar(' ');
		if (i>=k-1)
			put(a[q.front()]);
	}
	putchar('\n');
	q.clear();
	for(int i=0;i<n;i++)
	{
		while (!q.empty()&&a[i]>=a[q.back()])
			q.pop_back();
		q.push_back(i);
		if(i-q.front()>=k)
			q.pop_front();
		if (i>=k)
			putchar(' ');
		if (i>=k-1)
			put(a[q.front()]);
	}	
	return 0;
}
