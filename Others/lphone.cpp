/*
ID: dxmtb
PROG: 激光电话
TIME: 2010.12.26
STATE: Solved
MEMO: 最短路
*/
#include <cstdio>
#include <iostream>
#include <string>
#include <queue>
using namespace std;

const int MAXN=105;
const int oo=0x7fffffff;

string map[MAXN];
int Si,Sj,Ti,Tj;
int H,W;

int dis[MAXN][MAXN];
bool in[MAXN][MAXN];
void spfa()
{
	queue<pair<int,int> >q;
	for(int i=0;i<H;i++)
		for(int j=0;j<W;j++)
			dis[i][j]=oo;
	q.push(make_pair(Si,Sj));
	dis[Si][Sj]=-1;
	in[Si][Sj]=true;
	while(q.size())
	{
		pair<int,int> u=q.front();q.pop();
		int ui=u.first,uj=u.second;
		#define solve1 \
			if(map[i][uj]!='*')\
			{\
				if (dis[i][uj]>dis[ui][uj]+1)\
				{\
					dis[i][uj]=dis[ui][uj]+1;\
					if (!in[i][uj])\
					{\
						q.push(make_pair(i,uj));\
						in[i][uj]=true;\
					}\
				}\
			}\
			else break;
		for(int i=ui+1;i<H;i++)
			solve1
		for(int i=ui-1;i>=0;i--)
			solve1
		#define solve2 \
			if(map[ui][j]!='*')\
			{\
				if (dis[ui][j]>dis[ui][uj]+1)\
				{\
					dis[ui][j]=dis[ui][uj]+1;\
					if (!in[ui][j])\
					{\
						q.push(make_pair(ui,j));\
						in[ui][j]=true;\
					}\
				}\
			}\
			else break;
		for(int j=uj+1;j<W;j++)
			solve2
		for(int j=uj-1;j>=0;j--)
			solve2
	}
}

int main()
{
	freopen("lphone.in","r",stdin);
	freopen("lphone.out","w",stdout);
	cin>>W>>H;	
	for(int i=0;i<H;i++)
		cin>>map[i];
	for(int i=0,*ii=&Si,*jj=&Sj;i<H&&ii;i++)
		for(int j=0;j<W&&ii;j++)
			if (map[i][j]=='C')
			{
				*ii=i,*jj=j;
				if (ii==&Ti&&jj==&Tj)
					ii=NULL,jj=NULL;
				else ii=&Ti,jj=&Tj;
			}
	spfa();
/*	for(int i=0;i<H;i++)
	{
		for(int j=0;j<W;j++)
			printf("%d ",dis[i][j]);
		printf("\n");
	}*/
	if (dis[Ti][Tj]==-1)printf("0\n");
	else printf("%d\n",dis[Ti][Tj]);
	return 0;
}
