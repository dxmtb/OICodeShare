/*
 * Problem: [JSOI2008]最大数maxnumber 
 * Time: 2011.05.12
 * Author: dxmtb
 * State: Solved
 * Memo: 优先队列+二分查找
*/
#include <cstdio>
#include <cassert>
#include <algorithm>
#include <vector>
using namespace std;

const int MAXN=200005;

int N,D;
vector<int> v;
int q[MAXN],size;

void insert(int num,int ind)
{
	while(size && q[size-1]<=num)
	{
		v.pop_back();
		size--;
	}
	q[size++]=num;
	v.push_back(ind);
}

int find(int ind)
{
	vector<int>::iterator it=lower_bound(v.begin(),v.end(),ind);
	int pos=it-v.begin();
	printf("%d\n",q[pos]);
	return q[pos];
}

int main()
{
	freopen("1012.in","r",stdin);
	scanf("%d%d",&N,&D);
	long long t=0;
	size=0;
	int tot=0;
	while(N--)
	{
		char c;
		int d;
		scanf(" %c%d",&c,&d);
		if (c=='Q')
			t=find(tot-d);
		else
		{
			assert(c=='A');
			insert((t+d)%D,tot++);
		}
	}
	return 0;
}
