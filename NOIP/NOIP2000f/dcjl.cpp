/*
ID: dxmtb
PROG: NOIP2000 µ¥´Ê½ÓÁú
TIME: 2010.4.9
STATE: Solved
MEMO: 
*/
#include <cstdio>
#include <string>
using namespace std;

const int MAXN=20;

int comp(const void * a, const void * b)
{
  return ( *(string*)a > *(string*)b );
}
void search(int a,int);
void dfs();

FILE *fin=fopen("dcjl.in","r");
FILE *fout=fopen("dcjl.out","w");

int n,re=0;

string str[MAXN];
int used[MAXN];
int can[MAXN][MAXN];
char head;

int main() 
{
	fscanf(fin,"%d",&n);
	for(int i=0;i<n;i++)
	{
		char buf[1024];
		fscanf(fin,"%s",&buf);
		str[i]=buf;
	}
	qsort(str,n,sizeof(string),comp);
	fscanf(fin,"\n%c",&head);
	for(int i=0;i<MAXN;i++)
		used[i]=2;
	memset(can,0,sizeof(can));
	dfs();
	for(int i=0;i<n;i++)
		if (str[i][0]==head)
		{
			used[i]--;
			search(i,str[i].length());
			used[i]++;
		}
	fprintf(fout,"%d\n",re);
    return 0;
}

void search(int a,int b)
{
	if (b>re) re=b;
	for(int i=0;i<n;i++)
		if (used[i]>0&&can[a][i]>0&&str[i].length()!=can[a][i])
		{
			used[i]--;
			search(i,b+str[i].length()-can[a][i]);
			used[i]++;
		}
}

void dfs()
{
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
			{
			for(int k=str[i].length()-1;k>0&&str[i].length()-k<str[j].length();k--)
				if (str[i][k]==str[j][0])
				{
					bool flag=false;
					for(int a=0;a<str[i].length()-k;a++)
						if (str[i][k+a]!=str[j][a]) {flag=true;break;}
					if (!flag) {can[i][j]=str[i].length()-k;break;}
				}
			}
}
