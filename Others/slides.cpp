#include <cstdio>
#include <cstring>
using namespace std;

const int MAXN=26;

int mat[MAXN],mat2[MAXN],match=0;
bool g[MAXN][MAXN],used[MAXN];
int n;
int xmin[MAXN],xmax[MAXN],ymin[MAXN],ymax[MAXN];

void init()
{
	scanf("%d",&n);
	for(int i=0;i<n;i++)
		scanf("%d%d%d%d",&xmin[i],&xmax[i],&ymin[i],&ymax[i]);
	for(int i=0;i<n;i++)
	{
		int a,b;
		scanf("%d%d",&a,&b);
		for(int j=0;j<n;j++)
			if (a>=xmin[j]&&a<=xmax[j]&&b>=ymin[j]&&b<=ymax[j])
				g[i][j]=true;
	}
}

bool cross(int cur)
{
	for(int i=0;i<n;i++)
		if (g[cur][i]&&!used[i])
		{
			used[i]=true;
			if (mat[i]==-1||cross(mat[i]))
			{
				mat[i]=cur;
				return true;
			}
		}
	return false;
}

void hungary()
{
	memset(mat,-1,sizeof(mat));
	match=0;
	for(int i=0;i<n;i++)
	{
		memset(used,false,sizeof(used));
		if (cross(i))
			match++;
	}
}

int main()
{
	freopen("slides.in","r",stdin);
	freopen("slides.out","w",stdout);
	init();
	hungary();
	if (match<n)printf("None");
	else
	{
		for(int i=0;i<n;i++)mat2[i]=mat[i];
		for(int i=0;i<n;i++)
		{
			g[mat2[i]][i]=false;
			hungary();
			if (match==n)
			{
				printf("None");
				return 0;
			}
			g[mat2[i]][i]=true;
		}
		hungary();
		for(int i=0;i<n;i++)
			printf("%c %d\n",'A'+i,mat[i]+1);
	}
	return 0;
}
