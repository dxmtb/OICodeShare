// BEGIN CUT HERE

// END CUT HERE
#line 5 "PalindromizationDiv1.cpp"
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

const int MAXN=300;
const int oo=~0u>>2;

int add[MAXN],erase[MAXN];
int change[MAXN][MAXN];
int d[MAXN][MAXN];
class PalindromizationDiv1
{
	public:
		inline void Min(int &a,int b)
		{
			if (b<a)
				a=b;
		}
		int getMinimumCost(string str, vector <string> opt)
		{
			int N=str.size();
			memset(add,0,sizeof(add));
			memset(erase,0,sizeof(erase));
			memset(change,0,sizeof(change));
			for(int i=0;i<(int)opt.size();i++)
				if (opt[i][0]=='a')
				{
					char c;
					int x;
					sscanf(opt[i].c_str()+3," %c%d",&c,&x);
					add[c]=x;
				}
				else if (opt[i][0]=='e')
				{
					char c;
					int x;
					sscanf(opt[i].c_str()+5," %c%d",&c,&x);
					erase[c]=x;
				}
				else
				{
					char c1,c2;
					int x;
					sscanf(opt[i].c_str()+6," %c %c%d",&c1,&c2,&x);
					change[c1][c2]=x;
				}
			for(char k='a';k<='z';k++)
				for(char i='a';i<='z';i++)
					if (i!=k && change[i][k])
						for(char j='a';j<='z';j++)
							if (j!=i && j!=k && change[k][j])
							{
								if (change[i][j]==0)
									change[i][j]=change[i][k]+change[k][j];
								else
									Min(change[i][j],change[i][k]+change[k][j]);
							}
			for(int k=0;k<26*26*26;k++)
				for(char i='a';i<='z';i++)
					for(char j='a';j<='z';j++)
						if (i!=j && add[j] && change[j][i])
						{
							if (add[i]==0)
								add[i]=add[j]+change[j][i];
							else
								Min(add[i],add[j]+change[j][i]);
						}
			for(int k=0;k<26*26*26;k++)
				for(char i='a';i<='z';i++)
					for(char j='a';j<='z';j++)
						if (i!=j && erase[j] && change[i][j])
						{
							if (erase[i]==0)
								erase[i]=change[i][j]+erase[j];
							else
								Min(erase[i],change[i][j]+erase[j]);
						}
			for(int i=0;i<N;i++)
				for(int j=0;j<N;j++)
					d[i][j]=oo;
			for(int i=0;i<N;i++)
				d[i][i]=0;
			for(int i=0;i+1<N;i++)
				d[i+1][i]=0;
			for(int l=1;l<N;l++)
				for(int i=0,j;(j=i+l)<N;i++)
				{
					if (str[i]==str[j])
						Min(d[i][j],d[i+1][j-1]);
					if (erase[str[i]])
						Min(d[i][j],d[i+1][j]+erase[str[i]]);
					if (erase[str[j]])
						Min(d[i][j],d[i][j-1]+erase[str[j]]);
					if (add[str[i]])
						Min(d[i][j],d[i+1][j]+add[str[i]]);
					if (add[str[j]])
						Min(d[i][j],d[i][j-1]+add[str[j]]);
					if (change[str[i]][str[j]])
						Min(d[i][j],d[i+1][j-1]+change[str[i]][str[j]]);
					if (change[str[j]][str[i]])
						Min(d[i][j],d[i+1][j-1]+change[str[j]][str[i]]);
					for(char k='a';k<='z';k++)
					{
						if (k!=str[i] && change[str[i]][k] && add[k])
							Min(d[i][j],d[i+1][j]+change[str[i]][k]+add[k]);
						if (k!=str[j] && change[str[j]][k] && add[k])
							Min(d[i][j],d[i][j-1]+change[str[j]][k]+add[k]);
						if (k!=str[i] && k!=str[j] && change[str[i]][k] && change[str[j]][k])
							Min(d[i][j],d[i+1][j-1]+change[str[i]][k]+change[str[j]][k]);
					}
				}
			if (d[0][N-1]==oo)
				return -1;
			return d[0][N-1];
		}
		
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arg0 = "ltbgpjcsaknlzctionkqffrpevmybpptydvizassekdoznkln"; string Arr1[] ={"change g n 47673", "erase r 77264", "change l t 42081", "add r 4800", "add b 96464", "erase k 51662", "change b n 39898", "erase d 22461", "erase g 27854", "change p u 14295", "add d 51496", "add e 75369", "add o 87389", "change t z 27185", "change c z 71695", "change b l 54216", "add i 19003", "add f 27638", "add u 85866", "change j u 67802", "erase t 57582", "erase i 22054", "add k 10000", "change q b 34740", "add q 72938", "change x m 44234", "erase s 36666", "erase b 14907", "add h 69181", "erase f 99058", "change p b 90898", "erase l 21277", "add x 32316", "change c m 85633", "change v o 96383", "change y u 61797", "change h v 19755", "change p r 8901", "change n h 99960"} ; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 1629924; verify_case(0, Arg2, getMinimumCost(Arg0, Arg1)); }
	void test_case_1() { string Arg0 = "topcoder"; string Arr1[] = {"erase t 1", "erase o 1", "erase p 1", "erase c 1", "erase d 1", "erase e 1", "erase r 1"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 5; verify_case(1, Arg2, getMinimumCost(Arg0, Arg1)); }
	void test_case_2() { string Arg0 = "topcoder"; string Arr1[] = {"erase t 10", "erase o 1", "erase p 1", "erase c 1", "erase d 1", "erase e 1", "erase r 1"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 7; verify_case(2, Arg2, getMinimumCost(Arg0, Arg1)); }
	void test_case_3() { string Arg0 = "caaaaaab"; string Arr1[] = {"change b a 100000", "change c a 100000", "change c d 50000", "change b e 50000", "erase d 50000", "erase e 49999"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 199999; verify_case(3, Arg2, getMinimumCost(Arg0, Arg1)); }
	void test_case_4() { string Arg0 = "moon"; string Arr1[] = {"erase o 5", "add u 7", "change d p 3", "change m s 12", "change n d 6", "change s l 1"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = -1; verify_case(4, Arg2, getMinimumCost(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{
	PalindromizationDiv1 ___test;
	___test.run_test(0);
	return 0;
}
// END CUT HERE
