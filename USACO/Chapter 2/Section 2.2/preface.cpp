/*
ID: dxmtb1
PROG: preface
LANG: C++
*/
#include <cstdio>
#include <string>
#include <cmath>

using namespace std;

const int MAXN=7;
const int num[MAXN]={1,5,10,50,100,500,1000};
const int list[10][3]={{},{1},{2},{3},{1,1},{0,1},{1,1},{2,1},{3,1},{1,0,1}};

int n,ans[MAXN];

FILE *fin=fopen("preface.in","r");
FILE *fout=fopen("preface.out","w");

int main() 
{
	fscanf(fin,"%d",&n);
	for(int x=1;x<=n;x++)
	{
		int temp;
		for(int i=1;i<=4;i++)
		{
			temp=x%(int)(pow(10.0,i))/(int)(pow(10.0,i-1));
			for(int j=0;j<3;j++)
				ans[j+2*(i-1)]+=list[temp][j];
		}
	}
	if (ans[0]>0) fprintf(fout,"I %d\n",ans[0]);
	if (ans[1]>0) fprintf(fout,"V %d\n",ans[1]);
	if (ans[2]>0) fprintf(fout,"X %d\n",ans[2]);
	if (ans[3]>0) fprintf(fout,"L %d\n",ans[3]);
	if (ans[4]>0) fprintf(fout,"C %d\n",ans[4]);
	if (ans[5]>0) fprintf(fout,"D %d\n",ans[5]);
	if (ans[6]>0) fprintf(fout,"M %d\n",ans[6]);
	return 0;
}
