/*
 * Problem: NOI2004 曼哈顿
 * Time: 2011.06.16
 * Author: dxmtb
 * State: Solved
 * Memo: dp
*/
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

#define pb push_back
#define mp(a,b) make_pair(a,b)

const int MAXN=105;
const int oo=~0u>>2;

int N,M,T;
int x[MAXN][2],y[MAXN][2];
int xdr[MAXN],ydr[MAXN];
int xw[MAXN],yw[MAXN];
void init()
{
	scanf("%d%d",&M,&N);
	char str[MAXN];
	scanf(" %s",str);
	for(int i=0;i<M;i++)
		xdr[i+1]=(str[i]!='W');
	scanf(" %s",str);
	for(int i=0;i<N;i++)
		ydr[i+1]=(str[i]!='N');
	for(int i=1;i<=M;i++)
		scanf("%d",xw+i);
	for(int i=1;i<=N;i++)
		scanf("%d",yw+i);
	scanf("%d",&T);
	for(int i=0;i<T;i++)
		scanf("%d%d%d%d",x[i],y[i],x[i]+1,y[i]+1);
}

struct Node
{
	int l,need;
	Node *next;
	Node (int _l,int _need,Node *_next):l(_l),need(_need),next(_next){}
	Node (){}
}*adj[MAXN],pool[MAXN],*mem;

inline void addedge(int r,int l,int need)
{
	adj[r]=new (mem++)Node(l,need,adj[r]);
}

inline bool check(int r,int l,int now)
{
	for(Node *p=adj[r];p;p=p->next)
		if (p->need!=now && p->l>l)
			return false;
	return true;
}

vector<pair<int,int> > v[2],vt[2];
int re,tw;
int rxdr[MAXN],rydr[MAXN];
int d[MAXN][MAXN][2],K[MAXN][MAXN][2],J[MAXN][MAXN][2];
bool sure[MAXN];
void update()
{
	sort(vt[0].begin(),vt[0].end());
	sort(vt[1].begin(),vt[1].end());
	v[0].clear();
	v[1].clear();
#define _solve(_k)\
	for(int i=0;i<(int)vt[_k].size();i++)\
	{\
		while(v[_k].size() && v[_k].back().second>=vt[_k][i].second)\
			v[_k].pop_back();\
		bool flag=false;\
		for(int j=vt[_k][i].first;j<=vt[_k][i].second;j++)\
			if (ydr[j]==_k && sure[j])\
			{\
				flag=true;\
				break;\
			}\
		if (!flag)\
			v[_k].pb(vt[_k][i]);\
	}
	_solve(0)
	_solve(1)
	mem=pool;
	memset(adj,0,sizeof(adj));
	for(int i=0;i<(int)v[0].size();i++)
		addedge(v[0][i].second,v[0][i].first,0);
	for(int i=0;i<(int)v[1].size();i++)
		addedge(v[1][i].second,v[1][i].first,1);
	for(int i=0;i<=N;i++)
		for(int j=0;j<i;j++)
			d[i][j][0]=d[i][j][1]=oo;
	d[1][0][0]=(!sure[1] || ydr[1]==0)?(ydr[1]==0?0:yw[1]):oo;
	d[1][0][1]=(!sure[1] || ydr[1]==1)?(ydr[1]==1?0:yw[1]):oo;
	for(int i=1;i<N;i++)
		for(int j=0;j<i;j++)
			for(int k=0;k<2;k++)
				if (d[i][j][k]!=oo && check(i,j,k))
				{
					int nd;
					if (!sure[i+1] || ydr[i+1]==k)
					{
						nd=d[i][j][k]+((ydr[i+1]!=k)?yw[i+1]:0);
						if (nd<d[i+1][j][k])
						{
							d[i+1][j][k]=nd;
							J[i+1][j][k]=j;
							K[i+1][j][k]=k;
						}
					}
					if (!sure[i+1] || ydr[i+1]==(k^1))
					{
						nd=d[i][j][k]+((ydr[i+1]!=(k^1))?yw[i+1]:0);
						if (nd<d[i+1][i][k^1])
						{
							d[i+1][i][k^1]=nd;
							J[i+1][i][k^1]=j;
							K[i+1][i][k^1]=k;
						}
					}
				}
	int ans=oo,rj=-oo,rk=-oo;
	for(int j=0;j<N;j++)
		for(int k=0;k<2;k++)
			if (d[N][j][k]<ans && check(N,j,k))
				ans=d[N][j][k],rj=j,rk=k;
	ans+=tw;
	if (ans<re)
	{
		re=ans;
		memcpy(rxdr,xdr,sizeof(xdr));
		for(int i=N;i;i--)
		{
			rydr[i]=rk;
			int tj=J[i][rj][rk];
			int tk=K[i][rj][rk];
			rj=tj;
			rk=tk;
		}
	}
}

