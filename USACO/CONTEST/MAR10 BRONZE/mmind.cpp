/*
PROG: mmind
LANG: C++
ID: dxmtb1
*/

#include <fstream>
#include <cmath>

using namespace std;

const int MAXN=100;

ifstream fin ("mmind.in");
ofstream fout ("mmind.out");

int check(int,int);
void cal(int i);

int n,data[MAXN][2];

int main()
{
	fin>>n;
	for(int i=0;i<n;i++) 
	{
		fin>>data[i][0];
		int x,y;
		fin>>x>>y;
		data[i][1]=x*10+y;
	}
	for(int i=1000;i<10000;i++)
		cal(i);
	fout<<"NONE"<<endl;
	return 0;
}

void cal(int x)
{
	for(int i=0;i<n;i++)
		if (check(x,data[i][0])!=data[i][1]) return;
	fout<<x<<endl;
	exit(0);
}

int check(int a,int b)
{
	int x=a,y=b,t1,t2,re=0;
	int h1[10],h2[10],h3[10];
	for(int i=0;i<10;i++)h1[i]=0,h2[i]=0,h3[i]=0;
	for(int i=1;i<=4;i++)
	{
		t1=x%10;
		t2=y%10;
		x=x/10;
		y=y/10;
		if (t1==t2) re=re+10,h1[t1]++;
		h2[t1]++;h3[t2]++;
	}
	for(int i=0;i<=9;i++)
		re+=min(h3[i],h2[i])-h1[i];
	return re;
}
