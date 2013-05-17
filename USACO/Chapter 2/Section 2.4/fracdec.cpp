/*
ID: dxmtb1
PROG: fracdec
LANG: C++
*/
#include <cstdio>
#include <cstdlib>
#include <string>
using namespace std;

const int MAXN=100001;

int N,D;
int in[10][MAXN];
string re;
char str[10];

void init()
{
	scanf("%d%d",&N,&D);
	sprintf(str,"%d",N/D);
	re+=str;
	if (N%D==0)
	{
		sprintf(str,".0\n");
		re+=str;
		printf("%s",re.c_str());
		exit(0);
	}
	else
		re+='.';
}

void solve()
{
	int stack[MAXN],stop=0;	
	for(int temp=N%D*10;;temp=temp*10)
	{
		int x=temp/D;
		temp=temp%D;
		stack[++stop]=x;
		if (temp==0)
		{
			for(int i=1;i<=stop;i++)
			{
				sprintf(str,"%d",stack[i]);
				re+=str;
			}
			break;
		}
		if (in[x][temp])
		{
			for(int i=1;i<in[x][temp];i++)
			{
				sprintf(str,"%d",stack[i]);
				re+=str;
			}
			re+='(';
			for(int i=in[x][temp];i<stop;i++)
			{
				sprintf(str,"%d",stack[i]);
				re+=str;
			}
			re+=')';
			break;
		}
		else
		{
			in[x][temp]=stop;			
		}
	}
	printf("%c",re[0]);
	for(int i=1;i<re.length();i++)
	{
		printf("%c",re[i]);
		if (i%76==75)
			printf("\n");
	}
	if (re.length()%76!=0)
		printf("\n");
}

int main() 
{
	freopen("fracdec.in","r",stdin);
	freopen("fracdec.out","w",stdout);
	init();
	solve();
	return 0;
}
