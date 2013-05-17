/*
ID: dxmtb1
PROG: shuttle
LANG: C++
*/
#include <cstdio>
using namespace std;

const int MAXN=15;

char sta[MAXN*2+1];
int nb,N;
int fW,fB;
int M;

inline void swap(int to,int &now)
{
	if (sta[to]=='W')
	{
		if (to==fW)
			fW=now;
	}
	else 
		if (to==fB)
			fB=now;
	sta[now]=sta[to];
	sta[now=to]=' ';
//	printf("%s\n",sta);
}

int main()
{
	freopen("shuttle.in","r",stdin);
	freopen("shuttle.out","w",stdout);
	scanf("%d",&N);
	nb=N;
	sta[nb]=' ';
	for(int i=0;i<nb;i++)
		sta[i]='W';
	for(int i=nb+1;i<N*2+1;i++)
		sta[i]='B';
//	printf("%s\n",sta);
	M=N*2;
	fW=0,fB=M;
	int out=0;
	while(nb!=N||sta[nb-1]!='B'||sta[nb+1]!='W')
	{
		if (nb>=1&&sta[nb-1]=='W'&&(nb>fB||((sta[nb+1]=='B')&&(nb<2||sta[nb-2]=='W'))))
		{
			swap(nb-1,nb);
		}
		else if (nb>=2&&sta[nb-2]=='W'&&(nb>fB||sta[nb-1]!='W'))
		{
			swap(nb-2,nb);
		}
		else if (nb<M&&sta[nb+1]=='B'&&(nb<fW||(sta[nb-1]!='B')))
		{
			swap(nb+1,nb);
		}
		else if (nb+2<=M&&sta[nb+2]=='B'&&(nb-2<fW||((nb<1||sta[nb-1]!='B')&&(nb==M||sta[nb+1]!='B'))))
		{
			swap(nb+2,nb);
		}
		else 
			return 1;
		if (out%20) printf(" ");
		else if (out) printf("\n");
		out++;
		printf("%d",nb+1);
	}
	printf("\n");
	return 0;
}
