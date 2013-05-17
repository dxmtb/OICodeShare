// BEGIN CUT HERE

// END CUT HERE
#line 5 "SpecificPolyominoCovering.cpp"
#include <vector>
#include <cstdio>
#include <algorithm>
#include <string>
#include <cstdlib>
#include <cmath>
#include <sstream>
#include <iostream>
using namespace std;

const int MAXN=55;

int before[MAXN][MAXN];

class SpecificPolyominoCovering
{
	public:
		int N,M;
		vector<string> re;
		vector<string> now;
		void puta(int n,int m)
		{
			now[n][m]=now[n][m+3]=now[n+1][m]=now[n+1][m+1]=now[n+1][m+2]=now[n+1][m+3]='A';
			if (now[n][m+1]=='X')
				now[n][m+1]=now[n][m+2]='B';
		}
		void reca(int n,int m)
		{
			now[n][m]=now[n][m+3]=now[n+1][m]=now[n+1][m+1]=now[n+1][m+2]=now[n+1][m+3]='X';
			if (now[n][m+1]=='B')
				now[n][m+1]=now[n][m+2]='X';
		}
		void putb(int n,int m)
		{
			now[n][m]=now[n][m+1]='B';
		}	
		void recb(int n,int m)
		{
			now[n][m]=now[n][m+1]='X';
		}	
#define chk(x,y) ((x)<N && (y)<M && now[x][y]=='X')
#define che(x,y) ((x)<N && (y)<M && now[x][y]=='.')
		inline bool checka(int n,int m)
		{
			return chk(n,m) && ((chk(n,m+1) && chk(n,m+2)) || ( che(n,m+1) && che(n,m+2)))
				&& chk(n,m+3) && chk(n+1,m)
				&& chk(n+1,m+1) && chk(n+1,m+2) &&
				chk(n+1,m+3);
		}
		inline bool checkb(int n,int m)
		{
			return chk(n,m) && chk(n,m+1);
		}
#undef chk
#undef che
		bool dfs(int n,int m)
		{
			if (n==N)
			{
				re=now;
				return true;
			}
			if (m==M)
				return dfs(n+1,0);
			if (now[n][m]!='X')
				return dfs(n,m+1);
			if (checka(n,m))
			{
				int t=before[n+1][m];
				if (t%2==0 || (m-t-3>=0 && checka(n+1,m-t-3)))
				{
					puta(n,m);
					if (dfs(n,m+4))
						return true;
					reca(n,m);
				}
			}
			if (checkb(n,m))
			{
				putb(n,m);
				if (dfs(n,m+2))
					return true;
				recb(n,m);
			}
			return false;
		}
		vector <string> findCovering(vector <string> region)
		{
			N=region.size(),M=region[0].size();
			now=region;
			re.clear();
			for(int i=0;i<N;i++)
			{
				int tot=0;
				for(int j=0;j<M;j++)
					if (region[i][j]=='X')
						tot++;
				if (tot%2)
					return re;
			}
			for(int i=0;i<N;i++)
				for(int j=1;j<M-1;j++)
					if (region[i][j]=='X' && region[i][j-1]=='.' && region[i][j+1]=='.')
						if (!checka(i,j) && !checka(i,j-3))
								return re;
			for(int i=0;i<N;i++)
			{
				before[i][0]=0;
				for(int j=1;j<M;j++)
					if (region[i][j-1]=='.')
						before[i][j]=0;
					else
						before[i][j]=before[i][j-1]+1;
			}
			for(int i=0;i<N;i++)
				for(int j=1;j<M;j++)
					if (region[i][j]=='.' && (j-1>=0 || region[i][j-1]=='X'))
					{
						int t=before[i][j];
						if (t%2==1 && !checka(i,j-t-3) && !checka(i,j-1))
							return re;
					}
			dfs(0,0);
			return re;
		}
		
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const vector <string> &Expected, const vector <string> &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: " << print_array(Expected) << endl; cerr << "\tReceived: " << print_array(Received) << endl; } }
	void test_case_0() { string Arr0[] = {"XXXX",
 "XXXX"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"ABBA", "AAAA" }; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(0, Arg1, findCovering(Arg0)); }
	void test_case_1() { string Arr0[] = {"X..XXXX..X",
 "XXXX..XXXX"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"A..ABBA..A", "AAAA..AAAA" }; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(1, Arg1, findCovering(Arg0)); }
	void test_case_2() { string Arr0[] = {"XXXXXX",
 "XXXXXX",
 "XXXXXX"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"ABBABB", "AAAABB", "BBBBBB" }; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(2, Arg1, findCovering(Arg0)); }
	void test_case_3() { string Arr0[] = {"X..XX",
 "XXXXX"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = { }; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(3, Arg1, findCovering(Arg0)); }
	void test_case_4() { string Arr0[] = {"XXXXXXXXXX",
 "XXXXXXXXXX",
 "XXXXXXXXXX",
 "XXXXX..XXX",
 "XXXXXXXXXX",
 "XXXXXXXXXX",
 "XXXXXXXXXX"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"ABBAABBABB", "AAAAAAAABB", "ABBABBBBBB", "AAAAA..ABB", "ABBAAAAABB", "AAAAABBABB", "BBBBAAAABB" }; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(4, Arg1, findCovering(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{
	SpecificPolyominoCovering ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
