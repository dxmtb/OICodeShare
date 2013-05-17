/*
 * Problem: poj2778 DNA Sequence
 * Time: 2011.07.14
 * Author: dxmtb
 * State: Solved
 * Memo: AC自动机 + 矩阵乘法
*/
#include <iostream>
#include <queue>
#include <cstring>
using namespace std;

typedef long long s64;
const int MAXM=15,MAXN=MAXM*MAXM;
const int MO=100000;

struct Node
{
	int ch;
	Node *c[4],*next,*father;
	bool end;
	Node(int _ch=-1)
	{
		ch=_ch;
		memset(c,0,sizeof(c));
		next=NULL;
		end=false;
	}
	void *operator new (size_t,void *p){return p;}
}pool[MAXN],*mem=pool;

void addedge(Node*,Node *);

struct Trie
{
	Node *root;
	Trie()
	{
		root=new (mem++)Node(-1);
		root->next=root;
		root->father=NULL;
	}
	void insert(char *str,const int &n)
	{
		Node *p=root;
		for(int i=0;i<n;i++)
		{
			if (p->end)
				return ;
			int ch=str[i];
			if (p->c[ch]==NULL)
			{
				p->c[ch]=new (mem++)Node(ch);
				p->c[ch]->father=p;
			}
			p=p->c[ch];
		}
		p->end=true;
	}
	void update()
	{
		queue<Node*> q;
		q.push(root);
		while(q.size())
		{
			Node *p1=q.front();q.pop();
			int ch=p1->ch;
			if (p1!=root && p1->father!=root)
			{
				Node *p2=p1->father->next;
				while(p2->c[ch]==NULL)
				{
					if (p2==root)
						break;
					p2=p2->next;
				}
				if (p2->c[ch]!=NULL)
					p1->next=p2->c[ch];
			}
			if (p1->next==NULL)
				p1->next=root;
			if (!p1->end)
			{
				for(int i=0;i<4;i++)
					if (p1->c[i]==NULL)
					{
						Node *p2=p1->next;
						while(p2!=root && p2->c[i]==NULL)
							p2=p2->next;
						if (p2->c[i]!=NULL)
							addedge(p1,p2->c[i]);
						else
							addedge(p1,root);
					}
					else
					{
						addedge(p1,p1->c[i]);
						q.push(p1->c[i]);
					}
			}
		}
	}
}tree;

struct Matrix
{
	int n,m;
	s64 data[MAXN][MAXN];
	const s64 *operator [] (int a) const 
	{
		return data[a];
	}
	s64 *operator [] (int a)
	{
		return data[a];
	}
	Matrix(int _n=0,int _m=0)
	{
		init(_n,_m);
	}
	void init(int _n,int _m)
	{
		n=_n,m=_m;
		memset(data,0,sizeof(data));
	}
}trans;

Matrix operator *(const Matrix &a,const Matrix &b)
{
	Matrix c(a.n,b.m);
	for(int i=0;i<c.n;i++)
		for(int j=0;j<c.m;j++)
		{
			for(int k=0;k<a.m;k++)
				c[i][j]=(c[i][j]+a[i][k]*b[k][j])%MO;
		}
	return c;
}

Matrix pow(Matrix a,s64 n)
{
	while((n&1)==0)
	{
		a=a*a;
		n>>=1;
	}
	Matrix b=a;
	n>>=1;
	while(n)
	{
		b=b*b;
		if (n&1)
			a=a*b;
		n>>=1;
	}
	return a;
}

void addedge(Node* a,Node* b)
{
	if (!b->end)
		trans[a-pool][b-pool]++;
}

s64 N;
char allstr[15][15];
bool use[15];
int main()
{
	int M;
	cin>>M>>N;
	for(int i=0;i<M;i++)
		cin>>allstr[i];
	for(int i=0;i<M;i++)
	{
		char *str=allstr[i];
		int L=strlen(str);
		if (L>N)
			continue;
		for(int j=0;j<M;j++)
			if (i!=j && strstr(str,allstr[j])!=NULL)
				goto OUT;
		use[i]=true;
OUT:;
	}
	for(int i=0;i<M;i++)
		if (use[i])
		{
			char *str=allstr[i];
			int L=strlen(str);
			for(int j=0;j<L;j++)
			{
				switch (str[j])
				{
					case 'A':str[j]=0;break;
					case 'C':str[j]=1;break;
					case 'T':str[j]=2;break;
					case 'G':str[j]=3;break;
					default:return -1;
				}
			}
			tree.insert(str,L);
		}
	trans.init(mem-pool,mem-pool);
	tree.update();
	Matrix now(1,mem-pool);
	now[0][0]=1;
	now=now*pow(trans,N);
	int re=0;
	for(int i=0;i<now.m;i++)
		if (!pool[i].end)
			re=(re+now[0][i])%MO;
	cout<<re<<endl;
	return 0;
}
