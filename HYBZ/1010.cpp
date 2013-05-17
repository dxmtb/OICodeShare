/*
 * Problem: [HNOI2008]玩具装箱toy
 * Time: 2011.05.04
 * Author: dxmtb
 * State: Solved
 * Memo: dp + 斜率优化
*/
#include <cstdio>
#include <iostream>
using namespace std;

typedef long long s64;
const int MAXN=50005;

s64 d[MAXN],s[MAXN];
int N,L;

s64 h(int i)
{
	return 2*s[i];
}

s64 g1(int j,int k)
{
	return (d[j]-d[k]+2*L*(s[k]-s[j])+s[j]*s[j]-s[k]*s[k]);
}

s64 g2(int j,int k)
{
	return (s[j]-s[k]);
}

double g(int j,int k)
{
	return double(g1(j,k))/g2(j,k);
}

int q[MAXN],l,r;
void push(int i)
{
	while(l+1<=r && g1(q[r-1],q[r])*g2(q[r],i)>=g1(q[r],i)*g2(q[r-1],q[r]))
		r--;
	q[++r]=i;
}

int get(int i)
{
	while(l+1<=r && g1(q[l],q[l+1])>h(i)*g2(q[l],q[l+1]))
		l++;
	return q[l];
}

int main()
{
	freopen("1010.in","r",stdin);
	cin>>N>>L;
	L=-1-L;
	for(int i=1;i<=N;i++)
	{
		cin>>s[i];
		s[i]+=s[i-1];
	}
	for(int i=1;i<=N;i++)
		s[i]+=i;
	l=0;r=-1;
	d[0]=0;
	push(0);
	for(int i=1;i<=N;i++)
	{
		int j=get(i);
		d[i]=d[j]+(s[i]-s[j]+L)*(s[i]-s[j]+L);
		push(i);
	}
	cout<<d[N]<<endl;
	return 0;
}
