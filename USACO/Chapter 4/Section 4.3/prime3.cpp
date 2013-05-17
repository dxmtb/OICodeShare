/*
ID: dxmtb
PROG: prime3
LANG: C++
*/
#include <cstdio>
#include <algorithm>
#include <vector>
#include <sstream>
#include <iostream>
using namespace std;

const int MAXN=100000;

int S,ru;
bool flag[MAXN];
bool f[10][10][10][10][10];

void init()
{
	for(int i=2;i<MAXN;i++)
		flag[i]=true;
	for(int i=2;i<=MAXN;i++)
	{
		if (flag[i])
		{
			if (i>10000&&i/10000+i/1000%10+i/100%10+i/10%10+i%10==S)
				f[i/10000][i/1000%10][i/100%10][i/10%10][i%10]=true;
		}
		for(int j=i;j<MAXN;j+=i)
			flag[j]=false;
	}
}

bool out=false;
vector<string> re;
int main()
{
	freopen("prime3.in","r",stdin);
	freopen("prime3.out","w",stdout);
	scanf("%d%d",&S,&ru);
	init();
	for(int a1=ru;a1<=ru;a1++)
	for(int b2=0;b2<=9;b2++)
	for(int c3=0;c3<=9;c3++)
	for(int d4=0;d4<=9;d4++)
	{
		int e5=S-a1-b2-c3-d4;
		if (e5<=0)
			continue;
		if (e5>9||!f[a1][b2][c3][d4][e5])
			continue;
		for(int a5=1;a5<=9;a5++)
		for(int b4=0;b4<=9;b4++)
		for(int d2=0;d2<=9;d2++)
		{
			int e1=S-a5-b4-c3-d2;
			if (e1<=0||e1>9)
				continue;
			if (!f[a5][b4][c3][d2][e1])
				continue;				
			for(int c1=1;c1<=9;c1++)
			for(int c2=0;c2<=9;c2++)
			for(int c4=0;c4<=9;c4++)
			{
				int c5=S-c1-c2-c3-c4;
				if (c5<=0||c5>9)
					continue;
				if (!f[c1][c2][c3][c4][c5])
					continue;
				for(int b1=1;b1<=9;b1++)
				{
					int d1=S-a1-b1-c1-e1;
					if (d1<=0)
						continue;
					if (d1>9||!f[a1][b1][c1][d1][e1])
						continue;
					for(int b5=1;b5<=9;b5++)
					{
						int d5=S-a5-b5-c5-e5;
						if (d5<=0||d5>9)
							continue;
						if (!f[a5][b5][c5][d5][e5])
							continue;
						int b3=S-b1-b2-b4-b5;
						if (b3<0||b3>9) 
							continue;
						if (!f[b1][b2][b3][b4][b5])
							continue;	
						int d3=S-d1-d2-d4-d5;
						if (d3<0||d3>9) 
							continue;
						if (!f[d1][d2][d3][d4][d5])
							continue;	
						for(int a2=1;a2<=9;a2++)
						{
							int e2=S-a2-b2-c2-d2;
							if (e2<=0)
								continue;
							if (e2>9||!f[a2][b2][c2][d2][e2])
								continue;
							for(int a3=1;a3<=9;a3++)
							{
								int e3=S-a3-b3-c3-d3;
								if (e3<=0)
									continue;
								if (e3>9||!f[a3][b3][c3][d3][e3])
									continue;
								int a4=S-a1-a2-a3-a5;
								if (a4<=0||a4>9)
									continue;
								if (!f[a1][a2][a3][a4][a5])
									continue;
								int e4=S-a4-b4-c4-d4;
								if (e4<=0)
									continue;
								if (e4>9||!f[a4][b4][c4][d4][e4])
									continue;
								if (!f[e1][e2][e3][e4][e5])
									continue;
								stringstream nre;
								nre<<a1<<b1<<c1<<d1<<e1<<endl;
								nre<<a2<<b2<<c2<<d2<<e2<<endl;
								nre<<a3<<b3<<c3<<d3<<e3<<endl;
								nre<<a4<<b4<<c4<<d4<<e4<<endl;
								nre<<a5<<b5<<c5<<d5<<e5<<endl;
								re.push_back(nre.str());
							}		
						}		
					}
				}	
			}
		}
	}
	if (re.size())
	{
		sort(re.begin(),re.end());
		printf("%s",re[0].c_str());
		for(int i=1;i<re.size();i++)
			printf("\n%s",re[i].c_str());
	}
	else printf("NONE\n");
	return 0;
}
