/*
ID: dxmtb
PROG: poj1743 Musical Theme
TIME: 2010.7.24
STATE: Solved
MEMO: 后缀数组 + 二分
*/
#include <cstdio>
using namespace std;

const int MAXN=20005;

int r[MAXN],sa[MAXN],height[MAXN],rank[MAXN];
int wa[MAXN],wb[MAXN],wv[MAXN],ws[MAXN];

inline bool cmp(int *t,int a,int b,int l)
{
	return t[a]==t[b]&&t[a+l]==t[b+l];
}

void da(int n,int m)
{
	int *x=wa,*y=wb,*t,i,j,p;
	for(i=0;i<m;i++)ws[i]=0;
	for(i=0;i<n;i++)++ws[x[i]=r[i]];
	for(i=1;i<m;i++)ws[i]+=ws[i-1];
	for(i=n-1;i>=0;i--)sa[--ws[x[i]]]=i;
	for(j=1,p=1;p<n;j*=2,m=p)
	{
		for(i=n-j,p=0;i<n;i++)y[p++]=i;
		for(i=0;i<n;i++)if (sa[i]>=j) y[p++]=sa[i]-j;
		for(i=0;i<n;i++)wv[i]=x[y[i]];
		for(i=0;i<m;i++)ws[i]=0;
		for(i=0;i<n;i++)++ws[wv[i]];
		for(i=1;i<m;i++)ws[i]+=ws[i-1];
		for(i=n-1;i>=0;i--)sa[--ws[wv[i]]]=y[i];
		for(t=x,x=y,y=t,p=1,x[sa[0]]=0,i=1;i<n;i++)
			x[sa[i]]=cmp(y,sa[i-1],sa[i],j)?p-1:p++;
	}
}

void calheight(int n)
{
	int i,j,k=0;
	for(i=1;i<=n;i++)rank[sa[i]]=i;
	for(i=0;i<n;height[rank[i++]]=k)
		for(k?k--:0,j=sa[rank[i]-1];r[i+k]==r[j+k];k++);
}

bool check(int k,int n)
{
	int max=sa[1],min=sa[1];
	for(int i=2;i<=n;i++)
	{
		if (height[i]<k) max=min=sa[i];
		else
		{
			if (sa[i]>max)max=sa[i];
			if (sa[i]<min)min=sa[i];
			if (max-min>k)return true;
		}
	}
	return false;
}

inline void getnum(int &num)
{
	char ch=getchar();
	while(!(ch>='0'))ch=getchar();
	num=0;
	for(;ch>='0';ch=getchar())
		num=num*10+ch-'0';
}

inline void put(int x){
	char s[20];
	int bas = 0;
	for(;x;x/=10)s[bas++] = x%10+'0';
	for(;bas--;)putchar(s[bas]);
	putchar('\n');
}

int main()
{
	freopen("1743.in","r",stdin);
	freopen("1743.out","w",stdout);
	int n;
	while(scanf("%d",&n))
	{
		if (!n)break;
		--n;
		int t1,t2;
		getnum(t1);
		for(int i=0;i<n;i++)
		{
			getnum(t2);
			r[i]=t2-t1+100;
			t1=t2;
		}
		if (n<10){printf("0");putchar('\n');continue;}
		r[n]=0;
		da(n+1,200);
		calheight(n);
		int min=1,max=n/2;
		while(min<=max)
		{
			int mid=(min+max)/2;
			if (check(mid,n)) min=mid+1;
			else max=mid-1;
		}
		if (max>=4)put(max+1);
		else {printf("0");putchar('\n');}
	}
	return 0;
}
