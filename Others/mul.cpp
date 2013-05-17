#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
using namespace std;

const int MAXN=300;

ifstream fin ("mul.in");
ofstream fout ("mul.out");

int a[MAXN],b[MAXN],c[MAXN];

int main()
{
	void init(void);
	void mul(const int a[],const int c[],int c[]);
	void print(const int c[]);
	init();
	mul(a,b,c);
	print(c);
	return 0;
}

void init()
{
	string str1,str2;
	getline(fin,str1);
	getline(fin,str2);
	a[0]=str1.length();
	b[0]=str2.length();
	int t1=a[0],t2=b[0];
	for(int i=1,k=1;i<=a[0];i++,k++)
	{
		a[k]=str1[a[0]-i]-48;
		if (a[k]<0) {k--;t1--;}
	}
	for(int i=1,k=1;i<=b[0];i++,k++)
	{
		b[k]=str2[b[0]-i]-48;
		if (b[k]<0) {k--;t2--;}
	}
	a[0]=t1;
	b[0]=t2;
	memset(c,0,sizeof(c));
}

void mul(const int a[],const int b[],int c[])
{
	for(int i=1;i<=a[0];i++)
		for(int j=1;j<=b[0];j++)
		{
			c[i+j-1]+=a[i]*b[j];
			c[i+j]+=int(floor(double(c[i+j-1]/10)));
			c[i+j-1]=c[i+j-1] % 10;
		}
	c[0]=a[0]+b[0]+1;
	while((c[c[0]]==0)&&(c[0]>1))c[0]--;	
}

void print(const int c[])
{
	for(int i=c[0];i>=1;i--)
		fout<<c[i];
}
