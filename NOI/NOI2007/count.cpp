/*
ID: dxmtb
PROG: NOI2007 生成树计数
TIME: 2011.03.10
STATE: Solved
MEMO: 连通性状态压缩dp
*/
#include <cstdio>
#include <cstring>

typedef long long s64;

const int MAXK=10;
const int MAXS=4000;
const int MO=65521;

struct Matrix
{
	int N,M;
	s64 data[53][53];
	inline Matrix pow(const Matrix &a,s64 n);
	Matrix(const int &n,const int &m):N(n),M(m){memset(data,0,sizeof (data));}
	Matrix(const int &n,const int d[])
	{
		M=n;N=1;
		memset(data,0,sizeof(data));
		for(int i=0;i<M;i++)
			data[0][i]=d[i];
	}
	Matrix(){}
	inline Matrix operator * (const Matrix &b);
}ori,c;

inline Matrix Matrix::operator * (const Matrix &b)
{
	int x=N,y=M,z=b.M;
	c.N=x,c.M=y;
	memset(c.data,0,sizeof(c.data));
	for(int i=0;i<x;i++)
		for(int j=0;j<z;j++)
			for(int k=0;k<y;k++)
				c.data[i][j]=(c.data[i][j]+data[i][k]*b.data[k][j])%MO;
	return c;
}

inline Matrix pow(const Matrix &a,s64 n)
{
	Matrix b=a;
	while((n&1)==0)
		n>>=1,b=b*b;
	Matrix ans=b;n>>=1;
	while(n)
	{
		b=b*b;
		if (n&1) ans=ans*b;
		n>>=1;
	}
	return ans;
}

s64 N;
int tot;
int K,sta[MAXK];
int hash[MAXS],rhash[100];
void dfs(int dep,int now,int s)
{
	if (dep==K)
	{
		if (hash[s])
			printf("Wrong\n");
		hash[s]=tot;
		rhash[tot]=s;
		tot++;
		return ;
	}
	sta[dep]=now;
	dfs(dep+1,now+1,s*K+now);
	for(int i=0;i<now;i++)
	{
		sta[dep]=i;
		dfs(dep+1,now,s*K+i);
	}
}

void extract(int S,int sta[])
{
	sta[K]=0;
	for(int i=K-1;i>=0;i--)
	{
		sta[i]=S%K;
		S/=K;
	}
}

void compress(int &S,int sta[])
{
	S=0;
	for(int i=0;i<K;i++)
		S=S*K+sta[i];
}

int from;
int d[MAXK][MAXS];
bool used[MAXK];
void search(int i,int dep,int sta[]) //if i have edge with dep
{
	int csta[MAXK];
	memcpy(csta,sta,sizeof(csta));
	if (dep==K)
	{
		int now=-1;
		memset(used,false,sizeof(used));
		for(int j=K-i;j<K;j++)
			if (!used[sta[j]])
			{
				used[sta[j]]=true;
				now++;
				for(int k=j;k<=K;k++)
					if (sta[k]==sta[j])
						csta[k]=now;
			}
		if (sta[K]==-1)
			csta[K]=++now;
		int S;
		compress(S,csta+1);
		if (i==K)
		{
			int j;
			for(j=1;j<=K;j++)
				if (csta[0]==csta[j])
					break;
			if (j==K+1)
				return ;
			now=-1;
			memset(used,false,sizeof(used));
			for(int j=K-i+1;j<=K;j++)
				if (sta[j]==-1 || !used[sta[j]])
				{
					used[sta[j]]=true;
					now++;
					for(int k=j;k<=K;k++)
						if (sta[k]==sta[j])
							csta[k]=now;
				}
			compress(S,csta+1);
			ori.data[from][hash[S]]++;
		}
		d[i+1][hash[S]]+=d[i][from];
		return ;
	}
	search(i,dep+1,csta);
	if (csta[K]==csta[dep])
		return ;
	if (csta[K]==-1) csta[K]=csta[dep];
	else
	{
		int to=(csta[K]>csta[dep])?csta[dep]:csta[K];
		int from=csta[dep]+csta[K]-to;
		for(int j=K-i;j<=K;j++)
			if (csta[j]==from)
				csta[j]=to;
	}
	search(i,dep+1,csta);
}

void init()
{
	sta[0]=0;
	dfs(1,1,0);
	d[1][hash[0]]=1;//begin from 0
	for(int i=1,maxs=1;i<=K;i++,maxs*=K)
		for(int j=0;j<tot;j++)
		if (rhash[j]<maxs && d[i][j])
		{
			from=j;
			int S=rhash[j];
			extract(S,sta);
			sta[K]=-1;
			search(i,K-i,sta);
		}
}

int main()
{
	freopen("count.in","r",stdin);
	freopen("count.out","w",stdout);
	scanf("%d%lld",&K,&N);
	init();
//	printf("%d\n",tot);
	ori.N=ori.M=tot;
	Matrix begin(tot,d[K+1]);
	if(N-K-1>0)
	{
		begin=begin*pow(ori,N-K-1);
		printf("%lld\n",begin.data[0][hash[0]]);
	}
	else
		printf("%d\n",d[N][hash[0]]);
	return 0;
}
