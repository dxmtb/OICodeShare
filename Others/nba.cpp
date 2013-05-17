/*
ID: dxmtb
PROG: NBA总冠军
TIME: 2010.10.26
STATE: Solved
MEMO: 排序
*/
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;

struct Node
{
	string str;
	int year;
	Node(const string &a,int b=0):str(a),year(b){}
};

bool operator < (const Node &a,const Node &b)
{
	return a.year<b.year;
}

vector<Node> v;
int n;

int main()
{
	freopen("nba.in","r",stdin);
	freopen("nba.out","w",stdout);
	cin>>n;
	for(int i=0;i<n;i++)
	{
		scanf("\n");
		string str;
		char year[1000];
		int data;
		getline(cin,str);
		int len=str.length();
		if (str[len-1]=='\n'||str[len-1]=='\r')
			--len;
		int j;
		for(j=len-4;str[j]==' ';j--);
		int len2=str.copy(year,len-j,j);
		year[len2]='\0';
		sscanf(year,"%d",&data);
		str.erase(j-1);
		v.push_back(Node(str,data));
	}
	sort(v.begin(),v.end());
	for(int i=0;i<n;i++)
		if (i==0||v[i].year!=v[i-1].year)
		cout<<v[i].year<<' '<<v[i].str<<endl;
	return 0;
}
