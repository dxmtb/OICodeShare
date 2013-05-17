/*
ID: dxmtb1
PROG: hamming
LANG: C++
*/
#include <cstdio>
#include <cstdlib>
using namespace std;

const int MAXN=64,MAXB=8,MAXD=7;
const unsigned MAX=1<<MAXB;

FILE *fin=fopen("hamming.in","r");
FILE *fout=fopen("hamming.out","w");

int n,b,d;
unsigned way[MAXN];

void search(int,unsigned);
bool check(unsigned,int);

int main()
{
	fscanf(fin,"%d%d%d",&n,&b,&d);
	way[0]=0;
	search(1,0);
	return 0;
}

void search(int dep,unsigned last)
{
	if (dep>=n) 
	{
		fprintf(fout,"%d",way[0]);
		for(int i=1;i<n;i++)
		{
			if (i%10==9)fprintf(fout," %d\n",way[i]);
			else if (i%10==0)fprintf(fout,"%d",way[i]);
			else fprintf(fout," %d",way[i]);
		}
		if (n%10!=0)fprintf(fout,"\n");
		exit(0);
	}
	for(unsigned i=last+1;i<MAX;i++)
	{
		way[dep]=i;
		if (check(i,dep)) search(dep+1,i);
	}
}

bool check(unsigned x,int dep)
{
	for(int i=0;i<dep;i++)
	{
		unsigned temp=x^way[i];
		int timer=0;
		for(int j=0;j<8;j++)
			timer+=(temp>>j)&1u;
		if (timer<d) return false;
	}
	return true;
}
