#include <cstdio>
using namespace std;

const int MAXN=2000000;

int n;
int a[MAXN+1];

void sift(int a[],int k,int m)
{
	int i=k,x=a[i];
	while (i*2<=m)
	{
		int j=i*2+1;
		if (i*2==m||a[i*2]<=a[i*2+1])j=j-1;
		if (x>a[j])a[i]=a[j];
		else break;
		i=j;
	}
	a[i]=x;
}
void make_heap(int a[],int n)
{
	for(int i=n/2;i>=1;i--)
		sift(a,i,n);
}
void heap_sort(int a[],int n)
{
	make_heap(a,n);
	for(int i=n;i>=1;i--)
	{
		int x=a[i];
		a[i]=a[1];
		a[1]=x;
		sift(a,1,i-1);
	}
}

int main()
{
	freopen("sort.in","r",stdin);
	freopen("sort.out","w",stdout);
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	heap_sort(a,n);
	for(int i=n;i>=1;i--)
		printf("%d ",a[i]);
	return 0;
}
