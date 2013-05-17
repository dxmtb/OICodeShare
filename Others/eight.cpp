/*
ID: dxmtb
PROG: 八
TIME: 2010.11.18
STATE: Solved
MEMO: 容斥原理
*/
#include <cstdio>
typedef long long LL;

const LL MAXN=16;

LL ans[MAXN],top,limit,re; //re can
LL n,A,B,a[MAXN];

LL gcd(LL a,LL b)
{
	LL t;
	while(b!=0)
	{
		t=b;
		b=a%b;
		a=t;
	}
	return a;
}

LL lcm(LL a,LL b)
{
	return a*b/gcd(a,b);
}

void dfs(LL dep)
{
	if (dep==n)
	{
		if (top==0) return ;
		LL t=1;
		for(LL i=0;i<top;i++)
			t=lcm(t,ans[i]);
		if (top&1) re+=limit/t;	
		else re-=limit/t;
		return ;
	}
	dfs(dep+1);
	ans[top++]=a[dep];
	dfs(dep+1);
	top--;
}

int main()
{
	freopen("eight.in","r",stdin);
	freopen("eight.out","w",stdout);
	scanf("%lld",&n);
	for(LL i=0;i<n;i++)
	{
		scanf("%lld",a+i);
		if ((a[i]&1)==0)
			a[i]>>=1;
		if ((a[i]&1)==0)
			a[i]>>=1;
		if ((a[i]&1)==0)
			a[i]>>=1;
	}
	scanf("%lld%lld",&A,&B);
	if (A&7) A=(A>>3)+1;
	else A=(A>>3);
	LL final=0;
	B=(B>>3);

	limit=B;re=0;
	dfs(0);
	final=B-re;

	limit=A-1;re=0;
	dfs(0);
	final-=A-1-re;
	printf("%lld\n",final);
	return 0;
}

