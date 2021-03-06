/*
ID: dxmtb
PROG: [SCOI2009]迷路 
TIME: 2011.03.24
STATE: Solved
MEMO: 递推+矩阵乘法
*/
#include <cstdio>
#include <cstring>
#include <cassert>

const int MAXN=95;
const int P=2009;

struct Node
{
	int v;
	Node *next;
	Node (int _v,Node *_next):v(_v),next(_next){}
	Node(){}
	void *operator new (unsigned ,void *p){return p;}
}*adj[MAXN],pool[MAXN*MAXN],*mem=pool;

inline void addedge(const int &u,const int &v)
{
	adj[u]=new (mem++)Node(v,adj[u]);
}

struct Matrix
{
	int R,C;
	int a[MAXN][MAXN];
	void init(int _R,int _C)
	{
		R=_R,C=_C;
		memset(a,0,sizeof(a));
	}
	Matrix(){}
	Matrix(int _R,int _C)
	{
		init(_R,_C);
	}
}A,B;

Matrix operator *(const Matrix &a,const Matrix &b)
{
	assert(a.C==b.R);
	Matrix c(a.R,b.C);
	for(int i=0;i<c.R;i++)
		for(int j=0;j<c.C;j++)
			for(int k=0;k<a.C;k++)
				c.a[i][j]=(c.a[i][j]+a.a[i][k]*b.a[k][j])%P;
	return c;
}

Matrix pow(Matrix a,int N)
{
	assert(N>0);
	Matrix b=a;
	while((N&1)==0)
	{
		b=b*b;
		N>>=1;
	}
	a=b;
	N>>=1;
	while(N)
	{
		b=b*b;
		if (N&1)
			a=a*b;
		N>>=1;
	}
	return a;
}

char str[MAXN][MAXN];
int U[MAXN][9],size[MAXN];

int N,T;
int main()
{
	freopen("1297.in","r",stdin);
	scanf("%d%d",&N,&T);
	for(int i=0;i<N;i++)
		scanf(" %s",str[i]);
	int tot=N;
	for(int j=0;j<N;j++)
	{
		U[j][0]=j;	
		size[j]=1;
		for(int i=0;i<N;i++)
		{
			str[i][j]-='0';
			if (str[i][j])
			{
				if (str[i][j]>size[j])
				{
					for(int k=size[j];k<str[i][j];k++)
					{
						U[j][k]=tot++;
						addedge(U[j][k],U[j][k-1]);
					}
					size[j]=str[i][j];
				}
				addedge(i,U[j][str[i][j]-1]);
			}
		}
	}
	B.init(tot,tot);
	for(int i=0;i<tot;i++)
		for(Node *p=adj[i];p;p=p->next)
			B.a[i][p->v]=1;
	A.init(1,tot);
	A.a[0][0]=1;
	Matrix C=A*pow(B,T);
	printf("%d\n",C.a[0][N-1]);
	return 0;
}
