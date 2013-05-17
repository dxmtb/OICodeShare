// BEGIN CUT HERE

// END CUT HERE
#line 5 "RooksParty.cpp"
#include <vector>
#include <cstdio>
#include <algorithm>
#include <string>
#include <cstdlib>
#include <cmath>
#include <sstream>
#include <iostream>
#include <cstring>
using namespace std;

typedef long long s64;
const int MO=1000000009;

const int MAXN=35,MAXC=15;

int f[MAXN*MAXN][MAXN][MAXN];
int d[MAXC][MAXN][MAXN];
int C[MAXN*MAXN][MAXN*MAXN];
int N;
vector<int> A;

class RooksParty
{
	public:
		int getf(int s,int i,int j)
		{
			if (i*j<s)
				return 0;
			int &ret=f[s][i][j];
			if (ret!=-1)
				return ret;
			ret=C[i*j][s];
			for(int a=0;a<=i;a++)
				for(int b=0;b<=j;b++)
					if (a!=i || b!=j)
					{
						s64 t=getf(s,a,b);
						if (t==0)
							continue;
						t=t*C[i][a]%MO;
						t=t*C[j][b]%MO;
						ret=(ret+MO-t)%MO;
					}
			return ret;

		}
		int dp(int i,int j,int k)
		{
			if (i==N)
				return 1;
			int &ret=d[i][j][k];
			if (ret!=-1)
				return ret;
			ret=0;
			for(int a=0;a<=j;a++)
				for(int b=0;b<=k;b++)
				{
					s64 t=getf(A[i],a,b);
					if (t==0)
						continue;
					t=t*C[j][a]%MO;
					t=t*C[k][b]%MO;
					t=t*dp(i+1,j-a,k-b)%MO;
					ret=(ret+t)%MO;
				}
			return ret;
		}
		int countArrangements(int rows, int columns, vector <int> counts)
		{
			A=counts;
			N=A.size();
			C[0][0]=1;
			for(int i=1;i<=rows*columns;i++)
			{
				C[i][0]=1;
				for(int j=1;j<=i;j++)
					C[i][j]=(C[i-1][j]+C[i-1][j-1])%MO;
			}
			memset(d,-1,sizeof(d));
			memset(f,-1,sizeof(f));
			return dp(0,rows,columns);
		}
		
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 2; int Arg1 = 3; int Arr2[] = {1,1}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 12; verify_case(0, Arg3, countArrangements(Arg0, Arg1, Arg2)); }
	void test_case_1() { int Arg0 = 5; int Arg1 = 2; int Arr2[] = {3}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 120; verify_case(1, Arg3, countArrangements(Arg0, Arg1, Arg2)); }
	void test_case_2() { int Arg0 = 5; int Arg1 = 2; int Arr2[] = {1,1,1}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 0; verify_case(2, Arg3, countArrangements(Arg0, Arg1, Arg2)); }
	void test_case_3() { int Arg0 = 8; int Arg1 = 8; int Arr2[] = {1,1,1,1,1,1,1,1}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 625702391; verify_case(3, Arg3, countArrangements(Arg0, Arg1, Arg2)); }
	void test_case_4() { int Arg0 = 4; int Arg1 = 2; int Arr2[] = {3,1}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 8; verify_case(4, Arg3, countArrangements(Arg0, Arg1, Arg2)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{
	RooksParty ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
