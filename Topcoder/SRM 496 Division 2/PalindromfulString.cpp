/*
ID: dxmtb
PROG: Topcoder SRM 496 Division 2
TIME: 2011.02.02
STATE: Solved
MEMO: 最小表示+排列组合
*/
#include <vector>
#include <iostream>
using namespace std;

const int MAXN=13;

class PalindromfulString
{
	private:
		int way[MAXN];
		long long re,JC[MAXN],C[MAXN];
		int N,M,K,mid;
		bool check()
		{
			int tmp=0;
			for(int i=0;i<N-M+1;i++)
			{
				int j;
				for(j=0;j<mid;j++)
					if (way[i+j]!=way[i+M-j-1])
						break;
				if (j==mid)
					tmp++;
				if (tmp>=K)
					return true;
			}
			return false;
		}
		void search(int dep,int now)
		{
			if (dep==N)
			{
				if (check())
					re+=C[now];
				return ;
			}
			for(int i=1;i<=now&&i<=26;i++)
			{
				way[dep]=i;
				search(dep+1,now);
			}
			way[dep]=now+1;
			search(dep+1,now+1);
		}
	public:
		long long count(int NN,int MM,int KK)
		{
			N=NN;M=MM;K=KK;
			mid=M/2;
			re=0;
			JC[1]=1;
			for(int i=2;i<=N;i++)
				JC[i]=JC[i-1]*i;
			C[1]=26;
			for(int i=2;i<=N;i++)
				C[i]=C[i-1]*(27-i);
			way[0]=1;
			search(1,1);
			return re;
		}
};
