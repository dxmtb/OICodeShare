/*
ID: dxmtb
PROG: 锯木场选址
TIME: 2010.7.8
STATE: Solved
MEMO: 斜率优化单调队列
*/
#include <cstdio>
using namespace std;

const int MAXN=20000,MAXM=MAXN+2;
const int oo=0x7fffffff;

int n;
int d[MAXM][3];
int s[MAXM],p[MAXM],t[MAXM];

inline int min(int a,int b)
{
	return a>b?b:a;
}

inline int a(int k,int j)
{
	return d[k+1][j-1]+s[k]*p[k-1]-t[k-1];
}

inline int b(int k1,int k2)
{
	return s[k1]-s[k2];
}

inline double g(int k1,int k2,int j)
{
	return double(a(k1,j)-a(k2,j))/(s[k1]-s[k2]);
}

int q[3][MAXM];
int l[3]={0,0,0},r[3]={0,0,0};

int main()
{
//	freopen("saw.in","r",stdin);
//	freopen("saw.out","w",stdout);
	scanf("%d",&n);
	p[0]=s[1]=t[0]=0;
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d",p+i,s+i+1);
		s[i+1]+=s[i];
		t[i]=t[i-1]+s[i]*p[i];
		p[i]+=p[i-1];
		d[i][0]=d[i][1]=d[i][2]=oo;
	}
	d[n+1][0]=0;
	for(int i=n;i;i--)
		d[i][0]=s[n+1]*(p[n]-p[i-1])+t[i-1]-t[n];
	q[0][0]=q[1][0]=q[2][0]=n;
	for(int i=n;i;i--)
		for(int j=1;j<=2;j++)
			{
				int &ll=l[j],&rr=r[j];
				while(ll<rr&&a(q[j][ll],j)-a(q[j][ll+1],j)>=p[i-1]*b(q[j][ll],q[j][ll+1]))
					ll++;
				int k=q[j][ll];
//				printf("%d\n",k);
				int w=s[k]*(p[k-1]-p[i-1])+t[i-1]-t[k-1];
				d[i][j]=d[k+1][j-1]+w;
				while(ll<rr&&g(q[j][rr-1],q[j][rr],j)<=g(q[j][rr],i-1,j))
					rr--;
				q[j][++rr]=i-1;
			}
	printf("%d\n",d[1][2]);
	return 0;
}
