// BEGIN CUT HERE

// END CUT HERE
#line 5 "KingdomTour.cpp"
#include <vector>
#include <cstdio>
#include <algorithm>
#include <string>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <sstream>
#include <iostream>
using namespace std;

const int MAXN=205;

struct Node
{
	int v,w;
	Node *next;
	Node (int _v,int _w,Node *_next):v(_v),w(_w),next(_next){}
	Node (){}
	void *operator new (size_t,void *p){return p;}
}*adj[MAXN],pool[MAXN*2],*mem;

inline void addedge(int u,int v,int w)
{
	adj[u]=new (mem++)Node (v,w,adj[u]);
	adj[v]=new (mem++)Node (u,w,adj[v]);
}

int father[MAXN];
void dfs(int u)
{
	for(Node *p=adj[u];p;p=p->next)
		if (father[p->v]==-1)
		{
			father[p->v]=u;
			dfs(p->v);
		}
}

int d[MAXN][2];
Node *K[MAXN][2];
void dp(int u)
{
	d[u][0]=d[u][1]=0;
	K[u][0]=K[u][1]=NULL;
	for(Node *p=adj[u];p;p=p->next)
		if (p->v!=father[u])
		{
			dp(p->v);
			int nd=d[p->v][0]+p->w;
			if (nd>=d[u][0])
			{
				d[u][1]=d[u][0];
				K[u][1]=K[u][0];
				d[u][0]=nd;
				K[u][0]=p;
			}
			else if (nd>d[u][1])
			{
				d[u][1]=nd;
				K[u][1]=p;
			}
		}
}

void reset(int u)
{
	if (K[u][0]!=NULL)
	{
		K[u][0]->w=-K[u][0]->w;
		reset(K[u][0]->v);
	}
}

class KingdomTour
{
	public:
		int re;
		void init(const vector <string> &roads)
		{
			string str;
			for(int i=0;i<(int)roads.size();i++)
				str+=roads[i];
			for(int i=0;i<(int)str.size();i++)
				if (str[i]==',')
					str[i]=' ';
			mem=pool;
			memset(adj,0,sizeof(adj));
			int u,v,w;
			stringstream in(str);
			while(in>>u>>v>>w)
			{
				addedge(u,v,w);
				re+=2*w;
			}
		}
		int minTime(int N, vector <string> roads, int T, int L)
		{
			re=0;
			init(roads);
			memset(father,-1,sizeof(father));
			father[0]=0;
			dfs(0);
			for(int i=0;i<T;i++)
			{
				dp(0);
				int best=-1,bi=-1;
				for(int i=0;i<N;i++)
					if (d[i][0]+d[i][1]>best)
						bi=i,best=d[i][0]+d[i][1];
				if (best>L)
				{
					re=re-best+L;
					Node *p;
					if ((p=K[bi][0])!=NULL)
					{
						p->w=-p->w;
						reset(p->v);
					}
					if ((p=K[bi][1])!=NULL)
					{
						p->w=-p->w;
						reset(p->v);
					}
				}
				else
					break;
			}
			return re;
		}
		
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 3; string Arr1[] = {"2 1 9,0 1 3"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 8; int Arg3 = 4; int Arg4 = 16; verify_case(0, Arg4, minTime(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_1() { int Arg0 = 2; string Arr1[] = {"0 1 4"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 2; int Arg3 = 3; int Arg4 = 7; verify_case(1, Arg4, minTime(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_2() { int Arg0 = 6; string Arr1[] = {"4 0 4,2 0 4,2 5 4,4 3 1",
 "0,1 2 10"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 2; int Arg3 = 5; int Arg4 = 41; verify_case(2, Arg4, minTime(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_3() { int Arg0 = 10; string Arr1[] = {"1 2 2,4 1 9,2 5 5,6 5 4,", "1 7 7,7 3 1,2 0 2", ",5 8 5,9 5 6"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 2; int Arg3 = 4; int Arg4 = 59; verify_case(3, Arg4, minTime(Arg0, Arg1, Arg2, Arg3)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{
	KingdomTour ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
