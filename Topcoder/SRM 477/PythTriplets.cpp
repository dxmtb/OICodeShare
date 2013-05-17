// BEGIN CUT HERE

// END CUT HERE
#line 5 "PythTriplets.cpp"
#include <vector>
#include <cstdio>
#include <algorithm>
#include <string>
#include <cassert>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <sstream>
#include <iostream>
using namespace std;

const int MAXN=205;
#define pb push_back
#define mp make_pair
typedef long long s64;

struct Node
{
	int v;
	Node *next;
	Node (int _v,Node *_next):v(_v),next(_next){}
	Node (){}
	void *operator new(size_t,void *p){return p;}
}*adj[MAXN],pool[MAXN*MAXN],*mem;

inline void addedge(int u,int v)
{
	adj[u]=new (mem++)Node(v,adj[u]);
	adj[v]=new (mem++)Node(u,adj[v]);
}

s64 gcd(s64 a,s64 b)
{
	s64 t;
	while(b)
	{
		t=a%b;
		a=b;
		b=t;
	}
	return a;
}

bool check(s64 a,s64 b)
{
	if (gcd(a,b)==1)
	{
		s64 d=(s64)a*a+(s64)b*b;
		s64 c=sqrt(d);
		if (c*c==d)
			return true;
	}
	return false;
}

vector<int> num;
int N;
vector<pair<int,int> > edge;
int lv[MAXN];
int father[MAXN];

void dfs(int u)
{
	for(Node *p=adj[u];p;p=p->next)
	{
		if (lv[p->v]==-1)
		{
			lv[p->v]=lv[u]^1;
			father[p->v]=u;
			dfs(p->v);
		}	
		if (lv[u]==0)
			edge.pb(mp(u,p->v));
		else
			edge.pb(mp(p->v,u));
	}
}

bool vis[MAXN];
int mat[MAXN];
bool find(int u)
{
	for(Node *p=adj[u];p;p=p->next)
		if (!vis[p->v])
		{
			vis[p->v]=true;
			if (mat[p->v]==-1 || find(mat[p->v]))
			{
				mat[p->v]=u;
				return true;
			}
		}
	return false;
}

class PythTriplets
{
	public:
		void init(const vector <string> &stick)
		{
			string str;
			for(int i=0;i<(int)stick.size();i++)
				str+=stick[i];
			stringstream in(str);
			num.clear();
			int x;
			while(in>>x)
				num.push_back(x);
		}
		int findMax(vector <string> stick)
		{
			init(stick);
			N=num.size();
			mem=pool;
			memset(adj,0,sizeof(adj));
			for(int i=0;i<N;i++)
				for(int j=i+1;j<N;j++)
					if (check(num[i],num[j]))
						addedge(i,j);
			memset(lv,-1,sizeof(lv));
			edge.clear();
			for(int i=0;i<N;i++)
				if (lv[i]==-1)
				{
					lv[i]=0;
					dfs(i);
				}
			for(int i=0;i<N;i++)
				for(Node *p=adj[i];p;p=p->next)
					if (lv[p->v]==lv[i])
						return 0;
			mem=pool;
			memset(adj,0,sizeof(adj));
			for(int i=0;i<(int)edge.size();i++)
				addedge(edge[i].first,edge[i].second);
			int re=0;
			memset(mat,-1,sizeof(mat));
			for(int i=0;i<N;i++)
				if (lv[i]==0)
				{
					memset(vis,false,sizeof(vis));
					if (find(i))
						re++;
				}
			return re;
		}
		
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"1300 339915 587734 101835 150195 2332 69148 140 15", "052 22755 176692 442035 3772 2332 435 13485 51339 ", "9548 231340 49125 112539 276212 71925 6100 126868 ", "164715 9548 437980 2325 89500 55948 11115 58275", " 252315 131572 58275 435 197620 129315 252195 49", "125 339915 18525 3772 2595 819 131572 2325 10183", "5 8228 40132 456548 104980 213572 252315 188235", " 30459 6195 98252 18645 456548 6195 12628 22035 77", "0808 89500 112052 203812 253275 27692 982330 61", "732 339915 8932 2595 128428 30459 55948 374108 6", "9412 18525 64875 14259 203205 15052 428835 41140 9", "8252 6195 89500 40132 15052 203812 69148 128428 14", "259 51 18525 14852 2325 618772 293188 213572 401", "32 71925 8932 32835 437980 129315 6188 293188 1882", "35 17355 11115 210795 69412 741748 267195 374108 2", "93188 695955 131572 9548 69148 545453 41140 72521", "3 55948 233932 51 112539 253275 2565 13635 713012 ", "442035 3772 159068 692452 429195 27692 55348 25", "65 4012 2595 101835 176972 243219 231340 853076 58", "275 22755 112052 374108 435 442035 911360 428835", " 243219 2332 253275 3772 203812 49125 22035 1882", "35 61732 126868 276212 276212 308739 164715 4224", "99 110019 110019 231340 150195 112539 41140 252195", " 2565 126868 14852 150195 17355 12508 127148 2931", "88 984555 203205 243219 140 1221 61732 14259 44203", "5 437980 58275 27692 878475"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 93; verify_case(0, Arg1, findMax(Arg0)); }
	void test_case_1() { string Arr0[] = {"20 21 3021 220"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; verify_case(1, Arg1, findMax(Arg0)); }
	void test_case_2() { string Arr0[] = {"28 19", "5 1035 21412 37995"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; verify_case(2, Arg1, findMax(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{
	PythTriplets ___test;
	___test.run_test(0);
	return 0;
}
// END CUT HERE
