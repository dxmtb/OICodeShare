/*
ID: dxmtb
PROG: 著名医生的药方
TIME: 2010.10.27
STATE: Solved
MEMO: 搜索+卡时
*/
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <iostream>
#include <sstream>
using namespace std;

const int MAXN=505;

int adj[MAXN][MAXN];
int n,p;
int fangzi[MAXN];
int total;
bool cot[MAXN];
stringstream re;

void add(int a,int b)
{
	adj[a][++adj[a][0]]=b;
}

int use[MAXN],nodesum;

void search(int dep)
{
//	printf("%d\n",dep);
	nodesum++;
	if (dep==p)
	{
		total++;
		re<<fangzi[1];
		for(int i=2;i<=p;i++)
			re<<' '<<fangzi[i];
		re<<'\n';
		return ;
	}
	if (nodesum>1000000)
		return ;
	int now=fangzi[dep];
	if (fangzi[dep+1]) 
	{
		if (use[fangzi[dep+1]]>1)
			return ;
		if (dep)
			for(int i=1;i<=adj[now][0];i++)
				if (adj[now][i]!=fangzi[dep+1]&&cot[adj[now][i]])
					return ;
		for(int i=1;i<=adj[now][0];i++)
			if (adj[now][i]==fangzi[dep+1])
			{
				if (dep)
					for(int j=1;j<=adj[now][0];j++)
						use[adj[now][j]]++;
				else use[adj[now][i]]++;
				cot[adj[now][i]]=false;
				search(dep+1);
				if (dep)
					for(int j=1;j<=adj[now][0];j++)
						use[adj[now][j]]--;
				else use[adj[now][i]]--;
				cot[adj[now][i]]=true;
				break;
			}
	}
	else
	{
		if (dep)
			for(int i=1;i<=adj[now][0];i++)
				if (adj[now][i]!=fangzi[dep+1]&&cot[adj[now][i]])
					return ;
		for(int i=1;i<=adj[now][0];i++)
			if (!use[adj[now][i]])
			{
				if (dep)
					for(int j=1;j<=adj[now][0];j++)
						use[adj[now][j]]++;
				else use[adj[now][i]]++;
				fangzi[dep+1]=adj[now][i];
				search(dep+1);
				fangzi[dep+1]=0;
				if (dep)
					for(int j=1;j<=adj[now][0];j++)
						use[adj[now][j]]--;
				else use[adj[now][i]]--;
			}
	}
}

int main()
{
	freopen("doctor.in","r",stdin);
	freopen("doctor.out","w",stdout);
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		string str;
		do getline(cin,str);
		while(str=="\r");
		stringstream strin(str);
		for(int x;strin>>x;)
			add(i,x);
	}
	for(int i=1;i<=n;i++)
		use[i]=0;
	for(int i=0;i<n;i++)
		sort(adj[i]+1,adj[i]+adj[i][0]+1);
	cin>>p;
	for(int i=1;i<=p;i++)
	{
		cin>>fangzi[i];
		if (fangzi[i])
		{
			use[fangzi[i]]++;
			cot[fangzi[i]]=true;
		}
	}
	fangzi[0]=n+1;
	for(int i=1;i<=n;i++)
		add(n+1,i);
	search(0);
	cout<<total<<'\n'<<re.str();
	return 0;
}
