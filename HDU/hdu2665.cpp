/*
 * Problem: hdu2665 Kth Number
 * Time: 2011.04.11
 * Author: dxmtb
 * State: Solved
 * Memo: »®·ÖÊ÷
*/
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cassert>
using namespace std;

const int MAXN=100005,LOGN=18;

struct Node
{
    int first,second;
};

inline bool operator < (const Node &a,const Node &b)
{
    return a.first<b.first;
}

Node a[MAXN];
Node b[LOGN][MAXN];
int c[LOGN][MAXN];

void buildtree(int dep,int l,int r)
{
    if (l==r)
        return ;
    int i=l,j=(l+r)/2+1,mid=(l+r)/2;
    for(int k=l;k<=r;k++)
        if (b[dep][k].first<=mid)
        {
            b[dep+1][i++]=b[dep][k];
            c[dep][k]=1;
        }
        else
        {
            b[dep+1][j++]=b[dep][k];
            c[dep][k]=0;
        }            
    for(int k=l+1;k<=r;k++)
        c[dep][k]+=c[dep][k-1];
    buildtree(dep+1,l,mid);
    buildtree(dep+1,mid+1,r);
}

int query(int dep,int left,int right,int l,int r,int k)
{
    while (l!=r)
    {
        int mid=(left+right)/2,s1,s2;
        if (left==l)
            s1=s2=0;
        else
        {
            s1=c[dep][l-1];
            s2=l-1-left+1-s1;
        }
        int toleft=c[dep][r]-s1;
        if (toleft>=k)
            right=mid,l=left+s1,r=left+c[dep][r]-1;
        else
			r=mid+1+r-left+1-c[dep][r]-1,left=mid+1,l=mid+1+s2,k=k-toleft;
       dep++;
    }
    return b[dep][l].first;
}

int N,M;
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d",&N,&M);
        for(int i=1;i<=N;i++)
        {
            scanf("%d",&a[i].first);
            a[i].second=b[0][i].second=i;
        }
        sort(a+1,a+1+N);
        for(int i=1;i<=N;i++)
            b[0][a[i].second].first=i;
        buildtree(0,1,N);
        while(M--)
        {
            int l,r,k;
            scanf("%d%d%d",&l,&r,&k);
            printf("%d\n",a[query(0,1,N,l,r,k)].first);
        }
    }
    return 0;
}