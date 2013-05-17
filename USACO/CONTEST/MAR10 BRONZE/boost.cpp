/*
PROG: boost
LANG: C++
ID: dxmtb1
*/

#include <fstream>

using namespace std;

const int MAXN=20;

ifstream fin ("boost.in");
ofstream fout ("boost.out");

void search(int dep,int f,int m);

int f,m,n;
int m_i[MAXN],f_i[MAXN],way[MAXN+1];
double maxa;
bool is[MAXN];

int main()
{
	fin>>f>>m>>n;
	for(int i=0;i<n;i++)
	{
		fin>>f_i[i];
		fin>>m_i[i];
	}
	for(int i=0;i<=MAXN;i++)is[i]=false;
	maxa=(double)f/m;
	search(0,f,m);
	if (way[0]!=0)
		for(int i=1;i<=way[0];i++)
			fout<<way[i]+1<<endl;
	else fout<<"NONE"<<endl;
	return 0;
}

void search(int dep,int f,int m)
{
	if (dep==n)
	{
		if (double(f)/m>maxa)
		{
			maxa=(double)f/m;
			way[0]=0;
			for(int i=0;i<n;i++)
				if (is[i]) way[++way[0]]=i;
		}
		return;
	}
	search(dep+1,f,m);
	is[dep]=true;
	search(dep+1,f+f_i[dep],m+m_i[dep]);
	is[dep]=false;
}
