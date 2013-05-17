#include <cstdio>
#include <cstring>
#include <sstream>
using namespace std;

const int MAXN=300;

int m,n;
int total[MAXN],c[MAXN];
char str[MAXN*10];

int main(int argc,char **argv)
{
	FILE *fin=fopen(argv[1],"r");
	FILE *fout=fopen(argv[2],"r");
	FILE *fans=fopen(argv[3],"r");
	for(int i=1;i<=m;i++)
		fscanf(fin,"%d",total+i);
	for(int i=1;i<=n;i++)
		fscanf(fin,"%d",c+i);
	int tmp1,tmp2;
	fscanf(fans,"%d",&tmp1);
	fscanf(fout,"%d",&tmp2);
	if (tmp1!=tmp2)
	{
		printf("Wrong at first line!\n");
		return 0;
	}
	bool used[MAXN];
	for(int i=1;i<=m;i++)
	{
		memset(used,false,sizeof(used));
		fgets(str,sizeof(str),fout);
		stringstream lin(str);
		int j=0;
		while(lin>>tmp1)
		{
			j++;
			if (j>total[i])
			{
				printf("Exceeded at %d\n",i);
				return 0;
			}
			if (used[tmp1])
			{
				printf("%d hs been used\n",tmp1);
				return 0;
			}
			c[tmp1]--;
			if (c[tmp1]<0)
			{
				printf("%d overused",tmp1);
				return 0;
			}
		}
	}
	printf("Accepted!\n");
	return 0;
}
