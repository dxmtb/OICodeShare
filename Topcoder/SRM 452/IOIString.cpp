// BEGIN CUT HERE

// END CUT HERE
#line 5 "IOIString.cpp"
#include <vector>
#include <cstdio>
#include <algorithm>
#include <string>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <sstream>
#include <iostream>
using namespace std;

const int MO=1E9+7;
const int MAXN=2505;

int sum[MAXN];
class IOIString
{
	public:
		int countIOIs(vector <string> mask)
		{
			string str;
			for(int i=0;i<(int)mask.size();i++)
				str+=mask[i];
			int N=str.size();
			int re=1;
			for(int i=0;i<N;i++)
				if (str[i]=='?')
					re=re*2%MO;
			memset(sum,0,sizeof(sum));
			sum[0]=str[0]=='I';
			for(int i=1;i<N;i++)
				sum[i]=sum[i-1]+(str[i]=='I');
			if (!sum[N-1])
				re--;
			for(int i=0;i<N;i++)
				if (str[i]!='O')
				{
					if (sum[N-1]-sum[i]==0)
						re--;
					for(int j=1;i+j<N;j+=2)
					{
						for(int k=1;i+j*k<N;k++)
						{
							if (str[i+j*k]=='O')
								break;
							if (sum[i+j*k-1]-sum[i+j*(k-1)]!=0)
								break;
							if (sum[N-1]-sum[i+j*k]==0)
								re--;
						}
					}
					if (str[i]=='I')
						break;
				}
			return (re+MO)%MO;
		}
		
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"IO?"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; verify_case(0, Arg1, countIOIs(Arg0)); }
	void test_case_1() { string Arr0[] = {"????"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 4; verify_case(1, Arg1, countIOIs(Arg0)); }
	void test_case_2() { string Arr0[] = {"?II"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; verify_case(2, Arg1, countIOIs(Arg0)); }
	void test_case_3() { string Arr0[] = {"I??O??I"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 16; verify_case(3, Arg1, countIOIs(Arg0)); }
	void test_case_4() { string Arr0[] = {"???I???????O???","???????????O??IO????????I???"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 438952513; verify_case(4, Arg1, countIOIs(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{
	IOIString ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
