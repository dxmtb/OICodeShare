// BEGIN CUT HERE

// END CUT HERE
#line 5 "CatchTheMice.cpp"
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

const double eps=1e-7;

#define pb push_back
#define mp make_pair

class CatchTheMice
{
	public:
		double cross(pair<int,int> a,pair<int,int> b)
		{
			return double(a.second-b.second)/(b.first-a.first);
		}
		double largestCage(vector <int> xp, vector <int> yp, vector <int> xv, vector <int> yv)
		{
			int N=xp.size();
			vector<pair<int,int> > v;
			for(int i=0;i<N;i++)
				for(int j=0;j<N;j++)
					if (i!=j)
					{
						v.pb(mp(xv[i]-xv[j],xp[i]-xp[j]));
						v.pb(mp(yv[i]-yv[j],yp[i]-yp[j]));
					}
			int size=v.size();
			sort(v.begin(),v.end());
			vector<pair<int,int> > sta;
			for(int i=0;i<size;i++)
				if (i==size-1 || v[i].first!=v[i+1].first)
				{
					while(sta.size()>=2 && cross(v[i],sta[sta.size()-1])<cross(sta[sta.size()-1],sta[sta.size()-2]))
						sta.pop_back();
					if (sta.size()==1 && v[i].second>sta[0].second)
						sta.pop_back();
					sta.push_back(v[i]);
				}
			double re=sta[0].second;
			for(int i=0;i<(int)sta.size()-1;i++)
			{
				double t=cross(sta[i],sta[i+1]);
				double ans=sta[i].first*t+sta[i].second;
				if (ans<re)
					re=ans;
			}
			return re;
		}
		
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); if ((Case == -1) || (Case == 6)) test_case_6(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const double &Expected, const double &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {202, 437, 340, 461, 875, -134, 491, 42, 539, 224, 949, 598, -158, 21, 83, 71, 46, 565, 730, 250, 81, 481, 781, 331, 424, 780, 576, 309, 857, 507, 497, 231, 289, 26, 941, 965, 839, 58, 294, 855, 200, 120, 815, 738, 700, 8, -43, 504, 426, 448}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {-322, -932, -571, -168, -385, -312, -371, -356, -433, -854, -307, -480, -4, -197, -804, -812, -183, -340, -893, -520, -483, -194, -14, -952, -500, -917, -418, -782, -116, -889, -312, -645, -317, -551, -660, -345, -507, -752, -182, -482, -461, -663, -448, 62, -366, -243, -865, -57, -522, -60}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {61, -56, -47, -59, 1, 96, 39, -24, -64, 61, -8, 24, 96, -16, -21, -18, 82, -67, 8, 56, -22, -58, -98, 51, -53, 6, -77, -43, 0, 37, -69, -37, -48, 82, -7, -10, 1, -23, -47, 4, 68, -29, -94, -87, -83, 88, 93, -64, -60, -56}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {40, 6, 70, -76, -51, -56, 51, -51, -45, 94, 36, -44, -93, -71, -10, -7, 31, 40, 100, -34, 57, -72, 14, 1, -40, 99, 53, -15, -76, 98, 37, -25, -58, -34, -26, -60, 64, 80, -73, -38, -41, -22, -48, -98, 51, -71, 100, 12, -34, 20}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); double Arg4 = 10.0; verify_case(0, Arg4, largestCage(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_1() { int Arr0[] = {0,10,0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0,0,10}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {1,-6,4}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {4,5,-4}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); double Arg4 = 3.0; verify_case(1, Arg4, largestCage(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_2() { int Arr0[] = {50,10,30,15}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {-10,30,20,40}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {-5,-10,-15,-5}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {40,-10,-1,-50}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); double Arg4 = 40.526315789473685; verify_case(2, Arg4, largestCage(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_3() { int Arr0[] = {0,10,10,0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0,0,10,10}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {1,0,-1,0}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {0,1,0,-1}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); double Arg4 = 10.0; verify_case(3, Arg4, largestCage(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_4() { int Arr0[] = {13,50,100,40,-100}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {20,20,-150,-40,63}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {4,50,41,-41,-79}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {1,1,1,3,-1}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); double Arg4 = 212.78688524590163; verify_case(4, Arg4, largestCage(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_5() { int Arr0[] = {0,10}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0,0}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {5,5}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {3,3}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); double Arg4 = 10.0; verify_case(5, Arg4, largestCage(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_6() { int Arr0[] = {-49,-463,-212,-204,-557,-67,-374,-335,-590,-4}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {352,491,280,355,129,78,404,597,553,445}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {-82,57,-23,-32,89,-72,27,17,100,-94}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {-9,-58,9,-14,56,75,-32,-98,-81,-43}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); double Arg4 = 25.467532467532468; verify_case(6, Arg4, largestCage(Arg0, Arg1, Arg2, Arg3)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{
	CatchTheMice ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
