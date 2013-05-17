/*
 * Problem: 山顶问题
 * Time: 2011.04.12
 * Author: dxmtb
 * State: Solved
 * Memo: 贪心
*/
#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;
const int MAXN=100005;
const long long oo=~0ull>>2;

struct Node
{
	long long w;
	int l,r;
	Node(long long _w,int _l,int _r):
		w(_w),l(_l),r(_r){}
};
int tot;
vector<Node> v;

void push_heap(const Node &a)
{
	v.push_back(a);
	tot++;
}

int N,K;
long long H[MAXN];

long long getsum(int l,int r)
{
	long long to=max(H[l],H[r]);
	long long ans=0;
	for(int i=l;i<=r;i++)
		if (H[i]>to)
			ans+=H[i]-to;
	return ans;
}

long long pop_heap()
{
	long long minw=oo;
	int ri;
	for(int i=0;i<tot;i++)
		if (v[i].w<minw)
			minw=v[i].w,ri=i;
	long long to=max(H[v[ri].l],H[v[ri].r]);
	for(int i=v[ri].l;i<=v[ri].r;i++)
		if (H[i]>to)
			H[i]=to;
	if (H[v[ri].l]>=H[v[ri].r])
	{
		v[ri-1].r=v[ri].r;
		v[ri-1].w=getsum(v[ri-1].l,v[ri-1].r);
	}
	else
	{
		v[ri+1].l=v[ri].l;
		v[ri+1].w=getsum(v[ri+1].l,v[ri+1].r);
	}
	v.erase(v.begin()+ri);
	tot--;
	return minw;
}

int main()
{
	freopen("peaks.in","r",stdin);
	freopen("peaks.out","w",stdout);
	scanf("%d%d",&N,&K);
	for(int i=1;i<=N;i++)
		scanf("%d",H+i);
	H[0]=0;
	H[++N]=0;
	for(int i=1,j=0,l=0;i<=N;i++)
	{
		if (H[i]!=H[i-1])
		{
			if (j==0)
			{
				if (H[i]<H[i-1])
					j=1;
			}
			else
			{
				if (H[i]>H[i-1])
				{
					push_heap(Node(getsum(l,i-1),l,i-1));
					j=0;l=i-1;
				}
			}
		}
		if (i==N)
			push_heap(Node(getsum(l,N),l,N));
	}
	long long re=0;
	while(tot>K)
		re+=pop_heap();
	cout<<re<<endl;
	return 0;
}
