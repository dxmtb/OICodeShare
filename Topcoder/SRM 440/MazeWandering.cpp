// BEGIN CUT HERE

// END CUT HERE
#line 5 "MazeWandering.cpp"
#include <vector>
#include <cstdio>
#include <algorithm>
#include <string>
#include <cstdlib>
#include <cmath>
#include <sstream>
#include <iostream>
#include <map>
#include <cstring>
using namespace std;

const int MAXM=50*50;
const int way[4][2]={{0,1},{0,-1},{1,0},{-1,0}};
const double eps=1e-9;

int son[MAXM];
inline void addedge(int u,int v)
{
	son[u]++;
}

int tot;
map<pair<int,int>,int> hash;
inline int getnum(int x,int y)
{
	pair<int,int> now(x,y);
	map<pair<int,int>,int>::iterator it=hash.find(now);
	if (it!=hash.end())
		return it->second;
	hash[now]=tot++;
	return tot-1;
}

double a[MAXM][MAXM];
double b[MAXM];
class MazeWandering
{
	public:
		double expectedTime(vector <string> maze)
		{
			int n=maze.size(),m=maze[0].size();
			for(int i=0;i<n;i++)
				for(int j=0;j<m;j++)
					if (maze[i][j]!='X')
					{
						int now=getnum(i,j);
						if (maze[i][j]=='*')
						{
							a[now][now]=1;
							b[now]=0;
							continue;
						}
						for(int k=0;k<4;k++)
						{
							int x=i+way[k][0],y=j+way[k][1];
							if (x>=0 && x<n && y>=0 && y<m && maze[x][y]!='X')
								addedge(now,getnum(x,y));
						}
						a[now][now]=1;
						b[now]=1;
						for(int k=0;k<4;k++)
						{
							int x=i+way[k][0],y=j+way[k][1];
							if (x>=0 && x<n && y>=0 && y<m && maze[x][y]!='X')
								a[now][getnum(x,y)]=-1.0/son[now];
						}
					}
			for(int i=0;i<tot;i++)
			{
				for(int j=0;j<tot;j++)
					if (i!=j && a[j][i]!=0)
					{
						double mul=a[j][i]/a[i][i];
						for(int k=i;k<tot;k++)
							a[j][k]=a[j][k]-a[i][k]*mul;
						b[j]=b[j]-b[i]*mul;
					}
			}
			double re=0;
			for(int i=0;i<tot;i++)
				re+=b[i]/a[i][i];
			return re/tot;
		}
		
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const double &Expected, const double &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"*",
 "."}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); double Arg1 = 0.5; verify_case(0, Arg1, expectedTime(Arg0)); }
	void test_case_1() { string Arr0[] = {"*.."}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); double Arg1 = 2.3333333333333335; verify_case(1, Arg1, expectedTime(Arg0)); }
	void test_case_2() { string Arr0[] = {"...",
 "X*X",
 "..."}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); double Arg1 = 4.857142857142857; verify_case(2, Arg1, expectedTime(Arg0)); }
	void test_case_3() { string Arr0[] = {".*.",
 ".XX",
 "..."}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); double Arg1 = 13.714285714285714; verify_case(3, Arg1, expectedTime(Arg0)); }
	void test_case_4() { string Arr0[] = {"*........",
 "XXX.XXXX.",
 ".XX.X....",
 ".....XX.X"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); double Arg1 = 167.2608695652174; verify_case(4, Arg1, expectedTime(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{
	MazeWandering ___test;
	___test.run_test(1);
	return 0;
}
// END CUT HERE
