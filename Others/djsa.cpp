#include <cstdio>
#include <string>
using namespace std;

const int MAX=10000,MAXN=1000;

FILE *fin=fopen("djsa.in","r");
FILE *fout=fopen("djsa.out","w");

int n,m,d[MAXN][MAXN],w[MAXN][MAXN];

int main()
{
	for(int i=0;i<MAXN;i++)
		for(int j=0;j<MAXN;j++)
		{
			d[i][j]=MAX;
			w[i][j]=MAX;
		}
	for(int i=0;i<MAXN;i++)
	{
		d[i][i]=0;
		w[i][i]=0;
	}
	fscanf(fin,"%d%d",&n,&m);
	fscanf(fin,"%*[^\n]");
	for(int i=1;i<=m;i++)
	{
		int x,y,z;
		fscanf(fin,"%d%d%d",&x,&y,&z);
		w[x][y]=z;
		d[x][y]=z;
		w[y][x]=z;
		d[y][x]=z;
	}
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
				for(int k=0;k<n;k++)
					if (d[i][k]+d[k][j]<d[i][j])
						d[i][j]=d[i][k]+d[k][j];
	int min=MAX,p=MAX;
	for(int i=0;i<n;i++)
	{
		int s=0;
		for(int j=0;j<n;j++)
			if (d[j][i]>s)
				s=d[j][i];
		if (s<min)
		{
			min=s;
			p=i;
		}
	}
	fprintf(fout,"%d\n",p);
	return 0;
}
