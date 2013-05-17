/*
ID: dxmtb
PROG: [SCOI2009]生日快乐 
TIME: 2011.03.23
STATE: Solved
MEMO: 搜索
*/
#include <cstdio>
#include <algorithm>
using namespace std;

double dfs(double X,double Y,int N)
{
	if (X>Y) swap(X,Y);
	if (N==1) return Y/X;
	double re=1e18;
	for(int i=1;i<N;i++)
		re=min(re,min(
		    max(dfs(X/N*i,Y,i),dfs(X/N*(N-i),Y,N-i)),
		    max(dfs(X,Y/N*i,i),dfs(X,Y/N*(N-i),N-i))));
	return re;
}

int main()
{
	int X,Y,N;
	scanf("%d%d%d",&X,&Y,&N);
	printf("%lf\n",dfs(X,Y,N));
	return 0;
}