int cxdr[MAXN],cydr[MAXN];
int main()
{
	freopen("manhattan.in","r",stdin);
	freopen("manhattan.out","w",stdout);
	init();
	memcpy(cxdr,xdr,sizeof(xdr));
	memcpy(cydr,ydr,sizeof(ydr));
	re=oo;
	for(int S=0;S<(1<<M);S++)
	{
		memcpy(xdr,cxdr,sizeof(xdr));
		memcpy(ydr,cydr,sizeof(ydr));
		memset(sure,false,sizeof(sure));
		tw=0;
		for(int i=0;i<M;i++)
		{
			int dr=(S&(1<<i))?1:0;
			if (xdr[i+1]!=dr)
			{
				xdr[i+1]=dr;
				tw+=xw[i+1];
			}
		}
		bool flag=true;
		vt[0].clear();
		vt[1].clear();
		for(int i=0;i<T;i++)
		{
			if (x[i][0]==x[i][1])
			{
				if (y[i][0]==y[i][1])
					continue;
				else if ((y[i][0]<y[i][1])!=xdr[x[i][0]])
				{
					flag=false;
					break;
				}
				else continue;
			}
#define _makesure(_a,_b) {\
				int _t=(_b);\
				if (ydr[_a]!=_t && sure[_a])\
				{\
					flag=false;\
					break;\
				}\
				else\
				{\
					if (ydr[_a]!=_t)\
						ydr[_a]=_t,tw+=yw[_a];\
					sure[_a]=true;\
				}\
			}
			if (y[i][0]==y[i][1])
			{
				_makesure(y[i][0],(x[i][0]<x[i][1]))
				continue;
			}
			bool f1=y[i][0]>y[i][1],f2=x[i][0]>x[i][1];
			bool d1=xdr[x[i][0]]^f1,d2=xdr[x[i][1]]^f1;
			int x1,x2,y1,y2;
			if (y[i][0]<y[i][1]) 
				y1=y[i][0],y2=y[i][1];
			else 
				y1=y[i][1],y2=y[i][0];
			if (x[i][0]<x[i][1]) 
				x1=x[i][0],x2=x[i][1];
			else 
				x1=x[i][1],x2=x[i][0];
			if (d1)
				if (d2)
					vt[1^f2].pb(mp(y1,y2));
				else
					_makesure(f1?y1:y2,1^f2)
			else
				if (d2)
					_makesure(f1?y2:y1,1^f2)
				else
				{
					bool tag=false;
					for(int j=x1;j<=x2;j++)
					{
						if (xdr[j]==(1^f1))
						{
							tag=true;
							break;
						}
					}
					if (tag) 
					{
						_makesure(y1,1^f2)
						_makesure(y2,1^f2)
					}
					else
					{
						flag=false;
						break;
					}
				}
		}
		if (flag)
			update();
	}
	if (re==oo) printf("impossible\n");
	else
	{
		printf("possible\n");
		printf("%d\n",re);
		for(int i=1;i<=M;i++)
			printf("%c",(rxdr[i]==0)?'W':'E');
		printf("\n");
		for(int i=1;i<=N;i++)
			printf("%c",(rydr[i]==0)?'N':'S');
		printf("\n");
	}
	return 0;
}
