/*
 * Problem: poj3375 Network Connection
 * Time: 2011.07.07
 * Author: dxmtb
 * State: Solved
 * Memo: dp+决策优化
*/
#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int MAXM=100005,MAXN=2005;
const int oo=~0u>>1;

int d[2][MAXM];
int N,M,re=oo;
int A[MAXN],B[MAXM];
int P[MAXN];
int L[MAXN],R[MAXN];

inline void Min(int &a,int b)
{
	if (b<a) a=b;
}

int main()
{
	scanf("%d%d",&M,&N);
	for(int i=1;i<=M;i++)
		scanf("%d",B+i);
	for(int i=1;i<=N;i++)
		scanf("%d",A+i);
	sort(A+1,A+1+N);
	sort(B+1,B+1+M);
	for(int i=1,k=1;i<=N;i++)
	{
		while(abs(A[i]-B[k])>=abs(A[i]-B[k+1]))
			k++;
		P[i]=k;
	}
	L[1]=max(1,P[1]-N),R[1]=min(P[1]+N,M-(N-1));
	d[1][1]=abs(A[1]-B[1]);
	for(int j=2;j<=R[1];j++)
		d[1][j]=min(d[1][j-1],abs(A[1]-B[j]));
	for(int i=2;i<=N;i++)
	{
		L[i]=max(i,P[i]-N),R[i]=min(P[i]+N,M-(N-i));
		int *f=d[i&1],*g=d[(i&1)^1];
		for(int j=L[i];j<=R[i];j++)
		{
			f[j]=oo;
			int k=min(j-1,R[i-1]);
			if (k>=L[i-1] && g[k]!=oo)
				Min(f[j],g[k]+abs(A[i]-B[j]));
			if (j!=L[i])
				Min(f[j],f[j-1]);
			if (i==N && f[j]<re)
				re=f[j];
		}
	}
	printf("%d\n",re);
	return 0;
}
