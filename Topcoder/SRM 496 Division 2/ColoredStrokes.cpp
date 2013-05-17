/*
ID: dxmtb
PROG: Topcoder SRM 496 Division 2
TIME: 2011.02.02
STATE: Solved
MEMO: 贪心
*/
#include <vector>
#include <string>
using namespace std;

const int MAXN=60;

class ColoredStrokes
{
	private:

	public:
		int getLeast(vector<string> picture)
		{
			int re=0;
			int W=picture.size(),H=picture[0].length();
			for(int i=0;i<W;i++)
				for(int j=0;j<H;j++)
					if (picture[i][j]=='G'||
					    picture[i][j]=='R')
					if (j==0||picture[i][j-1]=='.'||picture[i][j-1]=='B')
						re++;
						
			for(int i=0;i<H;i++)
				for(int j=0;j<W;j++)
					if (picture[j][i]=='G'||
					    picture[j][i]=='B')
					if (j==0||picture[j-1][i]=='.'||picture[j-1][i]=='R')
						re++;
			return re;
		}
};
