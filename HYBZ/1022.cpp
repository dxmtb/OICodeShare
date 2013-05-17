/*
 * Problem: 1022: [SHOI2008]小约翰的游戏John 
 * Time: 2011.07.19
 * Author: dxmtb
 * State: Solved
 * Memo: Anti-SG
*/
#include <cstdio>

int main()
{
	int T;
	scanf("%d",&T);
	while(T--)
	{
		int N;
		scanf("%d",&N);
		bool flag=false;
		int val=0;
		for(int i=0;i<N;i++)
		{
			int x;
			scanf("%d",&x);
			if (x>1)
				flag=true;
			val^=x;
		}
		if ((val==0 && flag==false) || (val!=0 && flag==true))
			printf("John\n");
		else
			printf("Brother\n");
	}
	return 0;
}
