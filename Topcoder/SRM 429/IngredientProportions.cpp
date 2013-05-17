// BEGIN CUT HERE

// END CUT HERE
#line 5 "IngredientProportions.cpp"
#include <vector>
#include <cstdio>
#include <algorithm>
#include <string>
#include <cstdlib>
#include <cmath>
#include <sstream>
#include <iostream>
using namespace std;

typedef long long s64;


inline s64 gcd(s64 a,s64 b)
{
	if (a<0)
		a=-a;
	if (b<0)
		b=-b;
	while(b)
	{
		s64 t=a%b;
		a=b;
		b=t;
	}
	return a;
}

inline s64 lcm(s64 a,s64 b)
{
	return a*b/gcd(a,b);
}

const int MAXN=15;

s64 mat[MAXN][MAXN];
class IngredientProportions
{
	public:
		vector <int> getMasses(vector <string> proportions)
		{
			int N=proportions.size()+1;
			for(int i=0;i<N-1;i++)
			{
				const string &str=proportions[i];
				string ins;
				for(int j=0;j<(int)str.size();j++)
					if (str[j]>='0' && str[j]<='9')
						ins+=str[j];
					else if (str[j]==' '|| str[j]==':')
						ins+=' ';
				stringstream in(ins);
				int a,b,p,q;
				in>>a>>b>>p>>q;
				int d=gcd(p,q);
				mat[i][a]=q/d;
				mat[i][b]=-p/d;
			}
			for(int i=0;i<N-1;i++)
			{
				for(int j=i;j<N-1;j++)
					if (mat[j][i]!=0)
					{
						if (j!=i)
							for(int k=i;k<N;k++)
								swap(mat[j][k],mat[i][k]);
						break;
					}
				for(int j=0;j<N-1;j++)
				if (j!=i && mat[j][i]!=0)
				{
					s64 d=gcd(mat[i][i],mat[j][i]);
					s64 t1=mat[i][i]/d,t2=mat[j][i]/d;
					for(int k=0;k<N;k++)
						mat[j][k]=mat[j][k]*t1-mat[i][k]*t2;
				}
			}
			s64 wn=1;
			for(int i=0;i<N-1;i++)
			{
				s64 k1=mat[i][i],k2=mat[i][N-1];
				if (k1<0) k1=-k1;
				else k2=-k2;
				wn=lcm(wn,k1/gcd(k1,k2));
			}
			vector<int> re(N,0);
			re[N-1]=wn;
			for(int i=0;i<N-1;i++)
			{
				s64 k1=mat[i][i],k2=mat[i][N-1];
				if (k1<0) k1=-k1;
				else k2=-k2;
				re[i]=k2*wn/k1;
			}
			return re;
		}
		
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const vector <int> &Expected, const vector <int> &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: " << print_array(Expected) << endl; cerr << "\tReceived: " << print_array(Received) << endl; } }
	void test_case_0() { string Arr0[] = {"#0 and #1 as 6:4"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {3, 2 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(0, Arg1, getMasses(Arg0)); }
	void test_case_1() { string Arr0[] = {"#0 and #1 as 9:8","#1 and #2 as 9:8"}
; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {81, 72, 64 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(1, Arg1, getMasses(Arg0)); }
	void test_case_2() { string Arr0[] = {"#4 and #0 as 1:1", "#4 and #1 as 3:1", "#4 and #2 as 5:1", "#4 and #3 as 7:1"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {105, 35, 21, 15, 105 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(2, Arg1, getMasses(Arg0)); }
	void test_case_3() { string Arr0[] = {"#2 and #3 as 6:8", "#0 and #1 as 9:3", "#3 and #0 as 7:5"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {60, 20, 63, 84 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(3, Arg1, getMasses(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{
	IngredientProportions ___test;
	___test.run_test(1);
	return 0;
}
// END CUT HERE
