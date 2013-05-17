/*
ID: dxmtb
PROG: NOIP2004 ³æÊ³Ëã
TIME: 2010.4.29
STATE: Solved
MEMO: ËÑË÷
*/
#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;

const int MAXN=26;

int n,tt;
int a[MAXN];
int app[MAXN];
int order[MAXN],orn[MAXN];
char s1[MAXN+1],s2[MAXN+1],s3[MAXN+1];
bool used[MAXN];
bool get[MAXN];

void init()
{
	scanf("%d%s%s%s",&n,s1,s2,s3);
	int timer=0;
	for(int i=0;i<n;i++)
	{
		if (!used[s1[i]-'A'])orn[s1[i]-'A']=timer,order[timer++]=s1[i]-'A',used[s1[i]-'A']=true;
		if (!used[s2[i]-'A'])orn[s2[i]-'A']=timer,order[timer++]=s2[i]-'A',used[s2[i]-'A']=true;
		if (!used[s3[i]-'A'])orn[s3[i]-'A']=timer,order[timer++]=s3[i]-'A',used[s3[i]-'A']=true;
	}
	memset(used,false,sizeof(used));
}

bool check(int dep)
{
/////////
	if (get[s1[0]-'A']&&get[s2[0]-'A'])
		if (a[s1[0]-'A']+a[s2[0]-'A']>=n)return false;	
////////
	bool flag=false;
	int c;
	for(int i=n-1;i>=0;i--)
	{
		if (get[s1[i]-'A']&&get[s2[i]-'A']&&!get[s3[i]-'A'])
		{
			c=s3[i]-'A';
			flag=true;
			break;
		}
	}
	if (flag)
	{
		int x=order[dep+1],y=orn[c];
		order[dep+1]=c;
		order[orn[c]]=x;
		orn[c]=dep+1;
		orn[x]=y;
	}
///////
	for(int i=n-1;i>=0;i--)
	{
		bool x=get[s1[i]-'A'],y=get[s2[i]-'A'],z=get[s3[i]-'A'];
		if (z)
		{
			if (x||y)
			if (x)
				if (y)
				{
					int num=a[s1[i]-'A']+a[s2[i]-'A'];
					if (num%n!=a[s3[i]-'A']&&(num+1)%n!=a[s3[i]-'A'])
						return false;
				}
				else 
				{
					int n1=(a[s3[i]-'A']-a[s1[i]-'A']+n)%n,n2=(a[s3[i]-'A']-a[s1[i]-'A']-1+n)%n;
					if (used[n1]&&used[n2])
						return false;
				}
			else
			{
				int n1=(a[s3[i]-'A']-a[s2[i]-'A']+n)%n,n2=(a[s3[i]-'A']-a[s2[i]-'A']-1+n)%n;
				if (used[n1]&&used[n2])
					return false;
			}
		}
		else
		{
			if (x&&y&&
			used[(a[s1[i]-'A']+a[s2[i]-'A']+n)%n]&&used[(a[s1[i]-'A']+a[s2[i]-'A']+n+1)%n])
				return false;
		}
	}
	return true;	
}

bool final_check()
{
	int temp=0;
	for(int i=n-1;i>=0;i--)
	{
		int num=(a[s1[i]-'A']+a[s2[i]-'A'])+temp;
		if (num>=n)
		{
			num-=n;
			temp=1;
		}
		else temp=0;
		if (num!=a[s3[i]-'A'])
			return false;
	}
	return true;
}

void search(int dep)
{
	tt=dep;
	if (dep==n&&final_check())
	{
		for(int i=0;i<n;i++)
			printf("%d ",a[i]);
		printf("\n");
		exit(0);
	}
	else
	for(int i=0;i<n;i++)
		if (!used[i])
		{
			used[i]=true;
			get[order[dep]]=true;			
			a[order[dep]]=i;
			if (check(dep)) search(dep+1);
			used[i]=false;
			get[order[dep]]=false;
		}
}

int main() 
{
	freopen("alpha.in","r",stdin);
	freopen("alpha.out","w",stdout);
	init();
	search(0);
	return 0;
}
