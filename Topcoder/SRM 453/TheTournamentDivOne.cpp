// BEGIN CUT HERE

// END CUT HERE
#line 5 "TheTournamentDivOne.cpp"
#include <vector>
#include <cstdio>
#include <algorithm>
#include <string>
#include <cstdlib>
#include <cmath>
#include <sstream>
#include <iostream>
#include <numeric>
using namespace std;

const int MAXN=55;

int D[MAXN];
class TheTournamentDivOne
{
	public:
		int find(vector <int> points, int w, int d)
		{
			int N=points.size();
			for(int i=0;i<N;i++)
			{
				D[i]=points[i]/d;
				while(D[i]>=0 && ((points[i]-D[i]*d)%w)!=0)
					D[i]--;
				if (D[i]==-1)
					return -1;
			}
			int sump=accumulate(points.begin(),points.end(),0);
			int re=-1;
			while(true)
			{
				int b=0;
				for(int i=1;i<N;i++)
					if (D[i]>D[b])
						b=i;
				int sumd=accumulate(D,D+N,0);
				if (D[b]*2<=sumd && sumd%2==0)
				{
					int ans=sumd/2+(sump-sumd*d)/w;
					if (re==-1 || ans<re)
						re=ans;
				}
				D[b]--;
				while(D[b]>=0 && ((points[b]-D[b]*d)%w)!=0)
					D[b]--;
				if (D[b]==-1)
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
	void test_case_0() { int Arr0[] = {10, 1, 1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; int Arg2 = 1; int Arg3 = 6; verify_case(0, Arg3, find(Arg0, Arg1, Arg2)); }
	void test_case_1() { int Arr0[] = {1, 1, 1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; int Arg2 = 1; int Arg3 = -1; verify_case(1, Arg3, find(Arg0, Arg1, Arg2)); }
	void test_case_2() { int Arr0[] = {1, 4, 0, 2}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 3; int Arg2 = 1; int Arg3 = 3; verify_case(2, Arg3, find(Arg0, Arg1, Arg2)); }
	void test_case_3() { int Arr0[] = {8, 3, 8, 5, 9, 2, 7, 11}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 3; int Arg2 = 2; int Arg3 = 15; verify_case(3, Arg3, find(Arg0, Arg1, Arg2)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{
	TheTournamentDivOne ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
