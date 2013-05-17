/*
ID: dxmtb
PROG: HAOI2008 求回文串
TIME: 2011.03.16
STATE: Solved
MEMO: 贪心
*/
#include <cstdio>
#include <cstring>
#include <deque>
using namespace std;
const int MAXN=1000005;
const int oo=0x7fffffff;

deque<int> q[26];

char st[MAXN];

int a[MAXN];
int N;

void add(int pos,int num)
{
	while(pos<=N)
	{
		a[pos]+=num;
		pos+=(pos)&(-pos);
	}
}

int getsum(int pos)
{
	int ans=0;
	while(pos>=1)
	{
		ans+=a[pos];
		pos-=(pos)&(-pos);
	}
	return ans;
}

int getsum(int l,int r)
{
	return getsum(r)-getsum(l-1);
}

bool used[MAXN];
int str[MAXN];
int main()
{
	freopen("string!.in","r",stdin);
	freopen("string!.out","w",stdout);
	scanf("%s",st+1);
	int l=1,r=strlen(st+1);
	N=r;
	for(int i=l;i<=r;i++)
		q[str[i]=st[i]-'A'].push_back(i);
	bool flag=false;
	for(int i=0;i<26;i++)
		if (q[i].size()&1)
		{
			if (!flag) flag=true;
			else 
			{
				printf("-1\n");
				return 0;
			}
		}
	long long re=0;
	while(l<r)
	{
		while(used[l])
			l++;
		while(used[r])
			r--;
		if (l>=r)
			break;
		if (str[l]==str[r])
		{
			q[str[l]].pop_front();
			q[str[l]].pop_back();
			l++,r--;
		}
		else
		{
			int w1,w2;
			if (q[str[l]].size()>=2)
			{
				int t=q[str[l]].back();
				w1=r-t-getsum(t,r);
			}
			else w1=oo;
			if (q[str[r]].size()>=2)
			{
				int t=q[str[r]].front();
				w2=t-l-getsum(l,t);
			}
			else w2=oo;
			if (w1<w2)
			{
				re+=w1;
				int t=q[str[l]].back();
				add(t,1);
				used[t]=true;
				q[str[l]].pop_back();
				q[str[l]].pop_front();
				l++;
			}
			else
			{
				re+=w2;
				int t=q[str[r]].front();
				add(t,1);
				used[t]=true;
				q[str[r]].pop_back();
				q[str[r]].pop_front();
				r--;
			}
		}
	}
	printf("%lld\n",re);
	return 0;
}
