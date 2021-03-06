/*
ID: dxmtb
PROG: NOI2002 机器人 M 号
TIME: 2011.02.27
STATE: Solved
MEMO: 递推
*/
#include <cstdio>
#include <cstring>
typedef long long s64;
const s64 MAXN=1005;
const s64 MO=10000;

#define clear(x) memset((x),0,sizeof((x)))


s64 d[MAXN][2];
int p[MAXN],e[MAXN];
s64 dd[MAXN];
int N;

s64 getseries(int x,int n)
{
	s64 ans=1,l=0;
	int bit[32],multisum[32],multi[32];
	clear(bit);clear(multisum);clear(multi);
	//multisum sigma(p+p^2+...p^(2^i)) multi p^(2^i)
	for(int i=0;n;i++)
	{
		if (n&1)
			bit[l=i]=1;
		n>>=1;
	}
	multi[0]=x;
	for(int i=1;i<=l;i++)
		multi[i]=(multi[i-1]*multi[i-1])%MO;
	multisum[0]=x;
	for(int i=1;i<=l;i++)
		multisum[i]=multisum[i-1]*(multi[i-1]+1)%MO;
	for(int i=l,t=1;i>=0;i--)
		if (bit[i])
		{
			ans=(ans+multisum[i]*t)%MO;
			t=(t*multi[i])%MO;
		}
	return ans;
}

int main()
{
	freopen("robot.in","r",stdin);
	freopen("robot.out","w",stdout);
	scanf("%d",&N);
	int i;
	for(i=0;i<N;i++)
		scanf("%d%d",p+i,e+i);
	if (p[0]==2)
		i=3;
	else i=2;
	d[i-2][0]=0;
	d[i-2][1]=p[i-2]-1;
	d[i-1][0]=d[i-2][0]+d[i-2][1]*(p[i-1]-1);
	d[i-1][1]=d[i-2][1]+p[i-1]-1;
	while(i<N)
	{
		d[i][0]=d[i-1][0]+d[i-1][1]*(p[i]-1);
		d[i][1]=d[i-1][1]+(1+d[i-1][0])*(p[i]-1);
		d[i][0]%=MO;d[i][1]%=MO;
		i++;
	}
	printf("%lld\n%lld\n",d[N-1][0],d[N-1][1]);
	dd[0]=(p[0]-1)*getseries(p[0],e[0]-1)%MO;
	for(int i=1;i<N;i++)
	{
		dd[i]=dd[i-1];
		s64 tmp=getseries(p[i],e[i]-1);
		dd[i]=(dd[i]+(p[i]-1)*dd[i-1]*tmp)%MO;
		/*
		for(int k=0,tp=(p[i]-1)*dd[i-1];k<e[i];k++,tp*=p[i])
			dd[i]+=tp;*/
		dd[i]=(dd[i]+(p[i]-1)*tmp)%MO;
		/*
		for(int k=0,tp=p[i]-1;k<e[i];k++,tp*=p[i])
			dd[i]+=tp;*/
		dd[i]%=MO;
	//	printf("%d\n",dd[i]);
	}
	s64 re=dd[N-1]-d[N-1][0]-d[N-1][1];
	re%=MO;
	if (re<0) re+=MO;
	printf("%lld\n",re);
	return 0;
}
