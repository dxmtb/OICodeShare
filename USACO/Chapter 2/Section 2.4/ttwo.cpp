/*
ID: dxmtb1
PROG: ttwo
LANG: C++
*/
#include <cstdio>
#include <cstdlib>
using namespace std;

const int MAXN=10,rule[4][2]={{0,1},{1,0},{0,-1},{-1,0}};

char str[MAXN][MAXN+1];
int john[2],cow[2],step=0,d1=3,d2=3;
bool hash[MAXN][MAXN][MAXN][MAXN][4][4];

void init()
{
	for(int i=0;i<MAXN;i++)
	{
		gets(str[i]);
		for(int j=0;j<MAXN;j++)
			if (str[i][j]=='C')cow[0]=i,cow[1]=j;
			else if (str[i][j]=='F')john[0]=i,john[1]=j;
	}
}

void search()
{
	hash[john[0]][john[1]][cow[0]][cow[1]][d1][d2]=true;
	while (!(john[0]==cow[0]&&john[1]==cow[1]))
	{
		step++;
		if (john[0]+rule[d1][0]>=0&&john[0]+rule[d1][0]<10
			&&john[1]+rule[d1][1]>=0&&john[1]+rule[d1][1]<10
			&&str[john[0]+rule[d1][0]][john[1]+rule[d1][1]]!='*')
			john[0]+=rule[d1][0],john[1]+=rule[d1][1];
		else d1=(d1+1)%4;
		if (cow[0]+rule[d2][0]>=0&&cow[0]+rule[d2][0]<10
			&&cow[1]+rule[d2][1]>=0&&cow[1]+rule[d2][1]<10
			&&str[cow[0]+rule[d2][0]][cow[1]+rule[d2][1]]!='*')
			cow[0]+=rule[d2][0],cow[1]+=rule[d2][1];
		else d2=(d2+1)%4;
		if (hash[john[0]][john[1]][cow[0]][cow[1]][d1][d2])
		{
			printf("0\n");exit(0);
		}
		else
			hash[john[0]][john[1]][cow[0]][cow[1]][d1][d2]=true;
	}
	printf("%d\n",step);
}

int main() 
{
	freopen("ttwo.in","r",stdin);
	freopen("ttwo.out","w",stdout);
	init();
	search();
	return 0;
}
