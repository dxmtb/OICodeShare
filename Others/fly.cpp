/*
ID: dxmtb
PROG: 飞行棋
TIME: 2011.03.09
STATE: Solved
MEMO: 枚举
*/
#include <cstdio>

const int MAXN=25;

int A[MAXN];
int N,sum,re;
int main()
{
	freopen("fly.in","r",stdin);
	freopen("fly.out","w",stdout);
	scanf("%d",&N);
	for(int i=0;i<N;i++)
	{
		scanf("%d",A+i);
		sum+=A[i];
	}
	for(int i=0;i<N;i++)
	{
		int s1=A[i];
		for(int j=i+1;j<N;j++)
		{
			int s2=A[j];
			for(int a=j+1;a<N;a++)
			{
				int s3=A[a];
				for(int b=a+1;b<N;b++)
				{
					int s4=sum-s1-s2-s3;
					if (s1==s3 && s2==s4)
						re++;
					s3+=A[b];
				}
				s2+=A[a];
			}
			s1+=A[j];
		}
	}
	printf("%d\n",re);
	return 0;
}
