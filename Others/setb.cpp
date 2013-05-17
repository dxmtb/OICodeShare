/*
ID: dxmtb
PROG: setb
TIME: 2010.11.2
STATE: Solved
MEMO: 筛法+并查集
*/
#include <cstdio>
#include <cmath>
using namespace std;

const int MAXN=100005,MAXM=MAXN;

int father[MAXN];
int A,B,P,re;

int getfather(int u)
{
	if (father[u]==u)
		return u;
	return father[u]=getfather(father[u]);
}

void judge(int a,int b)
{
	int fa=getfather(a),fb=getfather(b);
	father[fb]=fa;
}

void getprime()
{
	bool flag[MAXM+1];
	for(int i=2;i<=B;i++)
		flag[i]=true;
	for(int i=2;i<P;i++)
		if (flag[i])
		for(int j=i+i;j<=B;j+=i)
			flag[j]=false;
	for(int i=P;i<=B;i++)
		if (flag[i])
		for(int j=i+i;j<=B;j+=i)
		{
			flag[j]=false;
			judge(i,j);
		}
//	for(int i=0;i<top;i++)
//		printf("%d\n",prime[i]);
}

bool used[MAXN];
int main()
{
	freopen("setb.in","r",stdin);
	freopen("setb.out","w",stdout);
	scanf("%d%d%d",&A,&B,&P);
	for(int i=1;i<=B;i++)
		father[i]=i;
	getprime();
	for(int i=A;i<=B;i++)
	{
		int j=getfather(i);
	//	printf("%d %d\n",i,j);
		if (!used[j])
		{
			used[j]=true;
			re++;
		}
	}
	printf("%d\n",re);
	return 0;
}

		
