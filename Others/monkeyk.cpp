/*
ID: dxmtb
PROG: 爱争吵的猴子
TIME: 2010.01.02
STATE: Solved
MEMO: 二项堆
*/
#include <cstdio>
#include <algorithm>
const int MAXN=100005;

struct Node
{
	int key,degree;
	int child,sibling;
	Node(int A=0,int B=0,int C=0,int D=0):
		key(A),degree(B),child(C),sibling(D){}
}mem[MAXN];

int Heap[MAXN];

inline void Link(int x,int y)
{
	if (mem[x].key<mem[y].key)
	{
		std::swap(mem[x].key,mem[y].key);
		std::swap(mem[x].degree,mem[y].degree);
		std::swap(mem[x].child,mem[y].child);
	}
	mem[x].sibling=mem[y].sibling;
	mem[y].sibling=mem[x].child;
	mem[x].child=y;
	mem[x].degree++;
}
inline int Maximum(const int &head)
{
	int ans=0;
	for(int p=head;p;p=mem[p].sibling)
		if (!ans||mem[p].key>mem[ans].key)
			ans=p;
	return ans;
}

inline int del(int &head,int h)
{
	int Now=mem[h].child;
	if (head==h)
		head=mem[head].sibling;
	else
	for(int p=head;p&&mem[p].sibling;p=mem[p].sibling)
		if (mem[p].sibling==h)
			mem[p].sibling=mem[h].sibling;
	mem[h].child=mem[h].sibling=NULL;
	mem[h].degree=0;
	return Now;
}

inline bool isEmpty(const int &H)
{
	return H==0;
}

inline void Merge(int &Now,const int &H1,const int &H2)
{
	if (isEmpty(H1)&&isEmpty(H2))
		Now=NULL;
	if (isEmpty(H1))
		Now=H2;
	if (isEmpty(H2))
		Now=H1;
	int p1=H1,p2=H2,*p=&Now;
	while(p1&&p2)
	{
		if (mem[p1].degree>=mem[p2].degree)
			*p=p1,p1=mem[p1].sibling,p=&mem[(*p)].sibling;
		else 
			*p=p2,p2=mem[p2].sibling,p=&mem[(*p)].sibling;
	}
	if (p1)
	{
		while(p1)
			*p=p1,p1=mem[p1].sibling,p=&mem[(*p)].sibling;
	}
	else if (p2)
	{
		while(p2)
			*p=p2,p2=mem[p2].sibling,p=&mem[(*p)].sibling;
	}
	*p=NULL;
}

inline int Union(const int &H1,const int &H2)
{
	if (isEmpty(H1)&&isEmpty(H2))
		return NULL;
	if (isEmpty(H1))
		return H2;
	if (isEmpty(H2))
		return H1;
	int Now=NULL;
	Merge(Now,H1,H2);
	if (Now)
	for(int p=Now;p&&mem[p].sibling;p=mem[p].sibling)
		while (mem[p].sibling&&mem[mem[p].sibling].degree==mem[p].degree
		    &&((!mem[mem[p].sibling].sibling)||
		    mem[mem[mem[p].sibling].sibling].degree!=mem[p].degree))
			Link(p,mem[p].sibling);
	return Now;
}

inline int insert(int head,int h)
{
	return Union(head,h);
}


int N,M;

int father[MAXN];

inline int getfather(int u)
{
	if (father[u]==u)
		return u;
	return father[u]=getfather(father[u]);
}
inline void judge(int x,int y)
{
	int fx=getfather(x),fy=getfather(y);
	father[fy]=fx;
}
inline bool same(int x,int y)
{
	return getfather(x)==getfather(y);
}

int main()
{
	freopen("monkeyk.in","r",stdin);
	freopen("monkeyk.out","w",stdout);
	scanf("%d",&N);
	for(int i=1;i<=N;i++)
	{
		father[i]=i;
		scanf("%d",&mem[i].key);
		Heap[i]=i;
	}
	scanf("%d",&M);
	while(M--)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		if (same(x,y)) printf("-1\n");
		else
		{
			int fx=getfather(x),fy=getfather(y);
			judge(fx,fy);
			
			int t;
			int p=Maximum(Heap[fx]);
			t=del(Heap[fx],p);
			Heap[fx]=Union(t,Heap[fx]);
			mem[p].key/=2;
			Heap[fx]=insert(Heap[fx],p);
			p=Maximum(Heap[fy]);
			
			t=del(Heap[fy],p);
			Heap[fy]=Union(t,Heap[fy]);
			mem[p].key/=2;
			Heap[fy]=insert(Heap[fy],p);
			
			Heap[fx]=Union(Heap[fx],Heap[fy]);
			Heap[fy]=NULL;
			printf("%d\n",mem[Maximum(Heap[fx])].key);
		}
	}
	return 0;
}
