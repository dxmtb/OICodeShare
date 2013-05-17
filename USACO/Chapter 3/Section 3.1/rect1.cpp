/*
  ID: dxmtb1
  PROG: rect1
  LANG: C++
*/
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;

const int MAXN=1000,MAXA=10000,MAXC=2500;

struct Sq
{
	int llx,lly,urx,ury,co;
	Sq* next;
	Sq (int a=0,int b=0,int c=0,int d=0,int e=0,Sq *n=0):llx(a),lly(b),urx(c),ury(d),co(e),next(n){}
}*head;

int A,B,n;
int llx[MAXN],lly[MAXN],urx[MAXN],ury[MAXN];
int color[MAXN];
int re[MAXC+1];

inline int min(int a,int b){return a>b?b:a;}
inline int max(int a,int b){return a>b?a:b;}

void add(int x1,int y1,int x2,int y2,int co)
{
	if ((x2-x1)*(y2-y1)==0)
		return;
	bool flag=false;
	for(Sq *p=head;p;p=p->next)
		if(x1>=p->llx&&p->urx>=x2&&y1>=p->lly&&p->ury>=y2)return;
		else if (x1<p->urx&&p->llx<x2&&y1<p->ury&&p->lly<y2)
		{
			int tx1=max(x1,p->llx),ty1=max(y1,p->lly);
			int tx2=min(x2,p->urx),ty2=min(y2,p->ury);
			if (p->ury<y2)add(x1,ty2,x2,y2,co),flag=true;
			if (x1<p->llx)add(x1,ty1,tx1,ty2,co),flag=true;
			if (p->urx<x2)add(tx2,ty1,x2,ty2,co),flag=true;
			if (y1<p->lly)add(x1,y1,x2,ty1,co),flag=true;
			if (flag)break;
		}
	if (!flag)
		head=new Sq(x1,y1,x2,y2,co,head);
}

void init()
{
	scanf("%d%d%d",&A,&B,&n);
	for(int i=0;i<n;i++)
		scanf("%d%d%d%d%d",llx+i,lly+i,urx+i,ury+i,color+i);
}

void solve()
{
	head=new Sq(llx[n-1],lly[n-1],urx[n-1],ury[n-1],color[n-1],NULL);
	for(int i=n-2;i>=0;i--)
		add(llx[i],lly[i],urx[i],ury[i],color[i]);
	add(0,0,A,B,1);
	for(Sq *p=head;p;p=p->next)
		re[p->co]+=(p->urx-p->llx)*(p->ury-p->lly);
	for(int i=1;i<=MAXC;i++)
		if (re[i])
			printf("%d %d\n",i,re[i]);
}
int main()
{
	freopen("rect1.in","r",stdin);
	freopen("rect1.out","w",stdout);
	init();
	solve();
	return 0;
}
