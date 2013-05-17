// BEGIN CUT HERE

// END CUT HERE
#line 5 "RightTriangle.cpp"
#include <vector>
#include <cstdio>
#include <algorithm>
#include <string>
#include <cstdlib>
#include <cmath>
#include <sstream>
#include <cstring>
#include <iostream>
using namespace std;

const int MAXN=1000005;
typedef long long s64;

int father[MAXN];
bool used[MAXN];
int sum[MAXN];

int getfather(int x)
{
	if (father[x]==x)
		return x;
	return father[x]=getfather(father[x]);
}

inline void join(int u,int v)
{
	int fx=getfather(u),fy=getfather(v);
	father[fx]=fy;
}

class RightTriangle
{
	public:
		long long triangleCount(int N, int M, int a, int b, int c)
		{
			if (N%2==1)
				return 0;
			memset(used,false,sizeof(used));
			for(int i=0;i<=N;i++)
				father[i]=i;
			for(int i=0;i<M;i++)
			{
				int u=((s64)a*i*i+(s64)b*i+c)%N;
				int v=getfather(u);
				if (v==N)
					v=getfather(0);
				used[v]=true;
				join(v,v+1);
			}
			sum[0]=used[0];
			for(int i=1;i<N;i++)
				sum[i]=sum[i-1]+used[i];
			s64 re=0;
			for(int i=0;i<N/2;i++)
				if (used[i])
				{
					int j=i+N/2;
					if (used[j])
					{
						if (i)
							re+=sum[i-1];
						re+=sum[N-1]-sum[j];
						re+=sum[j-1]-sum[i];
					}
				}
			return re;
		}
		
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 9; int Arg1 = 3; int Arg2 = 0; int Arg3 = 3; int Arg4 = 0; long long Arg5 = 0LL; verify_case(0, Arg5, triangleCount(Arg0, Arg1, Arg2, Arg3, Arg4)); }
	void test_case_1() { int Arg0 = 40; int Arg1 = 3; int Arg2 = 5; int Arg3 = 0; int Arg4 = 0; long long Arg5 = 1LL; verify_case(1, Arg5, triangleCount(Arg0, Arg1, Arg2, Arg3, Arg4)); }
	void test_case_2() { int Arg0 = 4; int Arg1 = 4; int Arg2 = 16; int Arg3 = 24; int Arg4 = 17; long long Arg5 = 4LL; verify_case(2, Arg5, triangleCount(Arg0, Arg1, Arg2, Arg3, Arg4)); }
	void test_case_3() { int Arg0 = 1000000; int Arg1 = 47000; int Arg2 = 0; int Arg3 = 2; int Arg4 = 5; long long Arg5 = 0LL; verify_case(3, Arg5, triangleCount(Arg0, Arg1, Arg2, Arg3, Arg4)); }
	void test_case_4() { int Arg0 = 200000; int Arg1 = 700; int Arg2 = 123456; int Arg3 = 789012; int Arg4 = 345678; long long Arg5 = 6980LL; verify_case(4, Arg5, triangleCount(Arg0, Arg1, Arg2, Arg3, Arg4)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{
	RightTriangle ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
