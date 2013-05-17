/*
 * Problem: poj2406 Power Strings
 * Time: 2011.04.08
 * Author: dxmtb
 * State: Solved
 * Memo: KMP
*/
#include <cstdio>
#include <cstring>
using namespace std;

const int MAXN=1000005;

char str[MAXN];
int N,next[MAXN];

int main()
{
	freopen("poj2406.in","r",stdin);
	while(true)
	{
		scanf(" %s",str);
		N=strlen(str);
		if (str[0]=='.' && N==1)
			break;
		next[0]=-1;
		for(int i=1,j=-1;i<N;i++)
		{
			while(j>=0 && str[i]!=str[j+1])
				j=next[j];
			if (str[i]==str[j+1])
				j++;
			next[i]=j;
		}
		if ((next[N-1]+1)*2<N)
			printf("1\n");
		else
		{
			int len=N-next[N-1]-1;
			if (N%len==0)
				printf("%d\n",N/len);
			else 
				printf("1\n");
		}
	}
	return 0;
}
