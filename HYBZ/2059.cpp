/*
 * Problem: [Usaco2010 Nov]Feed 购买饲料
 * Time: 2011.04.11
 * Author: dxmtb
 * State: Solved
 * Memo: dp+单调队列
*/
#include <cstdio>
#include <algorithm>
#include <deque>
#include <iostream>
using namespace std;
  
typedef long long s64;
  
const int MAXN=505,MAXK=10005;
const s64 oo=~0ull>>2;
  
struct Node
{
    int X,F;
    s64 C;
}a[MAXN];
  
inline bool operator <(const Node &a,const Node &b)
{
    return a.X<b.X;
}
  
inline void Min(int &a,const int &b)
{
    if (b<a)
        a=b;
}
  
int K,E,N;
s64 d[MAXN][MAXK];
  
int main()
{
    scanf("%d%d%d",&K,&E,&N);
    for(int i=0;i<N;i++)
    {
        scanf("%d%d%lld",&a[i].X,&a[i].F,&a[i].C);
        if (a[i].F>K)
            a[i].F=K;
    }
    sort(a,a+N);
    for(int j=0;j<=a[0].F;j++)
        d[0][j]=a[0].C*j;
    for(int i=a[0].F+1;i<=K;i++)
        d[0][i]=oo;
    for(int i=1;i<N;i++)
    {
        deque<pair<s64,int> > q;
        for(int j=0;j<=K;j++)
        {
            const int &k=j;
            s64 nd=d[i-1][k]-k*a[i].C+k*k*(a[i].X-a[i-1].X);
            while(q.size() && q.back().first>nd) q.pop_back();
            while(q.size() && q.front().second<j-a[i].F) q.pop_front();
            q.push_back(make_pair(nd,k));
            d[i][j]=q.front().first+j*a[i].C;
        }
    }
    cout<<d[N-1][K]+(E-a[N-1].X)*K*K;
    return 0;
}