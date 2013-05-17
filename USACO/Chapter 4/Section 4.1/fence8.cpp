/*
ID: dxmtb1
PROG: fence8
LANG: C++
*/
#include <cstdio>
#include <algorithm>
#include <cstdlib>
#include <cstring>
using namespace std;

const int MAXN=50,MAXR=1023;
const int oo=0x7fffffff;

int N,R,l,r,mid,total;
int len[MAXN],lenc[MAXN],need[MAXR],sum[MAXR];
int space;

bool search(int now,int begin)
{
	if (now==-1)
		return true;
	if (space>total-sum[mid])
		return false;
	for(int i=begin;i<N;i++)
		if (lenc[i]>=need[now])
		{
			lenc[i]-=need[now];
			if (lenc[i]<need[0])
				space+=lenc[i];
			if (now>=1&&need[now-1]==need[now])
			{
				if (search(now-1,i)) return true;
			}
			else if (search(now-1,0)) return true;
			if (lenc[i]<need[0])
				space-=lenc[i];
			lenc[i]+=need[now];
		}
	return false;
}

int main()
{
	freopen("fence8.in","r",stdin);
	freopen("fence8.out","w",stdout);
	scanf("%d",&N);
	for(int i=0;i<N;i++)
	{
		scanf("%d",len+i);
		total+=len[i];
	}
	scanf("%d",&R);
	for(int i=0;i<R;i++)
		scanf("%d",need+i);
	sort(len,len+N);
	sort(need,need+R);
	sum[0]=need[0];
	for(int i=1;i<R;i++)
		sum[i]=sum[i-1]+need[i];
	l=0,r=R-1;
	while(l<=r)
	{
		mid=(l+r)>>1;
		space=0;
		memcpy(lenc,len,sizeof(int)*N);
		if (search(mid,0)) l=mid+1;
		else r=mid-1;
	}
	printf("%d\n",r+1);
	return 0;
}
