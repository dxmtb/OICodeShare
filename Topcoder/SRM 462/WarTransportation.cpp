// BEGIN CUT HERE

// END CUT HERE
#line 5 "WarTransportation.cpp"
#include <vector>
#include <cstdio>
#include <algorithm>
#include <string>
#include <cstdlib>
#include <cmath>
#include <sstream>
#include <iostream>
using namespace std;

const int MAXN=1005;
const int oo=~0u>>2;

class WarTransportation
{
	public:
		int dis[MAXN],f[MAXN];
		int N,M;
		int Q[MAXN],P[MAXN],W[MAXN];
		inline void Min(int &a,int b)
		{
			if (b<a)
				a=b;
		}
		inline void Max(int &a,int b)
		{
			if (b>a)
				a=b;
		}
		void doit(int s,int cut)
		{
			for(int i=0;i<N;i++)
				dis[i]=oo;
			dis[s]=0;
			for(int i=0;i<N;i++)
				for(int j=0;j<M;j++)
					if (j!=cut)
						Min(dis[Q[j]],dis[P[j]]+W[j]);
		}
		int messenger(int _n, vector <string> highways)
		{
			N=_n;
			string str;
			for(int i=0;i<(int)highways.size();i++)
				str+=highways[i];
			for(int i=0;i<(int)str.size();i++)
				if (str[i]==',')
					str[i]=' ';
			stringstream in(str);
			M=0;
			while(in>>P[M]>>Q[M]>>W[M])
			{
				P[M]--;
				Q[M]--;
				M++;
			}
			for(int i=0;i<N;i++)
			{
				doit(i,-1);
				f[i]=dis[1];
				for(int j=0;j<M;j++)
					if (P[j]==i)
					{
						doit(i,j);
						Max(f[i],dis[1]);
					}
			}
			for(int i=0;i<N;i++)
				dis[i]=oo;
			dis[1]=0;
			for(int j=0;j<N;j++)
				for(int i=0;i<M;i++)
					Min(dis[P[i]],max(f[P[i]],dis[Q[i]]+W[i]));
			if (dis[0]==oo)
				return -1;
			return dis[0];
		}
		
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 3; string Arr1[] = {"1 2 1,1 3 2,3 2 3"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 5; verify_case(0, Arg2, messenger(Arg0, Arg1)); }
	void test_case_1() { int Arg0 = 8; string Arr1[] = {"1 3 1,1 4 1,3 5 1,4 5 1,5 6 1,6 7 1,6 8 1,7 2 1,",
 "8 2 1"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = -1; verify_case(1, Arg2, messenger(Arg0, Arg1)); }
	void test_case_2() { int Arg0 = 4; string Arr1[] = {"1 3 1,1 3 2,3 2 1,1 4 1,4 2 1"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = -1; verify_case(2, Arg2, messenger(Arg0, Arg1)); }
	void test_case_3() { int Arg0 = 4; string Arr1[] = {"1 3 1,3 2 1,1 4 1,4 2 1,3 4 1"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 3; verify_case(3, Arg2, messenger(Arg0, Arg1)); }
	void test_case_4() { int Arg0 = 20; string Arr1[] = {"1 13 3,13 4 7,4 3 4,3 10 8,10 18 9,18 12 6,12 2 3,",
 "1 17 6,17 13 6,13 9 4,9 10 8,10 7 2,7 5 5,5 19 9,1",
 "9 14 6,14 16 9,16 18 7,18 15 5,15 20 3,20 12 9,12 ",
 "8 4,8 11 3,11 4 1,4 3 7,3 2 3,20 10 2,1 18 2,16 19",
 " 9,4 15 9,13 15 6"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 23; verify_case(4, Arg2, messenger(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{
	WarTransportation ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
