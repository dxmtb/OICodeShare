/*
ID: dxmtb
PROG: Topcoder SRM 496 Division 2
TIME: 2011.02.02
STATE: Solved
MEMO: 枚举+并查集
*/
#include <vector>
#include <string>
#include <cstring>
using namespace std;
const int MAXN=60;
class AnagramFree
{
	private:
		int father[MAXN],N;
		int getfather(int p)
		{
			if (father[p]==p)
				return p;
			return father[p]=getfather(father[p]);
		}
		void judge(int x,int y)
		{
			int fx=getfather(x),fy=getfather(y);
			father[fx]=fy;
		}
	public:
		int getMaximumSubset(vector<string> S)
		{
			N=S.size();
			for(int i=0;i<N;i++)
				father[i]=i;
			for(int i=0;i<N;i++)
				for(int j=i+1;j<N;j++)
				if (S[i].length()==S[j].length())
				{
					int used1[26],used2[26];
					memset(used1,0,sizeof(used1));
					memset(used2,0,sizeof(used2));
					for(int k=0;k<S[i].length();k++)
						used1[S[i][k]-'a']++;
					for(int k=0;k<S[j].length();k++)
						used2[S[j][k]-'a']++;
					int k;
					for(k=0;k<26;k++)
						if (used1[k]!=used2[k])
							break;
					if (k==26)
						judge(i,j);
				}
			bool used[MAXN];
			for(int i=0;i<N;i++)
				used[i]=false;
			for(int i=0;i<N;i++)
				used[getfather(i)]=true;
			int re=0;
			for(int i=0;i<N;i++)
				if (used[i])
					re++;
			return re;
		}
};
