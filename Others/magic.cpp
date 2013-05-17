/*
ID: dxmtb
PROG: 魔术数字游戏
TIME: 2010.9.29
STATE: Solved
MEMO: 搜索
*/
#include <cstdio>
using namespace std;

int I,J;
int map[4][4];
bool used[17];
bool out=false;

inline bool check(int a,int b)
{
	if (b==0&&a!=0)
		if (map[a-1][0]+map[a-1][1]+map[a-1][2]+map[a-1][3]!=34)
			return false;
	if (a==3&&b!=0)
		if (map[0][b-1]+map[1][b-1]+map[2][b-1]+map[3][b-1]!=34)
			return false;
	if (a==1)
	{
		if (b==2)
			if (map[0][0]+map[0][1]+map[1][0]+map[1][1]!=34)
				return false;
	}
	else if (a==2)
	{
		if (b==1)
			if (map[0][2]+map[0][3]+map[1][2]+map[1][3]!=34)
				return false;
		if (b==3)
			if (map[1][1]+map[1][2]+map[2][1]+map[2][2]!=34)
				return false;
	}
	else if (a==3)
	{
		if (b==1)
			if (map[0][3]+map[1][2]+map[2][1]+map[3][0]!=34)
				return false;
		if (b==2)
			if (map[2][0]+map[2][1]+map[3][0]+map[3][1]!=34)
				return false;
	}
	if (a==4)
	{
		if (map[2][2]+map[2][3]+map[3][2]+map[3][3]!=34)
			return false;
		if (map[0][0]+map[1][1]+map[2][2]+map[3][3]!=34)
			return false;
		if (map[0][0]+map[0][3]+map[3][0]+map[3][3]!=34)
			return false;
		if (out)
			putchar('\n');
		else 
			out=true;
		for(int i=0;i<4;i++)
	 	{
	 		for(int j=0;j<4;j++)
				printf("%d ",map[i][j]);
			putchar('\n');
		}
		return false;
	}
	return true;
}

void search(int a,int b)
{
	if (a+1==I&&b+1==J)
	{
		if (b+1==4) search(a+1,0);
		else search(a,b+1);
	}
	else 
	for(int i=2;i<=16;i++)	
		if (!used[i])
		{
			map[a][b]=i;
			used[i]=true;
			if (b+1==4) {if (check(a+1,0)) search(a+1,0);}
			else {if (check(a,b+1)) search(a,b+1);}
			used[i]=false;
		}
}

int main()
{
	freopen("magic.in","r",stdin);
	freopen("magic.out","w",stdout);
	scanf("%d%d",&I,&J);
	map[I-1][J-1]=1;
	used[1]=true;
	search(0,0);
	return 0;
}



