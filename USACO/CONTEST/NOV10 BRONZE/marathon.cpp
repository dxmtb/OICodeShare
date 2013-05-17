/*
PROG: marathon
LANG: C++
ID: dxmtb1
*/
#include <cstdio>
#include <algorithm>
using namespace std;

const int MAXN=5005;

struct Node
{
	int a,b,c;
}t[MAXN];

inline bool operator < (const Node &u,const Node &v)
{
	return ((u.a<v.a)||(u.a==v.a&&u.b<v.b)||(u.a==v.a&&u.b==v.b&&u.c<v.c));
}

int N;

int main()
{
	freopen("marathon.in","r",stdin);
	freopen("marathon.out","w",stdout);
	scanf("%d",&N);
	for(int i=0;i<N;i++)
		scanf("%d%d%d",&t[i].a,&t[i].b,&t[i].c);
	sort(t,t+N);
	for(int i=0;i<N;i++)
		printf("%d %d %d\n",t[i].a,t[i].b,t[i].c);
}
