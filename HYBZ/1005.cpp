/*
 * Problem: [HNOI2008]神奇的国度
 * Time: 2011.04.20
 * Author: dxmtb
 * State: Solved
 * Memo: prufer code +高精度
*/
#include <cstdio>
#include <cstring>
#include <vector>
#include <iostream>
using namespace std;

const int MAXN=1005;

//typedef int High;

vector<int> v;
struct High
{
	int a[200];
	High operator = (int b)
	{
		memset(a,0,sizeof(a));
		for(int i=0;b>1 && i<int(v.size());i++)
			while (b%v[i]==0)
			{
				a[i]++;
				b/=v[i];
			}
		return *this;
	}
	High operator *= (int b)
	{		
		for(int i=0;b>1 && i<int(v.size());i++)
			while (b%v[i]==0)
			{
				a[i]++;
				b/=v[i];
			}
		return *this;
	}
	High operator *= (const High &b)
	{
		for(int i=0;i<(int)v.size();i++)
			a[i]+=b.a[i];
		return *this;		
	}	
	High operator /= (const High &b)
	{
		for(int i=0;i<(int)v.size();i++)
			a[i]-=b.a[i];
		return *this;		
	}
	High operator /= (int b)
	{
		for(int i=0;b>1 && i<int(v.size());i++)
			while (b%v[i]==0)
			{
				a[i]--;
				b/=v[i];
			}
		return *this;	
	}	
};

ostream &operator << (ostream &out,High a)
{
	int ans[10000]={1},len=1;
	for(int i=0;i<(int)v.size();i++)
	{
		int k=a.a[i],p=v[i];
		while(k--)
		{
			for(int i=0;i<len;i++)
				ans[i]*=p;
			for(int i=0;i<len;i++)
				ans[i+1]+=ans[i]/10,ans[i]%=10;
			while(ans[len])
			{
				ans[len+1]+=ans[len]/10;
				ans[len]%=10;
				len++;
			}
		}
	}
	for(int i=len-1;i>=0;i--)
		out<<ans[i];
	return out;
}

High frac(int n)
{
	High ans;
	ans=1;
	for(int i=2;i<=n;i++)
		ans*=i;
	return ans;
}

High pow(int a,int n)
{
	High b;
	b=1;
	while(n--)
		b*=a;
	return b;
}

int N;
int sum1,sum2;
int d[MAXN];
High re;

bool prime[MAXN];
void init()
{
	for(int i=2;i<=N;i++)
		prime[i]=true;
	for(int i=2;i<=N;i++)
		if (prime[i])
		{
			v.push_back(i);
			for(int j=i+i;j<=N;j+=i)
				prime[j]=false;
		}
}

void solve()
{
	if (sum2>N-2 || (sum1==N && sum2<N-2))
		cout<<"0\n";
	else
	{
		re=1;
		for(int i=N-2;i>=N-2-sum2+1;i--)
			re*=i;
		for(int i=0;i<N;i++)
		{
			for(int j=2;j<=d[i]-1;j++)
				re/=j;
			if (d[i]==0)
			{
				cout<<"0\n";
				return ;
			}
		}
		re*=pow(N-sum1,N-2-sum2);
		cout<<re<<endl;
	}
}

int main()
{
	freopen("1005.in","r",stdin);
	scanf("%d",&N);
	init();
	for(int i=0;i<N;i++)
	{
		scanf("%d",d+i);
		if (d[i]!=-1)
			sum1++,sum2+=d[i]-1;
	}
	if (N==1) 
	{
		if (d[0]==-1 || d[0]==0) cout<<"1\n";
		else cout<<"0\n";
	}
	else if (N==2)
	{
		if ((d[0]==-1 || d[0]==1) && (d[1]==-1 || d[1]==1)) cout<<"1\n";
		else cout<<"0\n";
	}
	else solve();
	return 0;
}
