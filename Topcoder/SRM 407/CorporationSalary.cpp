// BEGIN CUT HERE

// END CUT HERE
#line 5 "CorporationSalary.cpp"
#include <vector>
#include <cstdio>
#include <algorithm>
#include <string>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <cassert>
#include <set>
#include <map>
#include <queue>
#include <sstream>
#include <iostream>
using namespace std;

const int MAXN=55;
int adj[MAXN][MAXN];
bool vis[MAXN];
long long sum[MAXN];
int N;

class CorporationSalary
{
	public:
		void dfs(int u)
		{
			vis[u]=true;
			bool flag=false;
			for(int i=0;i<N;i++)
				if (adj[u][i])
				{
					if (!vis[i])
						dfs(i);
					sum[u]+=sum[i];
					flag=true;
				}
			if (!flag)
				sum[u]=1;
		}
		long long totalSalary(vector <string> relations)
		{
			N=relations.size();
			for(int i=0;i<N;i++)
				for(int j=0;j<N;j++)
					adj[i][j]=relations[i][j]=='Y';
			memset(vis,false,sizeof(vis));
			memset(sum,0,sizeof(sum));
			for(int i=0;i<N;i++)
				if (!vis[i])
					dfs(i);
			long long re=0;
			for(int i=0;i<N;i++)
				re+=sum[i];
			return re;
		}
		
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"N"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); long long Arg1 = 1LL; verify_case(0, Arg1, totalSalary(Arg0)); }
	void test_case_1() { string Arr0[] = {"NNYN",
 "NNYN",
 "NNNN",
 "NYYN"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); long long Arg1 = 5LL; verify_case(1, Arg1, totalSalary(Arg0)); }
	void test_case_2() { string Arr0[] = {"NNNNNN",
 "YNYNNY",
 "YNNNNY",
 "NNNNNN",
 "YNYNNN",
 "YNNYNN"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); long long Arg1 = 17LL; verify_case(2, Arg1, totalSalary(Arg0)); }
	void test_case_3() { string Arr0[] = {"NYNNYN",
 "NNNNNN",
 "NNNNNN",
 "NNYNNN",
 "NNNNNN",
 "NNNYYN"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); long long Arg1 = 8LL; verify_case(3, Arg1, totalSalary(Arg0)); }
	void test_case_4() { string Arr0[] = {"NNNN",
 "NNNN",
 "NNNN",
 "NNNN"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); long long Arg1 = 4LL; verify_case(4, Arg1, totalSalary(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{
	CorporationSalary ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
