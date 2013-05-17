/*
 * Problem: NOI2004 降雨量
 * Time: 2011.06.17
 * Author: dxmtb
 * State: Solved
 * Memo: 离散化
*/
#include <cstdio>
#include <cmath>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

#define pb push_back
#define mp(x,y) make_pair(x,y)
const int MAXN=15;
const double small=1e-5;
const double eps=1e-7;

struct Node
{
	double l,r,pos[2];
	int vk;
}block[MAXN*MAXN*250*10],*back=block;

inline bool cmp(const Node &a,const Node &b)
{
	return a.l<b.l || (a.l==b.l && a.r<b.r);
}

struct Sgn
{
	inline bool operator ()(const double &a,const double &b)
	{
	/*	if (fabs(a-b)<eps)
			return 0;*/
		return a<b;
	}
};

set<double,Sgn> event;
inline void addnode(double l,double r,int v,int pos,int L)
{
	event.insert(l);
	event.insert(r);
	back->l=l,back->r=r;
	back->vk=v;
	back->pos[0]=(double)pos-v*l,back->pos[1]=(double)pos-v*l+L;
	back++;
}

inline void addevent(Node *a,Node *b,int p1,int p2)
{
	if (a->vk==b->vk)
		return ;
	double x=double(b->pos[p2]-a->pos[p1])/(a->vk-b->vk);
	double l=max(a->l,b->l),r=min(a->r,b->r);
	if (l<=x && x<=r)
		event.insert(x);
}

double merge(vector<pair<double,double> > &v)
{
	if (v.size()==0)
		return 0;
	sort(v.begin(),v.end());
	v.push_back(mp(1000.0,1000.0));
	double l=v[0].first,r=v[0].second;
	double ans=0;
	for(int i=1;i<(int)v.size();i++)
		if (v[i].first<=r)
		{
			if (v[i].second>r)
				r=v[i].second;
		}
		else
		{
			ans+=r-l;
			l=v[i].first,r=v[i].second;
		}
	return ans;
}

int N,W,T,V;
double X[MAXN];
int L[MAXN],v[MAXN];
double re;

int main()
{
	freopen("rainfall.in","r",stdin);
	freopen("rainfall.out","w",stdout);
	scanf("%d%d%d%d",&N,&W,&T,&V);
	for(int i=0;i<N;i++)
	{
		scanf("%lf%d%d",X+i,L+i,v+i);
		if (X[i]==0 && X[i]+L[i]==W)
		{
			printf("0.00\n");
			return 0;
		}
	}
	for(int i=0;i<N;i++)
	{
		if (v[i]==0)
		{
			addnode(0,T,0,X[i],L[i]);
			continue;
		}
		double now=0;
		while(now<T)
		{
			if (v[i]>0)
			{
				double tnow=now+double(W-L[i]-X[i])/v[i];
				addnode(now,min((double)T,tnow),v[i],X[i],L[i]);
				v[i]=-v[i];
				X[i]=W-L[i];
				now=tnow;
			}
			else
			{
				double tnow=now+double(X[i])/(-v[i]);
				addnode(now,min((double)T,tnow),v[i],X[i],L[i]);
				v[i]=-v[i];
				X[i]=0;
				now=tnow;
			}
		}
	}
	sort(block,back,cmp);
	for(Node *i=block;i<back;i++)
		for(Node *j=block+1;j<back && j->l<=i->r;j++)
		{
			addevent(i,j,0,0);
			addevent(i,j,0,1);
			addevent(i,j,1,0);
			addevent(i,j,1,1);
		}
	event.insert(0);
	event.insert(T);
	double l=0;
	for(set<double,bool(*)(double,double)>::iterator it=++event.begin();it!=event.end();it++)
	{
		double r=*it;
		vector<pair<double,double> > v1,v2;
		for(Node *p=block;p<back;p++)
			if (p->l<=l && p->r>=r)
			{
				v1.push_back(make_pair(p->vk*l+p->pos[0],p->vk*l+p->pos[1]));
				v2.push_back(make_pair(p->vk*r+p->pos[0],p->vk*r+p->pos[1]));
			}
		double t1=merge(v1);
		double t2=merge(v2);
		re+=((r-l)*W-(t1+t2)*(r-l)/2)*V;
		l=r;
	}
	printf("%.2lf\n",re);
	return 0;
}
