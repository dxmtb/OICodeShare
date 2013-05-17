#include <cstdio>
#include <sstream>
using namespace std;

const int MAXN=200;

bool map[MAXN][MAXN];
bool used[MAXN];
int N,M;

int main(int argc,char *argv[])
{
	if (argc==1)
	{
		printf("Usage .in .ans .out");
		return 0;
	}
	FILE *in=fopen(argv[1],"r");
	FILE *ans=fopen(argv[2],"r");
	FILE *out=fopen(argv[3],"r");
	fscanf(in,"%d%d",&N,&M);
	while(M--)
	{
		int a,b;
		fscanf(in,"%d%d",&a,&b);
		map[b][a]=map[a][b]=true;
	}
	for(int i=0,a;i<N;i++)
		fscanf(ans,"%d",&a);
	int re;
	fscanf(ans,"%d",&re);
	for(int i=0;i<re;i++)
	{
		char str[MAXN*10];
		fgets(str,MAXN*10,out);
		stringstream strin(str);
		int u,v;
		strin>>u;
		used[u]=true;
		while(strin>>v)
		{
			if (!map[u][v])
			{
				printf("wrong!\n");
				return 0;
			}
			used[u=v]=true;
		}
	}
	int ore;
	fscanf(out,"%d",&ore);
	if (ore!=re)
	{
		printf("wrong answer!\n");
		return 0;
	}
	for(int i=1;i<=N;i++)
		if (!used[i])
		{
			printf("Forget %d\n",i);
			return 0;
		}
	printf("Accepted!\n");
	return 0;
}
