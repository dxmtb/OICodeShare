// BEGIN CUT HERE

// END CUT HERE
#line 5 "CubeWalking.cpp"
#include <string>
#include <vector>
using namespace std;

const int map[3][3]={{0,1,0},{1,2,1},{0,1,0}};
const int way[4][2]={{1,0},{0,1},{-1,0},{0,-1}};

class CubeWalking 
{
	public:
	string finalPosition(string movement) 
	{
		int x=1,y=1,to=0;
		int N=movement.length();
		for(int i=0;i<N;i++)
			if (movement[i]=='L')	
				i=(i-1+4)%4;
			else if (movement[i]=='R')
				i=(i+1)%4;
			else if (movement[i]=='W')
			{
				x=x+way[to][0],y=y+way[to][1];
				x=(x+4)%4;
				y=(y+4)%4;
			}
		if (map[x][y]==0)
			return "RED";
		if (map[x][y]==1)
			return "BLUE";
		if (map[x][y]==2)
			return "GREEN";
	}
};
