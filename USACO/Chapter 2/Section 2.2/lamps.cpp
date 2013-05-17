/*
ID: dxmtb1
PROG: lamps
LANG: C++
*/
#include <cstdio>
#include <bitset>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN=100,MAXC=10000;

int n,c;
bool need[MAXN+1],should[MAXN+1],way[4];
vector<string> v;
bitset<100> 
	begin,
	m1,
	m2(string("1010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010")),
	m3(string("0101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101")),
	m4(string("1001001001001001001001001001001001001001001001001001001001001001001001001001001001001001001001001001"));

	
FILE *fin=fopen("lamps.in","r");
FILE *fout=fopen("lamps.out","w");

void init()
{
	int temp;
	fscanf(fin,"%d%d%d",&n,&c,&temp);
	for(int i=0;i<=MAXN;i++)need[i]=false;
	while (temp!=-1)
	{
		need[temp]=true;
		should[temp]=1;
		fscanf(fin,"%d",&temp);
	}
	fscanf(fin,"%d",&temp);
	while (temp!=-1)
	{
		need[temp]=true;
		should[temp]=0;
		fscanf(fin,"%d",&temp);
	}
}

void search(int dep,int timer)
{
	if (timer>c||dep>4) return;
	if (dep==4&&((c-timer)%2==0))
	{
		bitset<100> temp=begin;
		if (way[0]) temp^=m1;
		if (way[1]) temp^=m2;
		if (way[2]) temp^=m3;
		if (way[3]) temp^=m4;
		for(int i=1;i<=n;i++)
			if (need[i]&&temp[100-i]!=should[i])
				return;
		string str=temp.to_string<char,char_traits<char>,allocator<char> >();
		str.erase(n,100-n);
		v.push_back(str);
		return;
	}
	way[dep]=true;
	search(dep+1,timer+1);
	way[dep]=false;
	search(dep+1,timer);
}

int main() 
{
	init();
	begin=~begin;
	m1=~m1;
	search(0,0);
	sort(v.begin(),v.end());
	if (v.size()==0u)
		fprintf(fout,"IMPOSSIBLE\n");
	else
	for(unsigned  i=0;i<v.size();i++)
		if ((i!=0&&v[i]!=v[i-1])||i==0)
		fprintf(fout,"%s\n",v[i].c_str());
	return 0;
}
