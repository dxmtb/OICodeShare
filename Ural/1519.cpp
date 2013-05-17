/*
ID: dxmtb
PROG: ural 1519 formular1
TIME: 2011.02.23
STATE: Solved
MEMO: 基于连通性的状态压缩dp
*/
#include <cstdio>
#include <stack>
#include <queue>
#include <vector>
using namespace std;

typedef long long s64;

const int MAXN=14;
const int MO=4001;

struct Node
{
	int i,j,S;
	Node(int a=0,int b=0,int c=0):i(a),j(b),S(c){}
};

class Hash
{
	private:
		vector<pair<int,s64> > d[MO];
	public:
		bool insert(int s,s64 dt) //true if already exist
		{
			vector<pair<int,s64> > &dr=d[s%MO];
			int size=dr.size();
			for(int i=0;i<size;i++)
				if (dr[i].first==s)
				{
					dr[i].second+=dt;
					return true;
				}
			dr.push_back(make_pair(s,dt));
			return false;
		}
		s64 find(int s)
		{
			vector<pair<int,s64> > &dr=d[s%MO];
			int size=dr.size();
			for(int i=0;i<size;i++)
				if (dr[i].first==s)
					return dr[i].second;
			return 0;
		}
		void clear()
		{
			for(int i=0;i<MO;i++)
				d[i].clear();
		}
}myhash[2];
int N,M;

inline int getbit(int s,int t)
{
	return (s&(3<<(t<<1)))>>(t<<1);
}

inline void setbit(int &s,int pos,int t)
{
	s|=(3)<<(pos<<1);
	s^=(3^t)<<(pos<<1);
}

inline void exact(int s,int tmp[])
{
	for(int i=0;i<N+1;i++)
		tmp[i]=s&3,s>>=2;
}

int nj,nh;
int ilast,jlast;
queue<Node> q;
inline void deal(Node now,int nS)
{
	if (now.i==ilast&&now.j==jlast)
		return ;
	if (now.j==M-1)
	{
		if (getbit(nS,M)!=0)
			return ;
		nS<<=2;
		now.i++,now.j=-1;
	}
	if (now.j!=nj)
	{
		nj=now.j;
		myhash[nh].clear();	
		nh^=1;
	}
	s64 t=myhash[nh].find(now.S);
	if (myhash[nh^1].insert(nS,t)==false)
		q.push(Node(now.i,now.j+1,nS));
}

s64 re;
void check(const Node &now,int s)
{
	int tmp[MAXN];
	exact(s,tmp);
	int status=0;
	for(int i=0;i<M+1;i++)
		if (tmp[i]==1)
			if (status==0)
				status=1;
			else return ;
		else if (tmp[i]==2)
			if (status==1)
				status=2;
			else return ;
	re+=myhash[nh^1].find(now.S);
}
int tmp[MAXN];
int mat[MAXN];

char data[MAXN][MAXN];
void solve()
{
	q.push(Node(0,0,0));
	myhash[0].insert(0,1);
	while(q.size())
	{
		Node now=q.front();
		int i=now.i,j=now.j,S=now.S;
		q.pop();
		int a=getbit(S,j),b=getbit(S,j+1);
		int nS=S;
		if (data[i][j]=='*')
		{
			if (!a && !b)
				deal(now,nS);
			continue;
		}
		if (a==0&&b==0)
		{
			setbit(nS,j,1);setbit(nS,j+1,2);
			deal(now,nS);
		}
		else if ((a && !b)||(!a && b))
		{
			deal(now,nS);
			setbit(nS,j,b);setbit(nS,j+1,a);
			deal(now,nS);	
		}
		else if (a && b)
		{
			if (a==2&&b==1)
			{
				setbit(nS,j,0);setbit(nS,j+1,0);
				deal(now,nS);
			}
			else if (a==1&&b==2)
			{
				if (i==ilast&&j==jlast)
				{
					check(now,nS);
				}
			}
			else //a==b
			{
				exact(nS,tmp);
				stack<int> sta;
				for(int k=0;k<N+1;k++)
				{
					if (tmp[k]==1)
						sta.push(k);
					else if (tmp[k]==2)
					{
						if (sta.size()==0)
							printf("Error!\n");
						mat[k]=sta.top();sta.pop();
						mat[mat[k]]=k;
					}
				}
				setbit(nS,mat[j+1],1);
				setbit(nS,mat[j],2);
				setbit(nS,j,0);
				setbit(nS,j+1,0);
				deal(now,nS);
			}
		}
		else printf("Impossible!\n");
	}
}

int main()
{
	scanf("%d%d",&N,&M);
	for(int i=0;i<N;i++)
	{
		scanf("%s",data[i]);
		for(int j=0;j<M;j++)
			if (data[i][j]=='.')
				ilast=i,jlast=j;
	}
	solve();
	printf("%lld\n",re);
	return 0;
}
