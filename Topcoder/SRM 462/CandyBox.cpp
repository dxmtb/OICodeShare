// BEGIN CUT HERE

// END CUT HERE
#line 5 "CandyBox.cpp"
#include <vector>
#include <cstdio>
#include <algorithm>
#include <string>
#include <cstdlib>
#include <cmath>
#include <sstream>
#include <iostream>
using namespace std;

const int MAXS=10005,MAXN=55;

double d[MAXS][MAXN];

class CandyBox
{
	public:
		vector <double> expectedScore(int C, vector <int> score, int S)
		{
			int N=score.size();
			int tot=N*C*(N*C-1)/2;
			double A=(tot-C*(N*C-C))/double(tot);
			double B=C/double(tot);
			for(int i=0;i<N;i++)
				d[0][i]=score[i];
			for(int i=1;i<=S;i++)
			{
				double sum=0;
				for(int k=0;k<N;k++)
					sum+=d[i-1][k];
				for(int j=0;j<N;j++)
				{
					d[i][j]=d[i-1][j]*A;
					d[i][j]+=(d[i-1][j]*(C-1)*(N-1)+sum-d[i-1][j])*B;
				}
			}
			vector<double> v;
			for(int j=0;j<N;j++)
				v.push_back(d[S][j]);
			return v;
		}
		
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const vector <double> &Expected, const vector <double> &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: " << print_array(Expected) << endl; cerr << "\tReceived: " << print_array(Received) << endl; } }
	void test_case_0() { int Arg0 = 10; int Arr1[] = {1, 10}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 0; double Arr3[] = {1.0, 10.0 }; vector <double> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); verify_case(0, Arg3, expectedScore(Arg0, Arg1, Arg2)); }
	void test_case_1() { int Arg0 = 2; int Arr1[] = {1, 10}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 1; double Arr3[] = {4.0, 7.000000000000001 }; vector <double> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); verify_case(1, Arg3, expectedScore(Arg0, Arg1, Arg2)); }
	void test_case_2() { int Arg0 = 1; int Arr1[] = {1, 4, 10}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 1; double Arr3[] = {5.0, 5.0, 5.0 }; vector <double> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); verify_case(2, Arg3, expectedScore(Arg0, Arg1, Arg2)); }
	void test_case_3() { int Arg0 = 98; int Arr1[] = {13, 82, 74, 78, 12, 71, 81, 80, 30}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 154; double Arr3[] = {26.25622829378155, 74.87969915903301, 69.24219529059805, 72.06094722481552, 25.551540310227182, 67.12813133993495, 74.17501117547864, 73.47032319192427, 38.23592401420582 }; vector <double> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); verify_case(3, Arg3, expectedScore(Arg0, Arg1, Arg2)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{
	CandyBox ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
