/*
ID: dxmtb1
PROG: shopping
LANG: C++
*/
#include <cstdio>
#include <vector>
#include <cstring>
using namespace std;
const int MAXN=6,MAXS=1011;
const int oo=0x7fffffff;

vector<int> hs[MAXS],hn[MAXS];//hs存商品。hn存个数
int hj[MAXS];//优惠后价钱
int c[MAXS],k[MAXS],p[MAXS];//需要商品，个数，原价
int s,b;
int d[MAXN+1][MAXN+1][MAXN+1][MAXN+1][MAXN+1];
int used[MAXS+1];

int main()
{
	freopen("shopping.in","r",stdin);
	freopen("shopping.out","w",stdout);
	memset(used,-1,sizeof(used));
	scanf("%d",&s);
	for(int i=0;i<s;i++)
	{
		int n;
		scanf("%d",&n);
		for(int j=0;j<n;j++)
		{
			int c,k;
			scanf("%d%d",&c,&k);
			hs[i].push_back(c);
			hn[i].push_back(k);
		}
		scanf("%d",hj+i);
	}
	scanf("%d",&b);
	for(int i=0;i<b;i++)
	{
		scanf("%d%d%d",c+i,k+i,p+i);
		used[c[i]]=i;
	}
	for(int i=0;i<=k[0];i++)
		for(int j=0;j<=k[1];j++)
			for(int a=0;a<=k[2];a++)
				for(int b=0;b<=k[3];b++)
					for(int c=0;c<=k[4];c++)
						d[i][j][a][b][c]=p[0]*i+p[1]*j+p[2]*a+p[3]*b+p[4]*c;
	for(int i=0;i<=k[0];i++)
		for(int j=0;j<=k[1];j++)
			for(int a=0;a<=k[2];a++)
				for(int b=0;b<=k[3];b++)
					for(int c=0;c<=k[4];c++)
					{
						for(int f=0;f<s;f++)
						{
							int t[5]={i,j,a,b,c};
							bool flag=true;
							for(unsigned e=0;e<hs[f].size();e++)
							{
								int temp=hs[f][e];
								if (used[temp]==-1)
								{
									flag=false;
									break;
								}
								t[used[temp]]-=hn[f][e];
							}
							if (!flag)continue;
							for(int e=0;e<5;e++)
								if (t[e]<0)
								{
									flag=false;
									break;
								}
							if (!flag)continue;
							int temp=d[t[0]][t[1]][t[2]][t[3]][t[4]]+hj[f];
							if (temp<d[i][j][a][b][c])
								d[i][j][a][b][c]=temp;
						}
					}
//	printf("%d\n",d[2][0][0][0][0]);
	printf("%d\n",d[k[0]][k[1]][k[2]][k[3]][k[4]]);
	return 0;
}
