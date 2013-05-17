/*
ID: dxmtb1
PROG: cryptcow
LANG: C++
*/
#include <cstdio>
#include <string>
#include <algorithm>
#include <iostream>
#include <cstring>
using namespace std;

const int MAXN=80,MO=134101;
const string final="Begin the Escape execution at the Break of Dawn";
const char *ch1="C",*ch2="O",*ch3="W";
const int LEN=final.length();

string begin;

bool hash[MO];
int timer;

int stringhash(string str)
{
	unsigned long h=0,len=str.length();
	for(int i=0;i<len;i++)
	{
		h=(h<<4)+str[i];
		unsigned long g=h&0xf0000000L;
		if (g) h^=g>>24;
		h&=~g;
	}
	return h%MO;
}

inline bool used(string now)
{
	int temp=stringhash(now);
	if (hash[temp])return true;
	else hash[temp]=true;
	timer++;
	return false;
}

inline bool cut(string now)
{
	int len=now.length();
	for(int i=0;i<len;i++)
		if (now[i]=='C'||now[i]=='O'||now[i]=='W')
			if (now[i]!='C')return true;
			else break;
	for(int i=len-1;i>=0;i--)
		if (now[i]=='C'||now[i]=='O'||now[i]=='W')
			if (now[i]!='W')return true;
			else break;
	int temp[30]={1,-1};
	for(int i=0;i<len;i++)
		if (now[i]=='C'||now[i]=='O'||now[i]=='W')
		{
			temp[++temp[0]]=i;
			int j=temp[temp[0]-1];
			if (final.find(now.substr(j+1,i-j-1))==final.npos)
				return true;
		}
	if (final.find(now.substr(temp[temp[0]]+1))==final.npos)
				return true;
	return false;
}

string trans(string now,int p1,int p2,int p3)
{
	char re[80];
	for(int i=0;i<80;i++)re[i]=0;	
	int i,j;
	for(i=0,j=0;i<p1;i++)
		re[j++]=now[i];
	for(i=p2+1;i<p3;i++)
		re[j++]=now[i];
	for(i=p1+1;i<p2;i++)
		re[j++]=now[i];
	for(i=p3+1;i<now.length();i++)
		re[j++]=now[i];
	return string(re);
}

bool dfs(string now)
{
	if (now==final)return true;
	if (used(now)) return false;
	if (cut(now)) return false;
	for(int i=0;i<now.length();i++)
	if (now[i]=='O')
		for(int j=0;j<i;j++)
		if (now[j]=='C')
			for(int k=now.length()-1;k>i;k--)
				if (now[k]=='W')
				if (dfs(trans(now,j,i,k)))
					return true;
	return false;
}

int main()
{
	freopen("cryptcow.in","r",stdin);
	freopen("cryptcow.out","w",stdout);
	getline(cin,begin);
	if ((begin.length()-LEN)%3==0&&count(begin.begin(),begin.end(),'C')==count(begin.begin(),begin.end(),'O')&&
			count(begin.begin(),begin.end(),'O')==count(begin.begin(),begin.end(),'W')
			&&dfs(begin)) printf("1 %d\n",count(begin.begin(),begin.end(),'C'));
	else printf("0 0\n");
//	printf("%d\n",timer);
	return 0;
}
