/*
ID: dxmtb1
PROG: prefix
LANG: C++
*/
#include <cstdio>
#include <string>
#include <cstring>
#include <iostream>
using namespace std;

const int MAXN=200000;

class Node
{
public:
	Node()
	{
		data='\0';
		is=false;
		memset(next,NULL,sizeof(next));
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
		unsigned p=0,t=x.length()-1;
		while (p<x.length())
		{
			if (temp->next[x[t-p]-'A']==NULL)
				temp->next[x[t-p]-'A']=new Node;
			temp=temp->next[x[t-p]-'A'];
			temp->data=x[t-p++];
			if (p==x.length())
				temp->is=true;
		}
	}
	int search(string x)
	{
		Node *temp=&root;
		unsigned p=0,t=x.length()-1;
		while (p<x.length())
		{
			if (temp->next[x[t-p]-'A']==NULL)
				return 0;
			temp=temp->next[x[t-p]-'A'];p++;
			if (p==x.length())
				if(temp->is==true)
					return 1;
				else return 2;
		}
	}
private:
	Node root;
	int timer;
};

FILE *fin=fopen("prefix.in","r");
FILE *fout=fopen("prefix.out","w");

bool d[MAXN];
int re=0;
string str;
Trie t;

void init()
{
	char temp='\0';
	string tstr("");
	fscanf(fin,"%c",&temp);
	while (temp!='.')
	{
		if (temp==' '||temp=='\n')
		{
			if (tstr.length()>0) 
				t.insert(tstr);
			tstr="";
			fscanf(fin,"%c",&temp);
			continue;
		}
		if (!(temp>='A'&&temp<='Z')){fscanf(fin,"%c",&temp);continue;}
		tstr+=temp;
		fscanf(fin,"%c",&temp);
	}
	if (tstr.length()>0) t.insert(tstr);
	tstr="";
	while (!feof(fin))
	{
		fscanf(fin,"%c",&temp);
		if (!(temp>='A'&&temp<='Z'))continue;
		tstr+=temp;
	}
	str=tstr;
}

int main()
{
	init();
	memset(d,0,sizeof(d));
	string tstr="";
	tstr+=str[0];
	if (t.search(tstr))
		d[0]=1,re=1;
	for(unsigned i=1;i<str.length();i++)
	{
		bool flag=false;
		for(int j=i-1;j>=-1&&!flag;j--)
			if (j==-1||d[j]>0)
			{
				tstr="";
				for(unsigned k=j+1;k<=i;k++)
					tstr+=str[k];
				int tint=t.search(tstr);
				if (tint==0)break;
				if (tint==1)d[i]=1,flag=true;
			}
		if (flag) re=i+1;
	}
	fprintf(fout,"%d\n",re);
	return 0;
}
