/*
 * Problem: poj1688 Dolphin Pool
 * Time: 2011.05.27
 * Author: dxmtb
 * State: Solved
 * Memo: 圆离散化
*/
#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;

const double eps=1e-8;
const int MAXN=50;

struct Circle
{
	int x,y,r;
}C[MAXN];

bool operator < (const Circle &a,const Circle &b)
{
	return a.x<b.x;
}

double event[MAXN*MAXN+MAXN*2];
int size;

inline int sgn(const double &x)
{
	if (abs(x)<eps) return 0;
	if (x>eps) return 1;
	return -1;
}
inline double sqr(const double &x)
{
	return x*x;
}

inline double getdis(const double &x1,const double &y1,const double &x2,const double &y2)
{
	return sqrt(sqr(x1-x2)+sqr(y1-y2));
}

void insert(const Circle &a,const Circle &b)
{
	double dis=getdis(a.x,a.y,b.x,b.y);
	if (a.r+b.r<dis)
		return ;
	double alpha=atan2(double(b.y-a.y),double(b.x-a.x));
	double beta=acos((sqr(a.r)+sqr(dis)-sqr(b.r))/(2*a.r*dis));
	double y;
	y=a.y+a.r*sin(alpha+beta);
	event[size++]=y;
	y=a.y+a.r*sin(alpha-beta);
	event[size++]=y;
}

struct Pair
{
	double l,r;
	Pair(double _l,double _r):l(_l),r(_r){}
};

int N;
vector<Pair> v[2];
void getcross(const double &line,int to)
{
	vector<Pair> &now=v[to];
	now.clear();
	for(int i=0;i<N;i++)
		if (abs(C[i].y-line)<C[i].r)
		{
			double t=sqrt(sqr(C[i].r)-sqr(C[i].y-line));
			now.push_back(Pair(C[i].x-t,C[i].x+t));
			while(now.size()>=2)
			{
				if (now[now.size()-1].l<=now[now.size()-2].r)
				{
					if (now[now.size()-2].l>now[now.size()-1].l)
						now[now.size()-2].l=now[now.size()-1].l;
					if (now[now.size()-2].r<now[now.size()-1].r)
						now[now.size()-2].r=now[now.size()-1].r;
					now.pop_back();
				}
				else break;
			}
		}
	double left=-10000;
	for(int i=0;i<(int)now.size();i++)
	{
		swap(now[i].l,now[i].r);
		swap(now[i].l,left);
	}
	now.push_back(Pair(left,10000));
}

int father[2][MAXN*2];
bool used[MAXN*2];
int ans;
void solve()
{
	ans=0;
	memset(father,0,sizeof(father));
	father[0][0]=1;
	for(int i=0;i<size;i++)
		if (i==0 || event[i]-event[i-1]>=1e-10)
		{
			getcross(event[i]-eps,0);
			getcross(event[i]+eps,1);
			memset(father[1],0,sizeof(father[1]));
			for(int j=0;j<(int)v[0].size();j++)
				for(int k=0;k<(int)v[1].size();k++)
					if (v[0][j].r>v[1][k].l && v[0][j].l<v[1][k].r)
					{
						if (father[1][k]==0)
							father[1][k]=father[0][j];
						else if (father[1][k]!=father[0][j])
						{
							const int &q=father[1][k];
							for(int t=0;t<2;t++)
								for(int p=0;p<(int)v[t].size();p++)
									if (father[t][p]==q)
										father[t][p]=father[0][j];
						}
					}
			memset(used,false,sizeof(used));
			for(int j=0;j<(int)v[1].size();j++)
				if (father[1][j])
					used[father[1][j]]=true;
			for(int j=0;j<(int)v[0].size();j++)
				if (!used[father[0][j]])
				{
					used[father[0][j]]=true;
					ans++;
				}
			memset(used,false,sizeof(used));
			for(int j=0;j<(int)v[1].size();j++)
				if (father[1][j])
					used[father[1][j]]=true;
			int from=1;
			for(int j=0;j<(int)v[1].size();j++)
				if (father[1][j]==0)
				{
					while(used[from])
						from++;
					father[1][j]=from++;
				}
			memcpy(father[0],father[1],sizeof(father[0]));
		}
	printf("%d\n",ans);
}

int main()
{
	freopen("1688.in","r",stdin);
	int T;
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&N);
		size=0;
		for(int i=0;i<N;i++)
		{
			scanf("%d%d%d",&C[i].x,&C[i].y,&C[i].r);
			event[size++]=C[i].y-C[i].r;
			event[size++]=C[i].y+C[i].r;
		}
		sort(C,C+N);
		for(int i=0;i<N;i++)
			for(int j=i+1;j<N;j++)
				insert(C[i],C[j]);
		sort(event,event+size);
		solve();
	}
	return 0;
}
