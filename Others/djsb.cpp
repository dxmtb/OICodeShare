#include <cstdio>
#include <string>
using namespace std;

const int MAX=10000,MAXN=1000;

FILE *fin=fopen("djsb.in","r");
FILE *fout=fopen("djsb.out","w");

int n,m,d[MAXN][MAXN],w[MAXN][MAXN];

int mini(int a,int b)
{return a<b?a:b;}

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
	int min=MAX,p1=MAX,p2=MAX;
	for(int i=0;i<n;i++)
		for(int k=i+1;k<n;k++)
		{
			int s=0;
			for(int j=0;j<n;j++)
				if (mini(d[j][k],d[j][i])>s)
					s=mini(d[j][k],d[j][i]);
			if (s<min)
			{
				min=s;
				p1=i;
				p2=k;
			}
		}
	fprintf(fout,"%d %d\n",p1,p2);
	return 0;
}
