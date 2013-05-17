#include <cstdio>
#include <cstring>
#include <string>
#include <map>
using namespace std;

const int MAXN=200;
const int oo=0x7fffffff;

bool g[MAXN][MAXN];

int N,M;

map<string,int> s1;

int main(int argc,char **argv)
{
	FILE *fin=fopen(argv[1],"r");
	FILE *fans=fopen(argv[2],"r");
	FILE *fout=fopen(argv[3],"r");
	fscanf(fin,"%d%d",&N,&M);
	for(int i=1;i<=N;i++)
	{
		char str[20];
		fscanf(fin,"%s",str);
		s1[string(str)]=i;
	}
	while(M--)
	{
		char str1[20],str2[20];
		fscanf(fin,"%s%s",str1,str2);
		int u=s1[str1],v=s1[str2];
		g[u][v]=g[v][u]=true;
	}
	int ans1,ans2;
	fscanf(fout,"%d",&ans1);
	fscanf(fans,"%d",&ans2);
	if (ans1!=ans2)
	{
		printf("Wrong at the beginning or maybe no solution!\n");
		printf("Please check yourself...\n");
		return 0;
	}
	bool flag=false;
	char str[20];
	int u,v;
	u=1;
	fscanf(fout,"%s",str);
	if (s1[str]!=u)
	{
		printf("It should be the first!\n");
		return 0;
	}
	while(--ans1)
	{
		fscanf(fout,"%s",str);
		v=s1[str];
		if (u==v)
		{
			printf("Double %d\n!",u);
			return 0;
		}
		if (flag^(u>v))
		{
			printf("Wrong order!\n");
			return 0;
		}
		if (!g[u][v])
		{
			printf("Mismatch %d %d",u,v);
			return 0;
		}
		if (v==N)
			flag=true;
		u=v;
	}
	printf("Accepted!\n");
	return 0;
}
