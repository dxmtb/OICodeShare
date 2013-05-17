// BEGIN CUT HERE

// END CUT HERE
#line 5 "TheSoccerDivOne.cpp"
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

const int MAXN=55,MAXM=MAXN*4*2+1;

int d[2][MAXM][MAXM];
class TheSoccerDivOne
{
	public:
		int find(vector <int> points)
		{
			int P=points[0]+4*3;
			int N=points.size(),M=N*4+1,Add=N*2;
			memset(d,-1,sizeof(d));
			d[0][4+Add][0]=0;
			for(int i=0;i<N-1;i++)
			{
				int (*f)[MAXM]=d[i&1];
				int (*g)[MAXM]=d[~i&1];
				memset(g,-1,sizeof(d[0]));
				for(int j=0;j<M;j++)
					for(int k=0;k<=Add;k++)
						if (f[j][k]!=-1)
						{
							for(int s=0;s<=4;s++)
								for(int t=0;s+t<=4;t++)
								{
									int q=4-s-t;
									int nj=j+s-t;
									if (nj<0 || nj>=M)
										continue;
									for(int nq=0;nq<=q;nq++)
									{
										int nk=abs(k-nq)+q-nq;
										if (nk>Add)
											continue;
										int nc=points[i+1]+s*3+q;
										int nd=f[j][k]+(nc>P);
										if (g[nj][nk]==-1 || g[nj][nk]>nd)
											g[nj][nk]=nd;
									}
								}
						}
			}
			return d[(N-1)&1][0+Add][0]+1;
		}
		
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {0, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 9, 9, 9, 9}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; verify_case(0, Arg1, find(Arg0)); }
	void test_case_1() { int Arr0[] = {5, 18, 21, 19}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 4; verify_case(1, Arg1, find(Arg0)); }
	void test_case_2() { int Arr0[] = {4, 1, 5}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; verify_case(2, Arg1, find(Arg0)); }
	void test_case_3() { int Arr0[] = {4, 16, 4, 16, 16}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; verify_case(3, Arg1, find(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{
	TheSoccerDivOne ___test;
	___test.run_test(0);
	return 0;
}
// END CUT HERE
