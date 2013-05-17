/*
ID: dxmtb
PROG: 翻译玛雅著作
TIME: 2010.9.28
STATE: Solved
MEMO: 枚举
*/
#include <cstdio>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;
const int MAXS=3000005;

int g,s;
int t[259],tt[259];

char str[MAXS];
int re;
int main()
{
	freopen("writing.in","r",stdin);
	freopen("writing.out","w",stdout);
	scanf("%d%d",&g,&s);
	for(int i=0;i<g;i++)
	{
		char ch;
		do
		{
			ch=getchar();
		}while(!((ch>='a'&&ch<='z')||(ch>='A'&&ch<='Z')));
		t[ch-'A']++;
	}
	scanf("\n");
	scanf("%s",str);
	memcpy(tt,t,sizeof(t));
	for(int i=0;i<s;i++)
	{
		int tmp=str[i]-'A';
		t[tmp]--;
		if (i-g>=0)
			t[str[i-g]-'A']++;
		if (t[tmp]<0)
			continue;
		bool flag=true;
		for(int i=0;i<26&&flag;i++)
			if (t[i]!=0)
				flag=false;
		if (!flag)
			continue;
		for(int i='a'-'A';i<='z'-'A'&&flag;i++)
			if (t[i]!=0)
				flag=false;
		if (!flag)
			continue;
		re++;
	}
	printf("%d\n",re);
	return 0;
}	
