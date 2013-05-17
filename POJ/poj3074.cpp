/*
ID: dxmtb
PROG: poj3074 Sudoku
TIME: 2011.03.01
STATE: Solved
MEMO: dancing links
*/
#include <cstdio>
#include <cstring>

const int N=9,H=9*9*9,W=9*9*4;
const int MAXM=(H+1)*(W+1);
const int oo=0x7fffffff;
const int Z[9][9]={
	{0,0,0,1,1,1,2,2,2},
	{0,0,0,1,1,1,2,2,2},
	{0,0,0,1,1,1,2,2,2},
	{3,3,3,4,4,4,5,5,5},
	{3,3,3,4,4,4,5,5,5},
	{3,3,3,4,4,4,5,5,5},
	{6,6,6,7,7,7,8,8,8},
	{6,6,6,7,7,7,8,8,8},
	{6,6,6,7,7,7,8,8,8}};

int g[N][N];
int A[H+1][W+1];
int head;
int R[MAXM],L[MAXM],U[MAXM],D[MAXM],C[MAXM],Row[MAXM];
int S[W+1];

int path[N*N],dep;
void getscore()
{
	for(int i=0;i<dep;i++)
	{
		int t1,t2,t3,t4;
		t1=Row[path[i]];
		t2=t1%9;
		if (t2==0) t2=9;
		t3=(t1-1)/81;
		t4=(t1-t3*81-1)/9;
		g[t3][t4]=t2;
	}
	for(int i=0;i<N;i++)
	{
		for(int j=0;j<N;j++)
			printf("%d",g[i][j]);
	}
	printf("\n");
}

void remove(int col)
{
	L[R[col]]=L[col];R[L[col]]=R[col];
	for(int i=D[col];i!=col;i=D[i])
		for(int j=R[i];j!=i;j=R[j])
			D[U[j]]=D[j],U[D[j]]=U[j],S[C[j]]--;
}

void resume(int col)
{
	for(int i=U[col];i!=col;i=U[i])
		for(int j=L[i];j!=i;j=L[j])
			D[U[j]]=j,U[D[j]]=j,S[C[j]]++;
	L[R[col]]=col;R[L[col]]=col;
}
bool dfs()
{
	if (R[head]==head)
	{
		getscore();
		return true;
	}
	int col,minsize=oo;
	for(int i=R[head];i!=head;i=R[i])
		if (S[i]<minsize)
			minsize=S[i],col=i;
	remove(col);
	for(int i=D[col];i!=col;i=D[i])
	{
		for(int j=R[i];j!=i;j=R[j])
			remove(C[j]);
		path[dep]=i;
		dep++;
		if (dfs())
			return true;
		dep--;
		for(int j=L[i];j!=i;j=L[j])
			resume(C[j]);
	}
	resume(col);
	return false;
}

int main()
{
	char str[82];
	while(scanf("%s",str)!=EOF)
	{
		if (str[0]=='e')
			break;
#define clear(x) memset((x),0,sizeof(x))
		clear(R);clear(L);
		clear(U);clear(D);
		clear(C);clear(Row);
		clear(S);clear(A);clear(g);
		head=0;R[W]=head;L[head]=W;
		for(int i=1;i<=W;i++)
			R[i-1]=i,L[i]=i-1;
		for(int x=0,t1=1,t2=W+1;x<N;x++)
			for(int y=0;y<N;y++)
				for(int num=1;num<=9;num++)
				{
					Row[t2]=t1;
					A[t1][x*9+num]=t2++;
					Row[t2]=t1;
					A[t1][81+y*9+num]=t2++;
					Row[t2]=t1;
					A[t1][81+81+Z[x][y]*9+num]=t2++;
					Row[t2]=t1;
					A[t1][81*3+x*9+y+1]=t2++;
					t1++;
				}
		for(int i=1;i<=H;i++)
		{
			int k=0,h,t;
			for(int j=1;j<=W;j++)
				if ((t=A[i][j]))
				{
					if (k) L[t]=k,R[k]=t;
					else h=t;
					k=t;
					S[j]++;C[t]=j;
				}
			R[k]=h;L[h]=k;
		}
		for(int j=1;j<=W;j++)
		{
			int k=j,t;
			for(int i=1;i<=H;i++)
				if ((t=A[i][j]))
				{
					U[t]=k,D[k]=t;
					k=t;
				}
			U[j]=k;D[k]=j;
		}
		for(int i=0;i<N;i++)
			for(int j=0;j<N;j++)
			{
				if (str[i*9+j]!='.')
				{
					g[i][j]=str[i*9+j]-'0';
					remove(i*9+g[i][j]);
					remove(81+j*9+g[i][j]);
					remove(81*2+Z[i][j]*9+g[i][j]);
					remove(81*3+i*9+j+1);
				}
			}
		dep=0;
		dfs();
	}
	return 0;
}
