// BEGIN CUT HERE

// END CUT HERE
#line 5 "SequenceOfCommands.cpp"
#include <vector>
#include <cstdio>
#include <algorithm>
#include <string>
#include <cstdlib>
#include <cmath>
#include <sstream>
#include <iostream>
using namespace std;

const int way[4][2]={{1,0},{0,1},{-1,0},{0,-1}};

class SequenceOfCommands
{
	public:
		string whatHappens(vector <string> commands)
		{
			int x=0,y=0,tl=0,tr=0,dir=0;
			for(int i=0;i<(int)commands.size();i++)
				for(int j=0;j<(int)commands[i].size();j++)
				{
					switch (commands[i][j])
					{
						case 'S':x+=way[dir][0],y+=way[dir][1];break;
						case 'L':tl++,dir=(dir+1)%4;break;
						case 'R':tr++,dir=(dir-1+4)%4;break;
					}
				}
			if ((x==0&&y==0) || (tl-tr)%4)
				return "bounded";
			else
				return "unbounded";
		}
		
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const string &Expected, const string &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"L"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "bounded"; verify_case(0, Arg1, whatHappens(Arg0)); }
	void test_case_1() { string Arr0[] = {"SRSL"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "unbounded"; verify_case(1, Arg1, whatHappens(Arg0)); }
	void test_case_2() { string Arr0[] = {"SSSS","R"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "bounded"; verify_case(2, Arg1, whatHappens(Arg0)); }
	void test_case_3() { string Arr0[] = {"SRSL","LLSSSSSSL","SSSSSS","L"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "unbounded"; verify_case(3, Arg1, whatHappens(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{
	SequenceOfCommands ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
