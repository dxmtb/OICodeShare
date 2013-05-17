/*
ID: dxmtb
PROG: NOIP2008 ±¿Ð¡ºï
TIME: 2010.7.22
STATE: Solved
MEMO: Ä£Äâ
*/
#include <cstdio>
#include <cmath>
#include <cstring>
using namespace std;

const int MAXN=105;

char str[MAXN];
int co[26];

int main()
{
	freopen("word.in","r",stdin);
	freopen("word.out","w",stdout);
	scanf("%s",str);
	for(unsigned i=0;i<strlen(str);i++)
		co[str[i]-'a']++;
	int min=0x7fffffff,max=0;
	for(int i=0;i<26;i++)
	{
		if (co[i]>max)
			max=co[i];
		if (co[i]&&co[i]<min)
			min=co[i];
	}
	int re=max-min;
	bool flag=true;
	if (re<=1)
		flag=false;
	for(unsigned i=2;i<=sqrt(double(re));i++)
		if (re%i==0)
		{
			flag=false;
			break;
		}
	if (flag)
		printf("Lucky Word\n%d\n",re);
	else printf("No Answer\n0\n");
	return 0;
}
