// BEGIN CUT HERE

// END CUT HERE
#line 5 "NetworkSecurity.cpp"
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

typedef long long s64;
const int MAXN=1005;

struct Node
{
	int v;
	Node *next;
	Node (int _v,Node *_next):v(_v),next(_next){}
}*adj[MAXN];

inline void addedge(int u,int v)
{
	adj[u]=new Node (v,adj[u]);
}

bool vis[MAXN];
int N;
s64 reach[MAXN];
class NetworkSecurity
{
	public:
		void dfs(int u)
		{
			vis[u]=true;
			for(Node *p=adj[u];p;p=p->next)
				if (p->v<N)
				{
					if (!vis[p->v])
						dfs(p->v);
					reach[u]|=reach[p->v];
				}
				else
					reach[u]|=(1LL<<(p->v-N));
		}
		int secureNetwork(vector <string> clientCable, vector <string> serverCable)
		{
			N=clientCable.size();
			memset(adj,0,sizeof(adj));
			for(int i=0;i<N;i++)
				for(int j=0;j<N;j++)
					if (clientCable[i][j]=='Y')
						addedge(i,j);
			for(int i=0;i<N;i++)
				for(int j=0;j<(int)serverCable[i].size();j++)
					if (serverCable[i][j]=='Y')
						addedge(i,j+N);
			memset(vis,false,sizeof(vis));
			memset(reach,0,sizeof(reach));
			for(int i=0;i<N;i++)
				if (!vis[i])
					dfs(i);
			int re=0;
			for(int i=0;i<N;i++)
			{
				s64 tmp=0;
				for(Node *p=adj[i];p;p=p->next)
					if (p->v<N)
						tmp|=reach[p->v];
				tmp=reach[i]^tmp;
				while(tmp)
				{
					re++;
					tmp-=(tmp&(-tmp));
				}
			}
			return re;
		}
		
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] ={"NNNYYNNNN", "NNNNYYNNY", "NNNYNNNYN", "NNNNNYNYN", "NNYYNNNYN", "NNNNNNNYN", "YNYYYNNNN", "NNNNNNNNN", "NNYYNNYNN"};  vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); 
		string Arr1[] = {"YNNNYNYNNNNYNNNNNNNNNNNNNYYNNNNNYNNNYYYNYNYNNNNNNY", "YNNNNYYNYYNNNNNYNNNYNNNNNYNYYNYNYNNYYNNNNNYNNNNNNN", "NNNYYNNNNYNYNNNNYNNNNNNYNNNNYYNNNNNNNNNNNNNNYNNNNN", "NNNNNNNNNYNYNNNNYNYYYNNNNYNYNYNNYNNNNNNNNYNYNNNYNN", "YYNNNYYNNYYNNNYNNYNNYNNNNNNNYNNNNNNYYNNYNNNNNNNNNN", "NYYNNYNNNNNNYNNNYYYNYYNNYNNNYNYNNYYYNNNYNNNNNNYNNN", "NYNNNNNNNNYNYNNNYYNNNNNYNNNNNNNYYNNNNNNNYNNNNYNNYN", "YNYYYYNNNYNNNYNNNYNNNNNNYNNYNNNNNNNYNNYNNYNNNNYNYY", "NYNNNNNNYYYNNNYNYYNNYYNYYYNNYYNYYNYNYYNYNNYNNYYNNN"};
		       	vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 48; verify_case(0, Arg2, secureNetwork(Arg0, Arg1)); }
	void test_case_1() { string Arr0[] = {"NN"
,"NN"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"NNN"
,"NNN"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 0; verify_case(1, Arg2, secureNetwork(Arg0, Arg1)); }
	void test_case_2() { string Arr0[] = {"NYNN"
,"NNNN"
,"NNNY"
,"NNNN"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"YYN"
,"NNN"
,"NNY"
,"NNN"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 3; verify_case(2, Arg2, secureNetwork(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{
	NetworkSecurity ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
