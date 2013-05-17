// BEGIN CUT HERE

// END CUT HERE
#line 5 "SquareFreeSets.cpp"
#include <vector>
#include <cstdio>
#include <algorithm>
#include <string>
#include <cstdlib>
#include <cmath>
#include <sstream>
#include <iostream>
#include <map>
using namespace std;

const int MO=1000000007;
const int MAXN=505;

map<pair<pair<int,int>,vector<int> >,int> hash;
int tot,re,N,K;
bool flag[MAXN];
int prime[MAXN];

inline int mod(int x)
{
	x%=MO;
	if (x<0)
		x+=MO;
	return x;
}

class SquareFreeSets
{
	public:
		void dfs(int dep,int del,vector<int> now)
		{
			if (dep==tot)
			{
				if (now.size()+del)
					re=mod(re+1);
				return ;
			}
			sort(now.begin(),now.end());
			while(now.size() && now.back()*prime[dep]>N)
			{
				del++;
				now.pop_back();
			}
			map<pair<pair<int,int>,vector<int> >,int>::iterator it;
			pair<pair<int,int>,vector<int> > sta=make_pair(make_pair(dep,del),now);
			it=hash.find(sta);
			if (it!=hash.end())
				re=mod(re+it->second);
			else
			{
				int tre=re;
				dfs(dep+1,del,now);
				for(int i=0;i<(int)now.size();i++)
				{
					now[i]*=prime[dep];
					dfs(dep+1,del,now);
					now[i]/=prime[dep];
				}
				if (del+(int)now.size()+1<=K)
				{
					now.push_back(prime[dep]);
					dfs(dep+1,del,now);
					now.pop_back();
				}
				hash[sta]=mod(re-tre);
			}
		}
		int countPerfect(int n, int k)
		{
			N=n,K=k;
			for(int i=2;i<=N;i++)
				flag[i]=true;
			for(int i=2;i<=N;i++)
				if (flag[i])
				{
					prime[tot++]=i;
					for(int j=i+i;j<=N;j+=i)
						flag[j]=false;
				}
			dfs(0,0,vector<int>());
			return mod(re);
		}
		
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 5; int Arg1 = 1; int Arg2 = 3; verify_case(0, Arg2, countPerfect(Arg0, Arg1)); }
	void test_case_1() { int Arg0 = 5; int Arg1 = 2; int Arg2 = 6; verify_case(1, Arg2, countPerfect(Arg0, Arg1)); }
	void test_case_2() { int Arg0 = 5; int Arg1 = 3; int Arg2 = 7; verify_case(2, Arg2, countPerfect(Arg0, Arg1)); }
	void test_case_3() { int Arg0 = 6; int Arg1 = 3; int Arg2 = 9; verify_case(3, Arg2, countPerfect(Arg0, Arg1)); }
	void test_case_4() { int Arg0 = 28; int Arg1 = 41; int Arg2 = 1599; verify_case(4, Arg2, countPerfect(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{
	SquareFreeSets ___test;
	___test.run_test(1);
	return 0;
}
// END CUT HERE
