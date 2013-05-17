/*
ID: dxmtb
PROG: HAOI 上升序列
TIME: 2011.03.14
STATE: Solved
MEMO: dp
*/
#include <cstdio>
#include <cstring>

const int MAXN=10005;
const int oo=0x7fffffff;

int a[MAXN],d[MAXN],K[MAXN];
int N,m;
int *v[MAXN],size[MAXN];
int A[MAXN];

int main()
{
	freopen("lis.in","r",stdin);
	freopen("lis.out","w",stdout);
	scanf("%d",&N);
	for(int i=1;i<=N;i++)
		scanf("%d\n",a+i);
	for(int i=N;i;i--)
	{
		d[i]=1;
		for(int j=i+1;j<=N;j++)
			if (a[i]<a[j])
			{
				if (d[i]<d[j]+1)
					d[i]=d[j]+1;
				if (size[i]==0 || d[j]>d[A[size[i]-1]])
					A[size[i]++]=j;
			}
		v[i]=new int[size[i]];
		memcpy(v[i],A,sizeof(int)*size[i]);
	}
	return 0;
	scanf("%d",&m);
	while(m--)
	{
		int L;
		scanf("%d",&L);
		int i,k;
		for(i=1;i<=N;i++)
			if (d[i]>=L)
			{
				printf("%d",a[i]);
				k=i;
				break;
			}
		if (i>N)
		{
			printf("Impossible\n");
			continue;
		}
		for(i=L-1;i;i--)
		{
	/*		int j;
			for(j=0;j<v[k].size();j++)
				if (d[v[k][j]]>=i)
				{
					printf(" %d",a[v[k][j]]);
					k=v[k][j];
					break;
				}*/
			int l=0,r=size[k]-1,mid;
			while(l+1<r)
			{
				mid=(l+r)/2;
				if (d[v[k][mid]]>=i) r=mid;
				else l=mid+1;
			}
			if (l==r || d[v[k][l]]>=i) 
			{
				printf(" %d",a[v[k][l]]);
				k=v[k][l];
			}
			else 
			{
				printf(" %d",a[v[k][r]]);
				k=v[k][r];
			}
		}
		printf("\n");
	}
	return 0;
}



