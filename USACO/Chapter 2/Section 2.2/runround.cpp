/*
ID: dxmtb1
PROG: runround
LANG: C++
*/
#include <cstdio>

using namespace std;

const unsigned MAXN=1<<32-1;

unsigned m,i;

FILE *fin=fopen("runround.in","r");
FILE *fout=fopen("runround.out","w");

bool check(unsigned x)
{
	if (x<10)return false;
	int temp=x,num[9],timer=-1,timer2=0,pos;
	bool in[10];
	for(int i=0;i<10;i++)in[i]=false;
	while (temp!=0)
	{
		unsigned y=temp%10;
		if (in[y]||y==0)return false;
		else in[y]=true,num[++timer]=y;
		temp=temp/10;
	}
	for(int i=0;i<10;i++)in[i]=false;
	pos=timer;
	while (timer2<timer+1)
	{
		if (in[num[pos]])return false;
		else in[num[pos]]=true,timer2++;		
		pos-=num[pos];
		while(pos<0)pos+=timer+1;
	}
	if (pos==timer)return true;
	else return false;
}

int main() 
{
	fscanf(fin,"%d",&m);
	
	for(i=m+1;i<MAXN;i++)
		if (check(i))
			{fprintf(fout,"%d\n",i);break;}
	return 0;
}
