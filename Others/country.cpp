/*
ID: dxmtb
PROG: 寻找国都名
TIME: 2010.9.6
STATE: Solved
MEMO: 搜索
*/
#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
using namespace std;

const int MAXN=105,MAXK=25;
const int me[8][2]={{0,1},{0,-1},{1,0},{-1,0},{1,-1},{-1,1},{1,1},{-1,-1}};

int n,m,K;
int way[MAXN];
string map[MAXN];
string city[MAXK];
bool vis[MAXN][MAXN];

bool find(string *str,int now,int x,int y)
{
	if (now==str->length())
		return true;
	bool flag=false;
	for(int i=0;i<8&&!flag;i++)
	{
		int nx=x+me[i][0],ny=y+me[i][1];
		if (nx>=0&&nx<n&&
				ny>=0&&ny<m&&
				map[nx][ny]==(*str)[now]&&!vis[nx][ny])
		{
			vis[nx][ny]=true;
			way[now]=i;
			if (find(str,now+1,nx,ny))
				flag=true;
			vis[nx][ny]=false;
		}
	}
	return flag;
}

int main()
{
	freopen("country.in","r",stdin);
	freopen("country.out","w",stdout);
	cin>>n>>m;
	for(int i=0;i<n;i++)
		cin>>map[i];
	cin>>K;
	for(int i=0;i<K;i++)
	{
		cin>>city[i];
//		cout<<city[i]<<endl;
		bool flag=true;
		for(int x=0;x<n&&flag;x++)
			for(int y=0;y<m&&flag;y++)
				if (map[x][y]==city[i][0])
				{
					memset(way,0,sizeof(way));
					vis[x][y]=true;
					if (find(&city[i],1,x,y))
					{
						flag=false;
						printf("(%d,%d)",x+1,y+1);
						int len=city[i].length();
						for(int i=1;i<len;i++)
							printf("%d",way[i]+1);
						printf("\n");
					}
					vis[x][y]=false;
				}
		if (flag)printf("No found\n");
	}
	return 0;
}
