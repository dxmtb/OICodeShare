/*
 * Problem: [HNOI2008]水平可见直线
 * Time: 2011.04.27
 * Author: dxmtb
 * State: Solved
 * Memo: 排序+维护类似凸包
*/
#include <cstdio>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
const int MAXN=50005;
const double eps=1e-9;

struct Line
{
	int A,B,ind;
}L[MAXN];

inline bool operator < (const Line &a,const Line &b)
{
	return a.A<b.A||(a.A==b.A && a.B<b.B);
}

double crossx(const Line &a,const Line &b)
{
	return double(b.B-a.B)/(a.A-b.A);
}

int N;

void init()
{
	scanf("%d",&N);
	for(int i=0;i<N;i++)
	{
		scanf("%d%d",&L[i].A,&L[i].B);
		L[i].ind=i+1;
	}
	if (N==1)
	{
		printf("1\n");
		exit(0);
	}
	sort(L,L+N);
	int j=0;
	for(int i=1;i<N;i++)
		if (L[i].A!=L[i-1].A)
			L[j++]=L[i-1];
	L[j++]=L[N-1];
	N=j;
}

int sgn(double t)
{
	if (fabs(t)<eps) return 0;
	if (t>0) return 1;
	else return -1;
}

void solve()
{
	static Line *stack[MAXN]={L,L+1};
	int size=2;
	for(int i=2;i<N;i++)
	{
		while(size>=2 && sgn(crossx(*stack[size-1],*stack[size-2])-crossx(*stack[size-1],L[i]))>=0)
			size--;
		stack[size++]=L+i;
	}
	vector<int> v;
	for(int i=0;i<size;i++)
		v.push_back(stack[i]->ind);
	sort(v.begin(),v.end());
	printf("%d",v[0]);
	for(int i=1;i<size;i++)
		printf(" %d",v[i]);
	printf("\n");
}

int main()
{
	freopen("1007.in","r",stdin);
	init();
	solve();
	return 0;
}
