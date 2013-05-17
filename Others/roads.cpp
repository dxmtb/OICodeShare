/*
ID: dxmtb
PROG: 建造路径
TIME: 2010.10.23
STATE: Solved
MEMO: 最小生成树
*/
#include <cstdio>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN=1005;

struct Node
{
	int u,v;
	double data;
	Node (int a=0,int b=0,double c=0):u(a),v(b),data(c){}
};

bool operator < (const Node &a,const Node &b)
{
	return a.data>b.data;
}

int father[MAXN];
int getfather(int u)
{
	if (father[u]==u)
		return u;
	return father[u]=getfather(father[u]);
}

void judge(int a,int b)
{
	int x=getfather(a),y=getfather(b);
	if (x==y)
		return ;
	father[x]=y;
}

bool use[MAXN];
inline bool used(int i)
{
	if (use[i]) return true;
	use[i]=true;
	return false;
}

int n,m,need=-1;
int x[MAXN],y[MAXN];
double re;

inline double sqr(int x)
{
	return double(x)*x;
}

inline double dis(int u,int v)
{
	return sqrt(sqr(x[u]-x[v])+sqr(y[u]-y[v]));
}

vector<Node> v;

inline void push(int u1,int u2,double data)
{
	v.push_back(Node(u1,u2,data));
}

void getmin(Node &x)
{
	x=v.back();
}

void pop()
{
	v.pop_back();
}

int main()
{
	freopen("roads.in","r",stdin);
	freopen("roads.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%d%d",x+i,y+i);
	for(int i=1;i<=n;i++)
		father[i]=i;
	for(int i=0;i<m;i++)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		judge(u,v);
	}
	for(int i=1;i<=n;i++)
		if (!used(getfather(i)))
			need++;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			if (i!=j)
				push(i,j,dis(i,j));
	sort(v.begin(),v.end());
	while(need--)
	{
		Node ad;
		do{
			getmin(ad);
			pop();
		}while(getfather(ad.u)==getfather(ad.v));
		judge(ad.u,ad.v);
		re+=ad.data;
	}
	printf("%.2lf\n",re);
	return 0;
}
