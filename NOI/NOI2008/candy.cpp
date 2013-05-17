/*
 * Problem: NOI2008 糖果雨
 * Time: 2011.05.30
 * Author: dxmtb
 * State: Solved
 * Memo: 二维+一维树状数组 + 起始时间相同 + 和[A,B]相交的区间数等于L<=B的减去R<A的
*/
#include <cstdio>
#include <cassert>
#include <algorithm>
using namespace std;

const int MAXN=200005,MAXL=1005,MAXC=1000005;

struct Cloud_Node
{
	int l,r,d;
}Cloud[MAXC];

int sum1d[2][MAXL];
int sum2d[4][MAXL][MAXL*3];
int Len;

void add1d(int pos,int x,int val)
{
	assert(x>0 && x<=Len+1);
	int *sum=sum1d[pos];
	for(;x<=Len+1;x+=(x&(-x)))
		sum[x]+=val;
}

int getsum1d(int pos,int x)
{
	assert(x>=0 && x<=Len+1);
	int val=0;
	int *sum=sum1d[pos];
	for(;x>0;x-=(x&(-x)))
		val+=sum[x];
	return val;
}

int query1d(int pos,int l,int r)
{
	if (l<1) l=1;
	if (r>Len+1) r=Len+1;
	if (l>r)
		return 0;
	assert(l>0 && r>0);
	return getsum1d(pos,r)-getsum1d(pos,l-1);
}

void add2d(int pos,int x,int y,int val)
{
	assert(x>0 && y>0);
	assert(x<=Len+1 && y<=Len+Len+1);
	int (*sum)[MAXL*3]=sum2d[pos];
	for(int i=x;i<=Len+1;i+=i&(-i))
		for(int j=y;j<=Len+Len+1;j+=j&(-j))
			sum[i][j]+=val;
}

int _query2d(int pos,int x,int y)
{
	assert(x>=0 && y>0);
	assert(x<=Len+1 && y<=Len+Len+1);
	int (*sum)[MAXL*3]=sum2d[pos];
	int val=0;
	for(int i=x;i>0;i-=i&(-i))
		for(int j=y;j>0;j-=j&(-j))
			val+=sum[i][j];
	return val;
}

int query2d(int pos,int x1,int x2,int y2)
{
	if (x1<1) x1=1;
	if (x2>Len+1) x2=Len+1;
	if (y2>2*Len+1)  y2=2*Len+1;
	if (x1>x2)
		return 0;
	if (1>y2)
		return 0;
	int val=0;
	assert(x1>0 && x2>0);
	assert(y2>0);
	val+=_query2d(pos,x2,y2);
	val-=_query2d(pos,x1-1,y2);
	return val;
}

void trans(int t,int &l,int &d)
{
	if (d==1)
	{
		if (t<=l) l=l-t,d=1;
		else if (t<=l+Len) l=t-l,d=-1;
		else l=l+Len*2-t,d=1;
	}
	else
	{
		if (t<=Len-l) l=l+t,d=-1;
		else if (t<=Len*2-l) l=Len*2-l-t,d=1;
		else l=t-Len*2+l,d=-1;
	}
}

int N;
int main()
{
	freopen("candy.in","r",stdin);
	freopen("candy.out","w",stdout);
	scanf("%d%d",&N,&Len);
	for(int i=0;i<N;i++)
	{
		int k;
		scanf("%d",&k);
		if (k==1)
		{
			int t,c,l,r,d,sub;
			scanf("%d%d%d%d%d",&t,&c,&l,&r,&d);
			sub=r-l;
			t%=2*Len;
			trans(t,l,d);
			r=l+sub;
			if (d==-1)
				d=0;
			add1d(d,l+1,1);
			add2d(d*2,l+1,r+1,1);
			add2d(d*2+1,l+1,r-2*l+Len+1,1);
			Cloud[c].l=l,Cloud[c].r=r,Cloud[c].d=d;
		}
		else if (k==2)
		{
			int T,A,B;
			scanf("%d%d%d",&T,&A,&B);
			int ans=0,C=T%(2*Len),t;
			if (C<Len)
				ans+=(t=query1d(0,C+1+1,B+C+1)-query2d(0,C+1+1,Len+1,A+C-1+1));
			else
				ans+=(t=query1d(0,0+1,min(C-Len,B+C-2*Len)+1)-query2d(0,0+1,C-Len+1,A+C-2*Len-1+1));
			assert(t>=0);
			ans+=(t=query1d(1,max(0,max(2*Len-B-C,Len-C))+1,min(Len,2*Len-C-1)+1)
				-query2d(3,max(0,Len-C)+1,min(Len,2*Len-C-1)+1,A+C-2*Len-1+Len+1));
			assert(t>=0);
			ans+=(t=query1d(0,max(0,max(C-Len+1,C-B))+1,C+1)-query2d(1,max(C-Len+1,0)+1,C+1,A-C-1+Len+1));
			assert(t>=0);
			if (C<Len)
				ans+=(t=query1d(1,0+1,min(B-C,Len-C-1)+1)-query2d(2,0+1,Len-C-1+1,A-C-1+1));
			else
				ans+=(t=query1d(1,2*Len-C+1,B-C+2*Len+1)-query2d(2,2*Len-C+1,Len+1,A-C+2*Len-1+1));
			assert(t>=0);
			printf("%d\n",ans);
		}
		else if (k==3)
		{
			int c;
			scanf("%d",&c);
			scanf("%d",&c);
			int d,l,r;
			d=Cloud[c].d,l=Cloud[c].l,r=Cloud[c].r;
			add1d(d,l+1,-1);
			add2d(d*2,l+1,r+1,-1);
			add2d(d*2+1,l+1,r-2*l+Len+1,-1);
		}
	}
	return 0;
}
