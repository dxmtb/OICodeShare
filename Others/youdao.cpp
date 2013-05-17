/*
ID: dxmtb
PROG: 有道难题资格赛一 有道搜索框
TIME: 2010.5.30
STATE: Solved
MEMO: Trie
*/
#include <string>
#include <iostream>
#include <cstring>
using namespace std;

int n,m;

class Node
{
public:
	Node()
	{
		data='\0';
		is=false;
		memset(next,0,sizeof(next));
	}
	char data;
	bool is;
	Node* next[26];
};

class Trie
{
public:
	Trie()
	{
		timer=0;
	}
	void insert(string x)
	{
		timer++;
		Node *temp=&root;
		unsigned p=0;
		while (p<x.length())
		{
			if (temp->next[x[p]-'a']==NULL)
				temp->next[x[p]-'a']=new Node;
			temp=temp->next[x[p]-'a'];
			temp->data=x[p++];
			if (p==x.length())
				temp->is=true;
		}
	}
	bool se(string x,Node *temp,int &count)
	{
		bool flag=false;
		if (!temp)return false;
		string xx=x+temp->data;
		if (temp->is)
		{
			count++;
			if (count>1)cout<<' ';
			cout<<xx;
			flag=true;
			if (count==8)return true;			
		}
		for(int i=0;i<26;i++)
			if (temp->next[i]&&count<8&&se(xx,temp->next[i],count))
			flag=true;
		return flag;
	}
	bool search(string x)
	{
		Node *temp=&root;
		unsigned p=0;
		int count=0;	
		bool flag=false;		
		while (p<x.length())
		{
			if (temp->next[x[p]-'a']==NULL)
				return false;
			temp=temp->next[x[p]-'a'];p++;
			if (p==x.length())
			{
				if (temp->is)
				{
					cout<<x;
					count++;
					flag=true;
				}
				break;
			}
		}
		for(int i=0;i<26;i++)
			if (temp->next[i]&&count<8&&se(x,temp->next[i],count))			
			flag=true;
		return flag;
	}
private:
	Node root;
	int timer;
}T;

void init()
{
	cin>>n;
	for(int i=0;i<n;i++)
	{
		string str;
		cin>>str;
		T.insert(str);
	}
}

void solve()
{
	int Q;
	cin>>Q;
	for(int i=0;i<Q;i++)
	{
		string str;
		cin>>str;
		if (!T.search(str))
			cout<<str;
		cout<<'\n';
	}
}

int main() 
{
	freopen("youdao.in","r",stdin);
	freopen("youdao.out","w",stdout);
	init();
	solve();
	return 0;
}
