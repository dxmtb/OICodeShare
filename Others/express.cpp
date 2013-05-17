/*
ID: dxmtb
PROG: 魔术数字游戏
TIME: 2010.9.29
STATE: Solved
MEMO: 表达式处理
*/
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <string>
#include <stack>
#include <list>
using namespace std;
const char ope[7]={'+','-','*','/','^','(',')'};
const int youx[]={1,1,2,2,3,0,0};

struct Node
{
	int tre;
	bool ty;
	Node(int a,bool b):tre(a),ty(b){}
};

string str;
string re;
stack<int> s1,s2;//s1 num s2 operator
int len;
bool first;
list<Node> tre;

void deal()
{
	int t1=s1.top();s1.pop();
	int t2=s1.top();s1.pop();
	int opt=s2.top();s2.pop();
	if (first){cerr<<"wrong\n";exit(-1);}
	re+=' ';
	re+=ope[opt];
	tre.push_back(Node(opt,true));
	switch (opt)
	{
		case 0:s1.push(t1+t2);break;
		case 1:s1.push(t2-t1);break;
		case 2:s1.push(t1*t2);break;
		case 3:s1.push(t2/t1);break;
		case 4:s1.push(pow(double(t2),t1));break;
		default : {cerr<<"wrong\n";exit(-1);}
	}
}

list<Node>::iterator it,it2;
void outbelong()
{
	it=tre.begin();
	if(it->ty){cerr<<"wrong\n";exit(200);}
	cout<<it->tre;
	for(it++;it!=tre.end();it++)
		if (it->ty)cout<<' '<<ope[it->tre];
		else cout<<' '<<it->tre;
	cout<<'\n';
}

void out()
{
	cout<<re<<endl;
//	outbelong();
	while(tre.size()!=1)
	{
		for(it=tre.begin();it!=tre.end();it++)
			if (it->ty)
			{
				int opt=it->tre;
				it2=it;
				it2--;
				tre.erase(it);
				int t2=it2->tre;
				it=it2;
				it--;
				tre.erase(it2);
				int t1=it->tre;
				switch (opt)
				{
					case 0:it->tre=t1+t2;break;
					case 1:it->tre=t1-t2;break;
					case 2:it->tre=t1*t2;break;
					case 3:it->tre=t1/t2;break;
					case 4:it->tre=pow(double(t1),t2);break;
					default:cerr<<"wrong\n";exit(-1);
				}
				break;
			}
		outbelong();
	}
}

void solve()
{
	len=str.length();
	str.erase(len-1);
	len-=1;
	first=true;
	for(int i=0;i<len;i++)
		if (str[i]==13)
			exit(i);
	for(int i=0;i<len;i++)
	{
		if (str[i]=='(')
		{
			s2.push(5);
			continue;
		}
		else if (str[i]==')')
		{
			while(s2.top()!=5)deal();
			s2.pop();
			continue;
		}
		if (str[i]>='0'&&str[i]<='9')
		{
			if (!first)re+=' ';
			else first=false;
			re+=str[i];
			tre.push_back(Node(str[i]-'0',false));
			s1.push(str[i]-'0');
		}
		else
		{
			char opc=str[i];
			int op=-100000;
			switch (opc)
			{
				case '+':op=0;break;
				case '-':op=1;break;
				case '*':op=2;break;
				case '/':op=3;break;
				case '^':op=4;break;
				default : cerr<<"wrong\n";exit(opc);
			}
			while (!s2.empty()&&youx[op]<=youx[s2.top()])
				deal();
			s2.push(op);
		}
	}
	while(!s2.empty())deal();
		s2.pop();
}

int main()
{
	freopen("express.in","r",stdin);
	freopen("express.out","w",stdout);
	getline(cin,str);
	solve();
	out();
	return 0;
}

