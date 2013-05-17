/*
ID: dxmtb
PROG: NOI2009 诗人小G
TIME: 2010.4.18
STATE: not Solved
MEMO: 动态规划
*/
#include <cstdio>
#include <cmath>
#include <deque>
#include <cstring>
using namespace std;

const int MAXN=100000;

struct Node
{
	int l,r,k;
	Node(int a,int b,int c){l=a,r=b,k=c;}
};

int N,L,P,T,len[MAXN+1];
char str[MAXN+1][30];
double d[MAXN];

double w(int i,int k)
{
	return pow((double)(abs(len[i]-len[k]-i-k-1-L)),P);
}

int binary_search(int l,int r,int k,int mk)
{
	if (l==r) return l;
	int mid=(l+r)/2;
	if (d[mk]+w(mid,mk)<d[k]+w(mid,k))
		return binary_search(mid+1,r,k,mk);
	else
		return binary_search(mid-1,r,k,mk);
}

void dp()
{
	gets(str[0]);
	gets(str[0]);
	len[0]=strlen(str[0]);	
	for(int i=1;i<N;i++)
	{
		gets(str[i]);
		len[i]=len[i-1]+strlen(str[i]);
	}
	memset(d,0,sizeof(d));
	d[0]=pow((double)(abs(len[0]-L)),P);
	for(int i=1;i<N;i++)
		d[i]=d[0]+w(i,0);
	deque<Node> q;
	q.push_back(Node(0,N-1,0));
	for(int i=1;i<N;i++)
	{
		Node now=q.back(),newone(N-1,N-1,i);
		while (!q.empty()&&d[now.k]+w(now.l,now.k)>d[i]+w(now.l,i))
		{
			newone.l=now.l;
			q.pop_back();
			now=q.back();
		}
		if (q.empty())
		{
			newone.l=0;
			q.push_back(newone);
			for(int j=1;j<N;j++)d[j]=d[i]+w(j,i);
		}
		else
		{
			newone.l=binary_search(now.l+1,now.r-1,i,now.k);
			q.push_back(newone);
			for(int j=newone.l;j<N;j++)d[j]=d[i]+w(j,i);
		}
	}
}

int main() 
{
	freopen("poet.in","r",stdin);
	freopen("poet.out","w",stdout);
	scanf("%d",&T);
	while (scanf("%d%d%d",&N,&L,&P)!=EOF)
		dp();
	return 0;
}
