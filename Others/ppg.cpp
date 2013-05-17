/*
ID: dxmtb
PROG: 扩散
TIME: 2010.11.18
STATE: Solved
MEMO: 模拟
*/
#include <cstdio>
#include <vector>
#include <cstdlib>
#include <algorithm>
using namespace std;
const int MAXN=50;
struct Node
{
	int dis;
	int u,v;
	Node(int a,int b,int c):dis(a),u(b),v(c){}
};

vector<Node> v;

bool operator < (const Node &a,const Node &b)
{
	return a.dis<b.dis;
}

int father[MAXN];
inline int getfather(int u)
{
	if (father[u]==u) return u;
	return father[u]=getfather(father[u]);
}
inline void judge(int x,int y)
{
	int fx=getfather(x),fy=getfather(y);
	father[fx]=fy;
}

int n,x[MAXN],y[MAXN],re;

int main()
{
	freopen("ppg.in","r",stdin);
	freopen("ppg.out","w",stdout);
	scanf("%d",&n);
	for(int i=0;i<n;i++)
		scanf("%d%d",x+i,y+i);
	for(int i=0;i<n;i++)
		father[i]=i;
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
		{
			int dis=(abs(x[i]-x[j])+abs(y[i]-y[j])+1)/2;
			v.push_back(Node(dis,i,j));
		}
	sort(v.begin(),v.end());
	for(vector<Node>::iterator it=v.begin();it!=v.end();it++)
	{
		if (getfather(it->u)!=getfather(it->v))
		{		
			re=it->dis;
			judge(it->u,it->v);
		}
	}
	printf("%d\n",re);
	return 0;
}
