// BEGIN CUT HERE

// END CUT HERE
#line 5 "SilverDistance.cpp"
#include <vector>
#include <cstdio>
#include <algorithm>
#include <string>
#include <cstdlib>
#include <cmath>
#include <sstream>
#include <iostream>
using namespace std;

class SilverDistance
{
	public:
		int minSteps(int sx, int sy, int gx, int gy)
		{
			int subx=gx-sx,suby=gy-sy;
			if (suby>=abs(subx))
				return suby;
			if (suby<=-abs(subx))
			{
				if ((suby-subx)%2==0)
					return -suby;
				else
					return -suby+2;
			}
			if ((suby-subx)%2)
				return abs(subx)+1;
			return abs(subx);
		}
		
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 1; int Arg1 = 0; int Arg2 = 1; int Arg3 = 9; int Arg4 = 9; verify_case(0, Arg4, minSteps(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_1() { int Arg0 = 0; int Arg1 = 0; int Arg2 = -4; int Arg3 = 3; int Arg4 = 5; verify_case(1, Arg4, minSteps(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_2() { int Arg0 = 0; int Arg1 = 0; int Arg2 = 5; int Arg3 = 8; int Arg4 = 8; verify_case(2, Arg4, minSteps(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_3() { int Arg0 = -487617; int Arg1 = 826524; int Arg2 = 892309; int Arg3 = -918045; int Arg4 = 1744571; verify_case(3, Arg4, minSteps(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_4() { int Arg0 = -27857; int Arg1 = 31475; int Arg2 = -27857; int Arg3 = 31475; int Arg4 = 0; verify_case(4, Arg4, minSteps(Arg0, Arg1, Arg2, Arg3)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{
	SilverDistance ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
