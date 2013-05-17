/*
 * Problem: [JSOI2007]麻将
 * Time: 2011.06.22
 * Author: dxmtb
 * State: Solved
 * Memo: dp + 记忆化搜索
*/
#include <cstdio>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;

const int MAXN=505;

int N;
map<pair<int,int>,bool> hash[MAXN][MAXN];
int tot[MAXN];
inline bool yes(bool sta,int dep,int a1,int a2)
{
	if (dep==N+1)
		return sta;
	map<pair<int,int>,bool>::iterator it=hash[sta][dep].find(make_pair(a1,a2));
	if (it!=hash[sta][dep].end())
		return it->second;
	bool flag=false;
	if (!sta && a1>=2)
		flag=yes(1,dep,a1-2,a2);
	for(int i=a1/3;i>=0 && !flag;i--)
	{
		int left=a1-i*3;
		if (a2>=left && tot[dep+2]>=left)
		{
			if (yes(sta,dep+1,a2-left,tot[dep+2]-left))
			{
				flag=true;
				break;
			}
		}
		else break;
	}
	return hash[sta][dep][make_pair(a1,a2)]=flag;
}

int main()
{
	freopen("1028.in","r",stdin);
	int M;
	scanf("%d%d",&N,&M);
	for(int i=0;i<3*M+1;i++)
	{
		int x;
		scanf("%d",&x);
		tot[x]++;
	}
	vector<int> v;
	for(int i=N;i;i--)
	{
		tot[i]++;
		for(int j=1;j<=i-2;j++)
		{
			hash[0][j].clear();
			hash[1][j].clear();
		}
		if (yes(0,1,tot[1],tot[2]))
			v.push_back(i);
		tot[i]--;
	}
	if (!v.size())
		printf("NO\n");
	else
	{
		reverse(v.begin(),v.end());
		printf("%d",v[0]);
		for(int i=1;i<(int)v.size();i++)
			printf(" %d",v[i]);
		printf("\n");
	}
	return 0;
}
