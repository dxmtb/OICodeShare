/*
ID: dxmtb
PROG: USACO lines
TIME: 2010.4.25
STATE: Solved
MEMO: Ã¶¾Ù+Î°´óµÄrb-tree
*/
#include <cstdio>
#include <cmath>
#include <set>
using namespace std;

const int MAXN=200,oo=0x7fffffff;
const double small=0.0000001;

int n,x[MAXN],y[MAXN],num=0;
set<double> hash;

void init()
{
	scanf("%d",&n);
	for(int i=0;i<n;i++)
		scanf("%d%d",&x[i],&y[i]);
}

bool cmp(double a,double b)
{
	if (abs(a-b)<small)
		return true;
	else return false;
}

int main() 
{
	freopen("lines.in","r",stdin);
	freopen("lines.out","w",stdout);	
	init();
	for(int i=0;i<n;i++)
		for(int j=i+1;j<n;j++)
		{
			double K;
			if (x[i]-x[j]!=0)
				K=double(y[i]-y[j])/(x[i]-x[j]);
			else K=oo;
			if (hash.find(K)==hash.end())
			{
				num++;
				hash.insert(K);
			}
		}
	printf("%d\n",num);
	return 0;
}
