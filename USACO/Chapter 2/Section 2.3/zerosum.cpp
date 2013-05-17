/*
ID: dxmtb1
PROG: zerosum
LANG: C++
*/
#include <cstdio>
#include <cstring>
#include <stack>
using namespace std;

const int MAXN=9;

FILE *fin=fopen("zerosum.in","r");
FILE *fout=fopen("zerosum.out","w");

int n,multi[MAXN-1];

void search(int a)
{
	if (a>n)
	{
		stack<int> s1,s2;
		int num=0,t=1;
		for(int i=0;i<n-1;i++)
		{
			num=num*10+i+1;
			switch (multi[i])
			{
				case 0:break;
				case 1:s1.push(num*t);t=1;num=0;s2.push(1);break;
				case 2:s1.push(num*t);t=-1;num=0;s2.push(1);break;
			}
		}
		num=num*10+n;
		s1.push(num*t);
		while (!s2.empty())
		{
			s2.pop();
				int a=s1.top();s1.pop();
				int b=s1.top();s1.pop();
				s1.push(a+b);		
		}
		if (s1.top()==0)
		{
			for(int i=1;i<n;i++)
			{
				fprintf(fout,"%d",i);
				switch(multi[i-1])
				{
					case 0:fprintf(fout," ");break;
					case 1:fprintf(fout,"+");break;
					case 2:fprintf(fout,"-");break;
				}
			}
			fprintf(fout,"%d\n",n);
		}
		return;
	}
	multi[a-2]=0;//space
	search(a+1);
	multi[a-2]=1;//+
	search(a+1);
	multi[a-2]=2;//-
	search(a+1);
}
int main()
{
	fscanf(fin,"%d",&n);
	search(2);
	return 0;
}
