/*
ID: dxmtb
PROG: [SHOI2008]汉诺塔
TIME: 2011.03.29
STATE: Solved
MEMO: 找规律+递推
*/
#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;

char way[6][3];
vector<int> v[3];
int N,M;
int a[3];
int s,t;

int main()
{
	scanf("%d",&M);
	for(int i=0;i<6;i++)
	{
		scanf(" %s",way[i]);
		way[i][0]-='A';
		way[i][1]-='A';
	}
	for(N=1;N<=3;N++)
	{
		v[0].clear();v[1].clear();v[2].clear();
		for(int i=0;i<N;i++)
			v[0].push_back(N-i);
		int before=-1,step=0;
		while(true)
		{
			for(int i=0;i<6;i++)
			{
				int from=way[i][0],to=way[i][1];
				int t;
				if (way[i][0]!=before && v[from].size() &&
					 (v[to].empty() || (v[from].back())<v[to].back()))
				{
					t=v[from].back();
					v[from].pop_back();
					v[to].push_back(t);
					before=to;
					step++;
					break;
				}
			}
			if (v[before].size()==N)
			{
				a[N]=step;
				break;
			}
		}
	}
	s=(a[2]-a[3])/(a[1]-a[2]);
	t=a[2]-s*a[1];
	long long re=a[1];
	for(int i=2;i<=M;i++)
		re=re*s+t;
	cout<<re<<endl;
	return 0;
}
