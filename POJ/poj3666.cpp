/*
 * Problem: poj3666 Making the Grade
 * Time: 2011.07.16
 * Author: dxmtb
 * State: Solved
 * Memo: 贪心 + 左偏树
*/
#include <cstdio>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN=2005;

struct Node
{
	int key,dist,size;
	Node *c[2];
	void init(int _k);
	friend Node* merge(Node *p1,Node *p2);
}pool[MAXN],Tnull,*null=&Tnull;

void Node::init(int _k)
{
	key=_k,dist=0,size=1;
	c[0]=c[1]=null;
}

Node* merge(Node *p1,Node *p2)
{
	if (p1==null) return p2;
	if (p2==null) return p1;
	if (p1->key<p2->key)
		swap(p1,p2);
	p1->c[1]=merge(p1->c[1],p2);
	if (p1->c[0]->dist<p1->c[1]->dist)
		swap(p1->c[0],p1->c[1]);
	p1->dist=p1->c[1]->dist+1;
	p1->size=p1->c[0]->size+p1->c[1]->size+1;
	return p1;
}
struct Pair
{
	int l,r,k;
	Node *heap;
	Pair(int _l,int _r,int _k,Node *_heap):
		l(_l),r(_r),k(_k),heap(_heap){}
};

int N,A[MAXN];
int re=~0u>>1;
void solve()
{
	for(int i=0;i<N;i++)
		pool[i].init(A[i]);
	vector<Pair> q;
	q.push_back(Pair(0,0,A[0],&pool[0]));
	for(int i=1;i<N;i++)
	{
		Pair now(i,i,A[i],&pool[i]);
		Node *&p=now.heap;
		while (q.size() && now.k<q.back().k)
		{
			now.l=q.back().l;
			p=merge(p,q.back().heap);
			q.pop_back();
			int size=i-now.l+1;
			while(p->size>(int)ceil(size/2.0))
				p=merge(p->c[0],p->c[1]);
			now.k=p->key;
		}
		q.push_back(now);
	}
	int ans=0;
	for(int i=0,size=q.size();i<size;i++)
		for(int j=q[i].l;j<=q[i].r;j++)
			ans+=abs(A[j]-q[i].k);
	if (ans<re)
		re=ans;
}

int main()
{
	scanf("%d",&N);
	for(int i=0;i<N;i++)
		scanf("%d",A+i);
	null->dist=-1;
	solve();
	reverse(A,A+N);
	solve();
	printf("%d\n",re);
	return 0;
}
