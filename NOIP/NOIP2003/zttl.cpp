/*
ID: dxmtb
PROG: NOIP2003 侦探推理
TIME: 2010.9.3
STATE: Solved
MEMO: 枚举
*/
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <vector>
using namespace std;

const int MAXN=25,MAXP=105;
const char week[][15]={"Monday","Tuesday","Wednesday","Thursday","Friday",
					"Saturday","Sunday"};

struct Node
{
	int u,v;
	Node(int a,int b):u(a),v(b){}
};

int m,n,p;
char name[MAXN][300];
vector<int> day[7];
vector<int> guity[MAXN];
vector<int> nguity[MAXN];
int status[MAXN];//0 true 1 false 2 unsettled
bool ag[MAXN][MAXN];
int re,man;

inline bool oppo(int i,int j)
{
	if (guity[i].size()&&nguity[j].size())
	for(vector<int>::iterator it=guity[i].begin();it<guity[i].end();
			it++)
		for(vector<int>::iterator it2=nguity[j].begin();it<nguity[j].end();
				it++)
			if (*it==*it2)
				return true;
	if (nguity[i].size()&&guity[j].size())
	for(vector<int>::iterator it=nguity[i].begin();it<guity[i].end();
			it++)
		for(vector<int>::iterator it2=guity[j].begin();it<nguity[j].end();
				it++)
			if (*it==*it2)
				return true;
	return false;
}

void init()
{
	scanf("%d%d%d\n",&n,&m,&p);
	for(int i=0;i<n;i++)
		scanf("%s\n",name[i]);
	for(int i=0;i<p;i++)
	{
		char na[300],evi[300],temp[300];
		int now;
		memset(na,0,sizeof(na));
		memset(evi,0,sizeof(evi));
		memset(temp,0,sizeof(temp));
		scanf("%s ",na);
		na[strlen(na)-1]=0;
		fgets(evi,sizeof(evi),stdin);
//		printf("%s %s\n",na,evi);
		for(int j=0;j<n;j++)
			if (strcmp(na,name[j])==0)
			{
				now=j;
				break;
			}
		if (strstr(evi," is guilty"))
		{
			sscanf(evi,"%s",temp);
			for(int j=0;j<n;j++)
				if (strcmp(temp,name[j])==0)
				{
					guity[now].push_back(j);
					break;
				}
		}
		else if (strstr(evi,"I am guilty"))
			guity[now].push_back(now);
		else if (strstr(evi,"Today is "))
		{
			sscanf(evi+9,"%s",temp);
			temp[strlen(temp)-1]=0;
			for(int j=0;j<7;j++)
			{
				int k;
				for(k=0;k<strlen(week[j]);k++)
					if (week[j][k]!=temp[k])
						break;
				if (k==strlen(week[j]))
				{
					day[j].push_back(now);
					break;
				}
			}
		}
		else if (strstr(evi," is not guilty"))
		{
			sscanf(evi,"%s",temp);
			for(int j=0;j<n;j++)
				if (strcmp(temp,name[j])==0)
				{
					nguity[now].push_back(j);
					break;
				}
		}
		else if (strstr(evi,"I am not guilty"))
			nguity[now].push_back(now);
	}
	for(int i=0;i<7;i++)
		if (day[i].size())
		for(int j=i+1;j<7;j++)
			if (day[j].size())
			for(vector<int>::iterator it=day[i].begin();it<day[i].end();
					it++)
				for(vector<int>::iterator it2=day[j].begin();it2<day[j].end();
						it2++)
					ag[*it][*it2]=ag[*it2][*it]=true;
	for(int i=0;i<n;i++)
		for(int j=i;j<n;j++)
			if (!ag[i][j]&&oppo(i,j))
				ag[i][j]=ag[j][i]=true;
}

void check(int ngu,int nday)
{
	int nf=0,nt=0;
	vector<int>::iterator it;
	for(int i=0;i<n;i++)
		status[i]=2;
	for(int i=0;i<7;i++)
		if (day[i].size()&&i!=nday)
			for(it=day[i].begin();it<day[i].end();it++)
				if (status[*it]==2)
					status[*it]=0,nf++;
				else printf("wrong!!");
	for(int i=0;i<n;i++)
	{
		for(it=guity[i].begin();it<guity[i].end();it++)
			if (status[i]==2)
			{
				if (*it!=ngu) status[i]=0,nf++;
				else status[i]=1,nt++;
			}
			else 
			{
				if (*it!=ngu){if (status[i]!=0)return;}
				else if (status[i]!=1) return;
			}
		for(it=nguity[i].begin();it<nguity[i].end();it++)
			if (status[i]==2)
			{
				if (*it!=ngu)status[i]=1,nt++;
				else status[i]=0,nf++;
			}
			else
			{
				if (*it!=ngu){if (status[i]!=1)return;}
				else if (status[i]!=0)return;
			}
	}
	if (nf<=m&&m<=n-nt&&(ngu!=man||re==0))
	{
		re++;
		man=ngu;
		if (re>1)
		{
			printf("Cannot Determine\n");
			exit(0);
		}
	}
}

void solve()
{
	for(int i=0;i<n;i++)
		if (ag[i][i])
			return;
	for(int i=0;i<n;i++)
		for(int j=0;j<7;j++)
			check(i,j);
}

int main()
{
	freopen("logic.in","r",stdin);
	freopen("logic.out","w",stdout);
	init();
	//printf("Init finished\n");
	solve();
	if (re)printf("%s\n",name[man]);
	else printf("Impossible\n");
	return 0;
}	
