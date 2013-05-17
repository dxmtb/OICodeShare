/*
ID: dxmtb
PROG: 物品
TIME: 2010.11.17
STATE: Solved
MEMO: dp
*/
#include <cstdio>
#include <sstream>
#include <iostream>
using namespace std;
const int MAXN=1005,MAXM=5005;
const int oo=100000000;

struct Node
{
	int first,second;
}p[MAXN];

int top=1;
int N,P,money,sum,sum2;
int d[MAXN][MAXM];

int main()
{
	freopen("magica.in","r",stdin);
	freopen("magica.out","w",stdout);
	cin>>N>>P;
	for(int i=0;i<N;i++)
	{
		string str;
		int x,y;
		while(true)
		{
			getline(cin,str);
			stringstream in(str);
			if (in>>x) 
			{
				if (in>>y)
				{
					if (y-x<=P) money+=x;
					else
					{
						p[top].first=x;
						p[top].second=y-P;
						sum+=y-P;
						sum2+=x;
						top++;
					}
				}
				else money+=x;
				break;
			}
		}	
	}
	for(int i=money+1;i<=P;i++)
		d[0][i]=oo;
	for(int i=1;i<top;i++)
		for(int j=0;j<=P;j++)
			d[i][j]=min(d[i-1][j],
				d[i-1][j-p[i].first]+
					p[i].second-p[i].first);
	if (d[top-1][P]!=oo) cout<<sum+money-d[top-1][P]<<endl;
	else cout<<sum2+money<<endl;
	return 0;
}
