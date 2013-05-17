/*
ID: dxmtb
PROG: 宠物收养所
TIME: 2010.11.19
STATE: Solved
MEMO: STL RB-tree
*/
#include <cstdio>
#include <set>
using namespace std;

const int MAXN=80000;
const int MAXINT=0x7fffffff;

set<int> tree;

inline int abs(int a)
{return a<0?-a:a;}

int n,re;
int s;
int a[MAXN];

int main()
{
	freopen("pet.in","r",stdin);
	freopen("pet.out","w",stdout);
	scanf("%d",&n);
	for(int i=0;i<n;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		if (x==s||tree.size()==0)
		{
			tree.insert(y);
			s=x;
			continue;
		}
		set<int>::iterator it1,it2;
		it1=it2=tree.lower_bound(y);
		if (it1!=tree.begin()) it1--;
		else it1=tree.end();
		if (it1!=tree.end()&&(it2==tree.end()||y-*it1<=*it2-y))
		{	
			re+=y-*it1;
			tree.erase(it1);
		}
		else
		{
			re+=*it2-y;
			tree.erase(it2);
		}
		re%=1000000;
	}
	printf("%d\n",re);
	return 0;
}
