/*
ID: dxmtb
PROG: 漂亮字串
TIME: 2010.11.2
STATE: Solved
MEMO: 数学方法
*/
#include <iostream>
#include <cstdio>
using namespace std;

typedef long long LL;

int main()
{
	freopen("bs.in","r",stdin);
	freopen("bs.out","w",stdout);
	LL maxo,maxx;
	LL counto,countx;
	while(cin>>counto>>countx>>maxo>>maxx)
	{
		if (counto>countx)
		{
			swap(counto,countx);
			swap(maxo,maxx);
		}
		//special
		if (maxo==0&&maxx==0)
		{
			cout<<0<<endl;
			continue;
		}
		if (maxo==0||maxx==0)
		{	
			cout<<min(maxo,counto)+min(maxx,countx)<<endl;
			continue;
		}
		if (counto==0&&countx==0)
		{
			cout<<0<<endl;
			continue;
		}
		if (counto==0||countx==0)
		{
			cout<<min(counto,maxo)+min(maxx,countx)<<endl;
			continue;
		}
		//usual
		if (counto==countx)
		{
			cout<<counto+countx<<endl;
			continue;
		}
		LL groupo=counto,groupx=groupo+1;
		LL eacho=counto/groupo,eachx=countx/groupx;
		LL lefto=counto-eacho*groupo,leftx=countx-eachx*groupx;
		LL cano=(maxo-eacho)*groupo,canx=(maxx-eachx)*groupx;
		LL re=eacho*groupo+eachx*groupx+
			min(cano,lefto)+min(canx,leftx);
		cout<<re<<endl;
	}
	return 0;
}
