// BEGIN CUT HERE

// END CUT HERE
#line 5 "LongStraightRoad.cpp"
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

const int MAXN=55;
const int oo=~0u>>2;
#define pb push_back
#define mp make_pair

struct Node
{
	int u,v,w;
}pool[MAXN*MAXN],*mem=pool;

inline void addedge(int u,int v,int w)
{
	mem->u=u,mem->v=v,mem->w=w;
	mem++;
}

map<string,int>  hash;
int tot;
int getnum(const string &str)
{
	map<string,int>::iterator it=hash.find(str);
	int ret;
	if (it==hash.end())
		hash[str]=ret=tot++;
	else
		ret=it->second;
	return ret;
}

int dis[MAXN][MAXN];
int dist[MAXN];
int N;
class LongStraightRoad
{
	public:
		bool spfa()
		{
			queue<pair<int,int> > q;
			for(int i=0;i<N;i++)
				for(int j=i+1;j<N;j++)
					if (dis[i][j]!=-1)
						q.push(mp(i,j));
			while(q.size())
			{
				int s=q.front().first,t=q.front().second;
				q.pop();
				for(int k=0;k<s;k++)
					if (dis[k][s]!=-1)
					{
						int nd=dis[k][s]+dis[s][t];
						if (dis[k][t]!=-1)
						{
							if (nd!=dis[k][t])
								return false;
						}
						else
						{
							dis[k][t]=dis[k][s]+dis[s][t];
							q.push(mp(k,t));
						}
					}
				for(int k=s+1;k<t;k++)
					if (dis[s][k]!=-1 || dis[k][t]!=-1)
					{
						if (dis[s][k]!=-1 && dis[k][t]!=-1)
						{
							if (dis[s][k]+dis[k][t]!=dis[s][t])
								return false;
						}
						else
						{
							if (dis[s][k]!=-1)
							{
								dis[k][t]=dis[s][t]-dis[s][k];
								q.push(mp(k,t));
							}
							else
							{
								dis[s][k]=dis[s][t]-dis[k][t];
								q.push(mp(s,k));
							}
						}
					}
				for(int k=t+1;k<N;k++)
					if (dis[t][k]!=-1)
					{
						int nd=dis[s][t]+dis[t][k];
						if (dis[s][k]!=-1)
						{
							if (nd!=dis[s][k])
								return false;
						}
						else
						{
							dis[s][k]=dis[s][t]+dis[t][k];
							q.push(mp(s,k));
						}
					}
			}
			return true;
		}
		int distanceToDestination(vector <string> signs, string destination)
		{
			N=signs.size();
			for(int i=0;i<N;i++)
				for(int j=0;j<(int)signs[i].size();j++)
					if (signs[i][j]==';')
						signs[i][j]=' ';
			hash.clear();
			tot=0;
			int T=getnum(destination);
			vector<pair<int,int> > v[MAXN];
			for(int i=0;i<N;i++)
			{
				stringstream in(signs[i]);
				string str;
				int x;
				while(in>>str>>x)
				{
					int a=getnum(str);
					v[i].pb(mp(a,x));
				}
				sort(v[i].begin(),v[i].end());
			}
			memset(dis,-1,sizeof(dis));
			mem=pool;
			for(int i=0;i<N;i++)
				for(int j=i+1;j<N;j++)
				{
					for(int a=0,b=0;a<(int)v[i].size();a++)
					{
						while(b<(int)v[j].size() && v[j][b].first<v[i][a].first)
							b++;
						if (b<(int)v[j].size())
						{
							if (v[i][a].first==v[j][b].first)
							{
								int nd=v[i][a].second-v[j][b].second;
								if (nd<=0)
									return -1;
								if (dis[i][j]==nd)
									continue;
								if (dis[i][j]==-1)
								{
									dis[i][j]=nd;
									addedge(j,i,nd*MAXN);
									addedge(i,j,-nd*MAXN);
								}
								else
									return -1;
							}
						}
						else
							break;
					}
				}
			if (!spfa())
				return -1;
			int ans=-1;
			for(int i=0;i<N;i++)
				if (i==N-1 || dis[i][N-1]!=-1)
				for(int j=0;j<(int)v[i].size();j++)
					if (v[i][j].first==T)
					{
						ans=v[i][j].second;
						if (i!=N-1)
							ans-=dis[i][N-1];
						break;
					}
			if (ans<0)
				return -1;
			for(int i=0;i+1<N;i++)
				addedge(i,i+1,-1);
			for(int i=0;i<N;i++)
				addedge(N,i,0);
			for(int i=0;i<N;i++)
				dist[i]=oo;
			dist[N]=0;
			bool flag=true;
			for(int i=0;i<N+1 && flag;i++)
			{
				flag=false;
				for(Node *p=pool;p<mem;p++)
					if (dist[p->u]!=oo && dist[p->v]>dist[p->u]+p->w)
					{
						dist[p->v]=dist[p->u]+p->w;
						flag=true;
					}
			}
			if (flag)
				return -1;
			return ans;
		}
		
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"A 12", "B 20", "B 10", "A 10"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "A"; int Arg2 = -1; verify_case(0, Arg2, distanceToDestination(Arg0, Arg1)); }
	void test_case_1() { string Arr0[] = {"COLCHESTER 5;GLASTONBURY 25;MARLBOROUGH 13"
,"GLASTONBURY 13;MARLBOROUGH 2"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "GLASTONBURY"; int Arg2 = -1; verify_case(1, Arg2, distanceToDestination(Arg0, Arg1)); }
	void test_case_2() { string Arr0[] = {"A 25;B 15"
,"A 2"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "B"; int Arg2 = -1; verify_case(2, Arg2, distanceToDestination(Arg0, Arg1)); }
	void test_case_3() { string Arr0[] = {"YVO 60;J 62"
,"K 45"
,"K 40;MV 17"
,"K 37;YVO 44;HY 48;CC 69;D 77;YXF 80"
,"YVO 30;B 37;RB 59"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "MV"; int Arg2 = 0; verify_case(3, Arg2, distanceToDestination(Arg0, Arg1)); }
	void test_case_4() { string Arr0[] = {"A 200;B 150"
,"C 45;D 100;E 150"
,"C 25;E 130"
,"F 80;G 65"
,"G 35;H 160"
,"A 160"
,"H 130"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "F"; int Arg2 = -1; verify_case(4, Arg2, distanceToDestination(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{
	LongStraightRoad ___test;
	___test.run_test(0);
	return 0;
}
// END CUT HERE
