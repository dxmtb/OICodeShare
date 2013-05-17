// BEGIN CUT HERE

// END CUT HERE
#line 5 "SolitaireSimulation.cpp"
#include <vector>
#include <cstdio>
#include <algorithm>
#include <string>
#include <cstdlib>
#include <cmath>
#include <sstream>
#include <set>
#include <map>
#include <iostream>
using namespace std;

class SolitaireSimulation
{
	public:
		int periodLength(vector <int> heaps)
		{
			sort(heaps.begin(),heaps.end(),greater<int>());
			map<vector<int>,int> hash;
			hash[heaps]=0;
			int tot=0;
			while(true)
			{
				tot++;
				int size=heaps.size();
				for(int i=0;i<size;i++)
					heaps[i]--;
				heaps.push_back(size);
				sort(heaps.begin(),heaps.end(),greater<int>());
				while(heaps.back()==0)
					heaps.pop_back();
				map<vector<int>,int>::iterator it=hash.find(heaps);
				if (it!=hash.end())
					return tot-it->second;
				hash[heaps]=tot;
			}
		}
		
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {3,1,3}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 4; verify_case(0, Arg1, periodLength(Arg0)); }
	void test_case_1() { int Arr0[] = {1,4}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 3; verify_case(1, Arg1, periodLength(Arg0)); }
	void test_case_2() { int Arr0[] = {1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; verify_case(2, Arg1, periodLength(Arg0)); }
	void test_case_3() { int Arr0[] = {4,3,2,1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; verify_case(3, Arg1, periodLength(Arg0)); }
	void test_case_4() { int Arr0[] = {3,3,3,3}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 5; verify_case(4, Arg1, periodLength(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{
	SolitaireSimulation ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
