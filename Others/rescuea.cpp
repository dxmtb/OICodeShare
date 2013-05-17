/*
 * Problem: Õü¾ÈÄÌÅ£±´Ï£
 * Time: 2011.04.12
 * Author: dxmtb
 * State: Solved
 * Memo: ÍÆ¹«Ê½
*/
#include <cstdio>
#include <cassert>
#include <algorithm>
using namespace std;
const int MAXM=10005;

pair<int,int> v[MAXM];

inline int caldis(int x1,int y1,int x2,int y2)
{
	//x1<=x2
	//number from 0
	int nre;
	if (x1>x2)
	{
		swap(x1,x2);
		swap(y1,y2);
	}	
	if (x1==x2)
		nre=abs(y1-y2);
	else if (y1/2==y2/2)
		nre=(x2-x1-1)*2+((y1&1)?2:1)+((y2&1)?0:1);
	else if (y1<y2)
	{
		nre=(y2/2-y1/2-1)*2+((y2&1)?2:1);
		int xx=x2-(y2/2-y1/2)+((y2&1)==0);
		if (xx<=x1)
		{
			if (y2&1)
				y2--,x2--,nre=1;
			else
				nre=0;
			int yy=(y2/2-(x2-x1))*2;
			nre+=yy-y1+(y2/2-yy/2)*2;
		}
		else
			nre+=(xx-x1)*2-((y1&1)==0);
	}
	else if (y1>y2)
		nre=(y1/2-y2/2-1)*2+((y2&1)?1:2)+(x2-x1)*2+(y1&1);
	return nre;
}

int main()
{
	freopen("rescuea.in","r",stdin);
	freopen("rescuea.out","w",stdout);
	int N,M;
	int nx,ny;
	scanf("%d%d",&N,&M);
	scanf("%d%d",&nx,&ny);
	nx--,ny--;
	for(int i=0;i<M;i++)
	{
		scanf("%d%d",&v[i].first,&v[i].second);
		v[i].first--;
		v[i].second--;
	}
	sort(v,v+M);
	int re=~0u>>1,rx,ry;
	for(int i=0;i<M;i++)
	{
		int x1=v[i].first,y1=v[i].second;		
		int x2=nx,y2=ny;
		int nre=caldis(x1,y1,x2,y2);
		if (nre<re)
			re=nre,rx=v[i].first,ry=v[i].second;		
	}
	printf("%d %d\n",rx+1,ry+1);
	printf("%d\n",re+1);
	return 0;
}