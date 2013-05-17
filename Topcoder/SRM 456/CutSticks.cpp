// BEGIN CUT HERE

// END CUT HERE
#line 5 "CutSticks.cpp"
#include <vector>
#include <cstdio>
#include <algorithm>
#include <string>
#include <cstdlib>
#include <cmath>
#include <sstream>
#include <iostream>
using namespace std;

class CutSticks
{
	public:
		inline bool check(const vector <int> &sticks,int C,int K,const double &mid)
		{
			int N=sticks.size();
			for(int i=N-1;i>=0;i--)
				if (sticks[i]>=mid)
				{
					int t=sticks[i]/mid;
					if (t-1>C)
						t=C+1;
					K-=t;
					C-=t-1;
					if (K<=0)
						return true;
				}
				else
					break;
			return false;
		}
		double maxKth(vector <int> sticks, int C, int K)
		{
			double l=0,r=0;
			int N=sticks.size();
			sort(sticks.begin(),sticks.end());
			for(int i=0;i<N;i++)
				if (sticks[i]>r)
					r=sticks[i];
			r++;
			while(r-l>1e-10)
			{
				double mid=(l+r)/2;
				if (check(sticks,C,K,mid))
					l=mid;
				else
					r=mid;
			}
			return l;
		}
		
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const double &Expected, const double &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {5, 8}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; int Arg2 = 1; double Arg3 = 8.0; verify_case(0, Arg3, maxKth(Arg0, Arg1, Arg2)); }
	void test_case_1() { int Arr0[] = {5, 8}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; int Arg2 = 2; double Arg3 = 5.0; verify_case(1, Arg3, maxKth(Arg0, Arg1, Arg2)); }
	void test_case_2() { int Arr0[] = {5, 8}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; int Arg2 = 3; double Arg3 = 4.0; verify_case(2, Arg3, maxKth(Arg0, Arg1, Arg2)); }
	void test_case_3() { int Arr0[] = {1000000000, 1000000000, 1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; int Arg2 = 5; double Arg3 = 1.0; verify_case(3, Arg3, maxKth(Arg0, Arg1, Arg2)); }
	void test_case_4() { int Arr0[] = {76, 594, 17, 6984, 26, 57, 9, 876, 5816, 73, 969, 527, 49}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 789; int Arg2 = 456; double Arg3 = 34.92; verify_case(4, Arg3, maxKth(Arg0, Arg1, Arg2)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{
	CutSticks ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
