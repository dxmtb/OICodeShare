/*
 * Problem: [BeiJing2006]狼抓兔子
 * Time: 2011.04.19
 * Author: dxmtb
 * State: Solved
 * Memo: 最短路平面图最小割
*/
#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;
 
typedef long long s64;
 
const int MAXN=1005,MAXM=(MAXN-1)*(MAXN-1)*2+2;
const s64 oo=~0ull>>1;
 
struct Node
{
    int v,w;
    Node *next;
    Node (int _v,int _w,Node *_next):v(_v),w(_w),next(_next){}
    Node(){}
    void *operator new (size_t,void *p){return p;}
}*adj[MAXM],pool[MAXN*MAXN*6],*mem=pool;
     
inline void addedge(int u,int v,int w)
{
    adj[u]=new (mem++)Node(v,w,adj[u]);
    adj[v]=new (mem++)Node(u,w,adj[v]);
}
 
s64 dis[MAXM];
 
struct Heap //small first
{
    int a[MAXM],b[MAXM];
    int size;
    void down(int i)
    {
        while(i*2<=size)
        {
            int j=2*i;
            if (j<size && dis[a[j+1]]<dis[a[j]])
                j++;
            if (dis[a[i]]>dis[a[j]])
            {
                swap(b[a[i]],b[a[j]]);                     
                swap(a[i],a[j]);       
            }
            else
                break;
            i=j;
        }
    }
    void up(int i)
    {
        while(i!=1 && dis[a[i]]<dis[a[i/2]])
        {
            swap(b[a[i]],b[a[i/2]]);           
            swap(a[i],a[i/2]);
            i=i/2;
        }
    }
    void dec(int u)
    {
        up(b[u]);
        down(b[u]);
    }
    int getmin()
    {
        swap(b[a[1]],b[a[size]]);
        swap(a[1],a[size]);
        size--;
        down(1);
        return a[size+1];
    }
    void init(int _size)
    {
        size=_size;
        for(int i=1;i<=size;i++)
        {
            a[i]=i-1;
            b[i-1]=i;
        }
    }
/*  bool check(int i)
    {
        if (i*2>size)
            return true;
        if (dis[a[i*2]]<dis[a[i]] || (i*2+1<=size && dis[a[i*2+1]]<dis[a[i]]))
            return false;
        return check(i*2) && check(i*2+1);
    }
    void check()
    {
        if (!check(1))
            printf("wrong");
    }*/
}q;
 
int S,T;
//int n1[MAXN][MAXN],n2[MAXN][MAXN];
#define n1(i,j) ((i)*(M-1)*2+(j)*2+1)
#define n2(i,j) ((i)*(M-1)*2+(j)*2+2)
int N,M;
 
bool sure[MAXM];
void dijkstra()
{
    for(int i=S;i<=T;i++)
        dis[i]=oo;
    dis[S]=0;
    q.init(T-S+1);
    while(!sure[T])
    {
        int j=q.getmin();
        sure[j]=true;
        for(Node *p=adj[j];p;p=p->next)
            if (dis[j]+p->w<dis[p->v])
            {
                dis[p->v]=dis[j]+p->w;
                q.dec(p->v);
                 
        //q.check();
            }
    }
}
 
int main()
{
	freopen("1001.in","r",stdin);
    scanf("%d%d",&N,&M);
    S=0,T=(N-1)*(M-1)*2+1;
/*  for(int i=0;i<N-1;i++)
        for(int j=0;j<M-1;j++)
            n1(i,j)=T++,n2(i,j)=T++;*/
    for(int j=0;j<M-1;j++)
    {
        int w;
        scanf("%d",&w);
        addedge(T,n2(0,j),w);
    }
    for(int i=0;i<N-2;i++)
        for(int j=0;j<M-1;j++)
        {
            int w;
            scanf("%d",&w);
            addedge(n1(i,j),n2(i+1,j),w);
        }
    for(int j=0;j<M-1;j++)
    {
        int w;
        scanf("%d",&w);
        addedge(S,n1(N-2,j),w);
    }
    for(int i=0;i<N-1;i++)
    {
        int w;
        scanf("%d",&w);
        addedge(S,n1(i,0),w);
        for(int j=0;j<M-2;j++)
        {
            scanf("%d",&w);
            addedge(n2(i,j),n1(i,j+1),w);
        }
        scanf("%d",&w);
        addedge(T,n2(i,M-2),w);
    }
    for(int i=0;i<N-1;i++)
        for(int j=0;j<M-1;j++)
        {
            int w;
            scanf("%d",&w);
            addedge(n1(i,j),n2(i,j),w);
        }
    dijkstra();
    cout<<dis[T]<<endl;
    return 0;
}