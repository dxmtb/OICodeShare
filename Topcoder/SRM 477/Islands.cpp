// BEGIN CUT HERE

// END CUT HERE
#line 5 "Islands.cpp"
#include <vector>
#include <cstdio>
#include <algorithm>
#include <string>
#include <cstdlib>
#include <cmath>
#include <sstream>
#include <iostream>
using namespace std;

class Islands
{
	public:
		int beachLength(vector <string> str)
		{
			int N=str.size(),M=str[0].size();
			int re=0;
			for(int i=0;i<N;i++)
				for(int j=0;j<M;j++)
					if (str[i][j]=='#')
					{
						if (j && str[i][j-1]=='.')
							re++;
						if (j+1<M && str[i][j+1]=='.')
							re++;
						if (i&1)
						{
							if (i!=0)
								re+=(str[i-1][j]=='.')+((j+1<M)?(str[i-1][j+1]=='.'):0);
							if (i+1<N)
								re+=(str[i+1][j]=='.')+((j+1<M)?(str[i+1][j+1]=='.'):0);
						}
						else
						{
							if (i!=0)
								re+=(j?(str[i-1][j-1]=='.'):0)+(str[i-1][j]=='.');
							if (i+1<N)
								re+=(j?(str[i+1][j-1]=='.'):0)+(str[i+1][j]=='.');
						}
					}
			return re;
		}
		
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {".#...#.."}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 4; verify_case(0, Arg1, beachLength(Arg0)); }
	void test_case_1() { string Arr0[] = {"..#.##", 
 ".##.#.", 
 "#.#..."}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 19; verify_case(1, Arg1, beachLength(Arg0)); }
	void test_case_2() { string Arr0[] = {"#...#.....",
 "##..#...#."}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 15; verify_case(2, Arg1, beachLength(Arg0)); }
	void test_case_3() { string Arr0[] = {"....#.",
 ".#....",
 "..#..#",
 "####.."}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 24; verify_case(3, Arg1, beachLength(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{
	Islands ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
