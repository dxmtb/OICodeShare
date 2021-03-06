/*
ID: dxmtb
PROG: hust1017 Exact cover
TIME: 2011.03.01
STATE: Solved
MEMO: dancing links
*/
#include <cstdio>
#include <cstring>
const int MAXN=1005,MAXM=MAXN*100;
const int oo=0x7fffffff;

int C[MAXM],Row[MAXM];
int R[MAXM],L[MAXM],U[MAXM],D[MAXM];
int S[MAXN];

int N,M,head;
int A[MAXN][MAXN];

inline void remove(int col)
{
	L[R[col]]=L[col];
	R[L[col]]=R[col];
	for(int i=D[col];i!=col;i=D[i])
	{
		for(int j=R[i];j!=i;j=R[j])
			U[D[j]]=U[j],D[U[j]]=D[j],S[C[j]]--;
	}
}

inline void resume(int col)
{
	for(int i=U[col];i!=col;i=U[i])
	{
		for(int j=L[i];j!=i;j=L[j])
			U[D[j]]=j,D[U[j]]=j,S[C[j]]++;
	}
	L[R[col]]=col;
	R[L[col]]=col;
}

int path[MAXN];
bool dfs(int dep)
{
	if (R[head]==head)
	{
		printf("%d",dep);
		for(int i=0;i<dep;i++)
			printf(" %d",Row[path[i]]);
		printf("\n");
		return true;
	}
	int minsize=oo,col;
	for(int i=R[head];i!=head;i=R[i])
		if (S[i]<minsize)
			minsize=S[i],col=i;
	remove(col);
	for(int i=D[col];i!=col;i=D[i])
	{
		path[dep]=i;
		for(int j=R[i];j!=i;j=R[j])
			remove(C[j]);
		if (dfs(dep+1))
			return true;
		for(int j=L[i];j!=i;j=L[j])
			resume(C[j]);
	}
	resume(col);
	return false;
}

int main()
{
	while(scanf("%d%d",&N,&M)!=EOF)
	{
		if (N==0 || M==0)
			break;
#define clear(x) memset((x),0,sizeof(x))
		clear(A);clear(R);clear(L);
		clear(U);clear(D);clear(S);
		head=0;
		L[head]=M;R[head]=1;
		R[M]=head;
		for(int i=1;i<M;i++)
			R[i]=i+1,L[i+1]=i;
		for(int i=1,t=M+1;i<=N;i++)
		{
			int T;
			scanf("%d",&T);
			while(T--)
			{
				int j;
				scanf("%d",&j);
				C[t]=j;
				Row[t]=i;
				A[i][j]=t++;
				S[j]++;
			}
		}
		for(int i=1,t;i<=N;i++)
		{
			int k=0,h=0;
			for(int j=1;j<=M;j++)
				if ((t=A[i][j]))
				{
					if (k) L[t]=k,R[k]=t;
					else h=t;
					k=A[i][j];
				}
			R[k]=h;L[h]=k;
		}
		for(int j=1;j<=M;j++)
		{
			int k=j;
			for(int i=1;i<=N;i++)
				if (A[i][j])
				{
					U[A[i][j]]=k,D[k]=A[i][j];
					k=A[i][j];
				}
			U[j]=k;D[k]=j;
		}
		if (!dfs(0))
			printf("NO\n");
	}
	return 0;
}
