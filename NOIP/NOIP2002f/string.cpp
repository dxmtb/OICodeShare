/*
ID: dxmtb
PROG: NOIP2002 ×Ö´®±ä»»
TIME: 2010.5.3
STATE: Solved
MEMO: Ë«ÏòËÑËØ
*/
#include <cstdio>
#include <string>
#include <set>
#include <queue>
#include <iostream>
#include <cstdlib>
using namespace std;

const int MAXN=20;

struct Node
{
	string data;
	int dep;
	Node(string x,int d){data=x;dep=d;}
};

int n=0,d[2];
string A,B;
string r[2][6];
set<string> s[2];
queue<Node> q[2];

void init()
{
	cin>>A>>B;
	scanf("\n");
	char buf[100],temp1[100],temp2[100];
	memset(buf,0,sizeof(buf));
	while (gets(buf)!=NULL)
	{
		memset(temp1,0,sizeof(temp1));
		memset(temp2,0,sizeof(temp2));
		sscanf(buf,"%s%s",temp1,temp2);
		r[0][n]=temp1,r[1][n]=temp2;
		++n;
	}
	if (A==B)
	{
		printf("0\n");
		exit(0);
	}
	q[0].push(Node(A,0));
	q[1].push(Node(B,0));
	s[0].insert(A);
	s[1].insert(B);
}

void op(int di)
{
	int opp=1-di;
	while (q[di].front().dep==d[di])
	{
		Node now=q[di].front();
		q[di].pop();
		string str=now.data;
		for(int i=0;i<n;i++)
		{
			size_t j=str.find(r[di][i]);
			while(j!=string::npos)
			{
				string newone=str;
				newone.erase(j,r[di][i].length());
				newone.insert(j,r[opp][i]);
				if (s[opp].find(newone)!=s[opp].end())
				{
					printf("%d\n",d[0]+d[1]+1);
					exit(0);
				}
				if (s[di].find(newone)==s[di].end())
				{
					s[di].insert(newone);
					q[di].push(Node(newone,d[di]+1));
				}
				j=str.find(r[di][i],j+1);
			}
		}
	}
	d[di]++;
}

void search()
{
	while (d[0]+d[1]<=10)
	if (d[0]>d[1])
		op(1);
	else
		op(0);
	printf("NO ANSWER!\n");
}

int main() 
{
	freopen("string.in","r",stdin);
	freopen("string.out","w",stdout);
	init();
	search();
	return 0;
}
