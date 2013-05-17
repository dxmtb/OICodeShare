#include <cstdio>
#include <cstring>
#include <sstream>
#include <set>
using namespace std;

const int MAXN=3000;

int K,N;
int need[MAXN];
char str[MAXN];
set<int> s[MAXN];
int main(int argc,char **argv)
{
	FILE *fin=fopen(argv[1],"r");
	FILE *fout=fopen(argv[2],"r");
	FILE *fans=fopen(argv[3],"r");
	fscanf(fin,"%d%d",&K,&N);
	for(int i=1;i<=K;i++)
		fscanf(fin,"%d",need+i);
	for(int i=1;i<=N;i++)
	{
		int p;
		fscanf(fin,"%d",&p);
		while(p--)
		{
			int a;
			fscanf(fin,"%d",&a);
			s[a].insert(i);
		}
	}
	fgets(str,sizeof(str),fans);
	str[12]=0;
	if (strcmp(str,"No Solution!")==0)
	{
		fgets(str,sizeof(str),fout);
		str[12]=0;
		if (strcmp(str,"No Solution!")==0)
			printf("Accepted!\n");
		else printf("Wrong Answer!\n");
		return 0;
	}
	else
	{
		bool used[MAXN];
		memset(used,false,sizeof(used));
		for(int i=1;i<=K;i++)
		{
			fgets(str,sizeof(str),fout);
			stringstream lin(str);
			int tmp;
			char chr;
			lin>>tmp>>chr;
			for(int j=1;j<=need[i];j++)
			{
				lin>>tmp;
				if (used[tmp]||s[i].find(tmp)==s[i].end())
				{
					printf("Exception at %d\n",i);
					return 0;
				}
				used[tmp]=true;
			}
		}
	}
	printf("Accepted!\n");
	return 0;
}
