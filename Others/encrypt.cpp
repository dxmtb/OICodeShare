/*
ID: dxmtb
PROG: HAOI 破译密文
TIME: 2010.4.19
STATE: Solved
MEMO: 并查集
*/
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
using namespace std;

const int MAXN=10000;

int n,m,l=0,fs=0;
long long re=0;
char s1[MAXN],s2[MAXN];
int len[26],sum[26];
bool us[26],used[MAXN+2];
int father[MAXN+2];

inline int num(char ch,int i)
{
	return (sum[ch-'a']+i);
}

int getfather(int x)
{
	if (father[x]==x) return x;	
	return father[x]=getfather(father[x]);
}

void judge(int a,int b)
{
	int fx=getfather(a),fy=getfather(b);
	if (fx==fy)return;
	father[fx]=fy;
}

void init()
{
	gets(s1);
	gets(s2);
	scanf("%d",&n);
	for(int i=0;i<n;i++)
	{
		char ch;int t;
		do
		{
			scanf("%c%d",&ch,&t);
		}
		while (!(ch>='a'&&ch<='z'));
		len[ch-'a']=t;
		fs+=t;
	}
	for(unsigned i=0;i<strlen(s1);i++)
		if (s1[i]>='a'&&s1[i]<='z')
			l+=len[s1[i]-'a'],us[s1[i]-'a']=true;
		else l+=1;
	int l2=0;	
	for(unsigned i=0;i<strlen(s2);i++)
		if (s2[i]>='a'&&s2[i]<='z')
			l2+=len[s2[i]-'a'],us[s2[i]-'a']=true;
		else l2+=1;
	if (l!=l2){printf("0\n");exit(0);}
	sum[0]=0;
	for(int i=1;i<26;i++)
		sum[i]=sum[i-1]+len[i-1];
	for(int i=0;i<fs;i++)
		father[i]=i;
	father[MAXN]=MAXN;
	father[MAXN+1]=MAXN+1;
}

void solve()
{
	int p1=0,p2=0,pp1=0,pp2=0;
	for(int i=0;i<l;i++)
	{
		bool a=(s1[p1]>='0'&&s1[p1]<='9');
		bool b=(s2[p2]>='0'&&s2[p2]<='9');
		if (a&&!b)
		{
			judge(num(s2[p2],pp2),MAXN+s1[p1]-'0');
			p1++;pp1=0;
			if (pp2==len[s2[p2]-'a']-1)
			{
				p2++;pp2=0;
			}
			else
				pp2++;
		}
		else
		if (!a&&b)
		{
			judge(num(s1[p1],pp1),MAXN+s2[p2]-'0');
			p2++;pp2=0;
			if (pp1==len[s1[p1]-'a']-1)
			{
				p1++;pp1=0;
			}
			else
				pp1++;
		}
		else
		if (a&&b)
		{
			if (s2[p2]!=s1[p1]){printf("0\n");exit(0);}
			p1++;pp1=0;
			p2++;pp2=0;
		}
		else
		{
			judge(num(s1[p1],pp1),num(s2[p2],pp2));
			if (pp1==len[s1[p1]-'a']-1)
			{
				p1++;pp1=0;
			}
			else
				pp1++;			
			if (pp2==len[s2[p2]-'a']-1)
			{
				p2++;pp2=0;
			}
			else
				pp2++;
		}
	}
	for(int i=0;i<fs;i++)
		father[i]=getfather(father[i]);
	if (getfather(MAXN+1)==getfather(MAXN))
	{
		printf("0\n");
		exit(0);
	}
	used[father[MAXN]]=true;
	used[father[MAXN+1]]=true;
	for(int i=0;i<26;i++)
		if (us[i])
			for(int j=sum[i];j<=sum[i]+len[i]-1;j++)
				if (!used[getfather(j)])
				{
					used[father[j]]=true;
					re++;
				}
	if (re==0)printf("1\n");
	else 
	{
		long long ans=1;
		for(int i=0;i<re;i++)
			ans*=2;
		printf("%lld\n",ans); 
	}
}

int main() 
{
	freopen("encrypt.in","r",stdin);
	freopen("encrypt.out","w",stdout);
	init();
	solve();
	return 0;
}
