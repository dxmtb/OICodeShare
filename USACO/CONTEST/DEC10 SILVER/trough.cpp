/*
PROG: trough
LANG: C++
ID: dxmtb1
*/
#include <cstdio>
#include <vector>
using namespace std;

int N,M;
vector<pair<int,int> > v;
int rS,re;

int main()
{
	freopen("trough.in","r",stdin);
	freopen("trough.out","w",stdout);
	scanf("%d%d",&N,&M);
	for(int i=0;i<M;i++)
	{
		int b,c,j;
		char a[100];
		scanf("%s%d",a,&b);
		for(c=0,j=0;j<N;j++)
		{
			c<<=1;
			c+=a[j]-'0';
		}
		v.push_back(make_pair(c,b));
	}
	int MAXS=(1<<N);
	for(int S=0;S<MAXS;S++)
	{
		bool flag=true;
		for(int i=0;i<M;i++)
		{
			int nS=S&v[i].first;
			int t=0,maxt=v[i].second;
			while(nS&&t<=maxt)
			{
				t++;
				nS-=((nS)&(-nS));
			}
			if (t!=maxt)
			{
				flag=false;
				break;
			}
		}
		if (flag)
		{
			if (re)
			{
				printf("NOT UNIQUE\n");
				return 0;
			}
			else
			{
				re++;
				rS=S;
			}
		}
	}
	if (re)
	{
		char str[100];
		int top=0;
		while(rS)
		{
			str[top++]='0'+(rS&1);
			rS>>=1;
		}
		for(int i=N-1;i>=top;i--)
			printf("0");
		for(int i=top-1;i>=0;i--)
			printf("%c",str[i]);
		printf("\n");
	}
	else printf("IMPOSSIBLE\n");
	return 0;
}

