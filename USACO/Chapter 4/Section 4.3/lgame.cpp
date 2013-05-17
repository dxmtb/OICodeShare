/*
ID: dxmtb1
PROG: lgame
LANG: C++
*/
#include <cstdio>
#include <string>
#include <string.h>
#include <vector>
#include <algorithm>
using namespace std;

const int W[26]={2,5,4,4,1,6,5,5,1,7,6,3,5,2,3,5,7,2,1,2,4,6,6,7,5,7};

FILE *fin=fopen("lgame.in","r");
FILE *fdict=fopen("lgame.dict","r");
FILE *fout=fopen("lgame.out","w");

char str[10];
vector<string> ans,v;
int can[30],need[30];
int re;

int main()
{
	fscanf(fin,"%s",str);
	for(int i=0;i<strlen(str);i++)
		can[str[i]-'a']++;
	while(true)
	{
		fscanf(fdict,"%s",str);
		if (strcmp(str,".")==0)
			break;
		int i,total=0;
		memset(need,0,sizeof(need));
		for(i=0;i<strlen(str);i++)
		{
			need[str[i]-'a']++;
			total+=W[str[i]-'a'];
			if (need[str[i]-'a']>can[str[i]-'a'])
				break;
		}
		if (i==strlen(str))
		{
			v.push_back(string(str));
			if (total>re)
			{
				re=total;
				ans.clear();
				ans.push_back(string(str));
			}
			else if (total==re)
				ans.push_back(string(str));
		}
	}
	for(int i=0;i<v.size();i++)
		for(int j=i+1;j<v.size();j++)
		{
			memset(need,0,sizeof(need));
			int k,total=0;
			for(k=0;k<v[i].length();k++)
			{
				need[v[i][k]-'a']++;
				total+=W[v[i][k]-'a'];
				if (need[v[i][k]-'a']>can[v[i][k]-'a'])
					break;
			}
			if (k==v[i].length())
			{
				for(k=0;k<v[j].length();k++)
				{
					need[v[j][k]-'a']++;
					total+=W[v[j][k]-'a'];
					if (need[v[j][k]-'a']>can[v[j][k]-'a'])
						break;
				}
				if (k==v[j].length())
				if (total>re)
				{
					ans.clear();
					ans.push_back(v[i]+' '+v[j]);
					re=total;	
				}
				else if (total==re)
					ans.push_back(v[i]+' '+v[j]);
			}
		}
	sort(ans.begin(),ans.end());
	fprintf(fout,"%d\n",re);
	for(int i=0;i<ans.size();i++)
		fprintf(fout,"%s\n",ans[i].c_str());
	return 0;
}
