/*
 * Problem: [FJOI2007]ÂÖ×´²¡¶¾ 
 * Time: 2011.04.19
 * Author: dxmtb
 * State: Solved
 * Memo: dp+¸ß¾«¶È
*/
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

typedef long long s64;

const int MAXN=105;

struct High;
ostream &operator << (ostream &out,const High &a);

struct High
{
	int len,a[100];
	High operator + (const High &b)
	{
		High c;
		c.len=max(len,b.len);
		for(int i=0;i<c.len;i++)
		{
			c.a[i]+=a[i]+b.a[i];
			c.a[i+1]=c.a[i]/1000;
			c.a[i]%=1000;
		}
		if (c.a[c.len])
			c.len++;
		//cout<<*this<<'+'<<b<<'='<<c<<endl;
		return c;
	}
	High operator * (const int b)
	{
		High a=*this;
		for(int i=0;i<len;i++)
			a.a[i]*=b;
		for(int i=0;i<len;i++)
			a.a[i+1]+=a.a[i]/1000,a.a[i]%=1000;
		while(a.a[a.len])
			a.len++;
		//cout<<*this<<'*'<<b<<'='<<a<<endl;
		return a;
	}
	High operator =(const int b)
	{
		len=1;
		a[0]=b;
		return *this;
	}
	High()
	{
		memset(a,0,sizeof(a));
		len=1;
	}
};

ostream &operator << (ostream &out,const High &a)
{
	out<<a.a[a.len-1];
	for(int i=a.len-2;i>=0;i--)
	{
		if (a.a[i]>=100)
			out<<a.a[i];
		else if (a.a[i]>=10)
			out<<'0'<<a.a[i];
		else
			out<<"00"<<a.a[i];
	}
	return out;
}

int N;
High d[MAXN],re;

int main()
{
	freopen("1002.in","r",stdin);
	scanf("%d",&N);
	d[0]=1;
	for(int i=1;i<=N;i++)
		for(int j=0;j<i;j++)
			d[i]=d[i]+d[j]*(i-j);
	re=d[N];
	for(int i=1;i<=N;i++)
		for(int j=i+1;j<=N;j++)
			re=re+d[j-i-1]*(i+N-j+1);
	cout<<re<<endl;
	return 0;
}
