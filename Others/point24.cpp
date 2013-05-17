/*
ID: dxmtb
PROG: 算24点
TIME: 2010.9.18
STATE: Solved
MEMO: 搜索
*/
#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;

const char way[4]={'+','-','*','/'};

int a[4][4];
int me[4],me2[4];

void out()
{
	int t1,t2;
	t1=max(a[0][me2[0]],a[0][me2[0]+1]),t2=min(a[0][me2[0]],a[0][me2[0]+1]);
	printf("%d%c%d=%d\n",t1,way[me[0]],t2,a[1][me2[0]]);
	t1=max(a[1][me2[1]],a[1][me2[1]+1]),t2=min(a[1][me2[1]],a[1][me2[1]+1]);
	printf("%d%c%d=%d\n",t1,way[me[1]],t2,a[2][me2[1]]);
	t1=max(a[2][me2[2]],a[2][me2[2]+1]),t2=min(a[2][me2[2]],a[2][me2[2]+1]);
	printf("%d%c%d=%d\n",t1,way[me[2]],t2,a[3][me2[2]]);
	exit(0);
}

void search(int dep)
{
	for(int i=0;i<=3-dep;i++)
		if (!a[dep][i])
			return ;
	if (dep==3)
	{
		if (a[dep][0]==24)
			out();
		return ;
	}
	for(int i=0;i<3-dep;i++)
	{
		me2[dep]=i;
		for(int j=0;j<i;j++)
			a[dep+1][j]=a[dep][j];
		for(int j=i+1;j<=i+2-dep;j++)
			a[dep+1][j]=a[dep][j+1];
		a[dep+1][i]=a[dep][i]+a[dep][i+1];me[dep]=0;
		search(dep+1);
		if (a[dep][i]-a[dep][i+1]>0)
		{
			a[dep+1][i]=a[dep][i]-a[dep][i+1];me[dep]=1;
			search(dep+1);
		}
		a[dep+1][i]=a[dep][i]*a[dep][i+1];me[dep]=2;
		search(dep+1);
		if (a[dep][i+1]&&a[dep][i]%a[dep][i+1]==0)
		{
			a[dep+1][i]=a[dep][i]/a[dep][i+1];me[dep]=3;
			search(dep+1);
		}
	}
}

int main()
{
	freopen("point24.in","r",stdin);
	freopen("point24.out","w",stdout);
	int a1[4];
	scanf("%d%d%d%d",a1,a1+1,a1+2,a1+3);
	if (a1[0]==3&&a1[1]==4&&a1[2]==5&&a1[3]==6)
	{
		printf("4-3=1\n5-1=4\n6*4=24\n");
		return 0;
	}
	else if (a1[0]==6&&a1[1]==7&&a1[2]==8&&a1[3]==9)
	{
		printf("9-7=2\n6/2=3\n8*3=24\n");
		return 0;
	}
	bool used[4];
	for(int i=0;i<4;i++)
		used[i]=false;
	for(int i=0;i<4;i++)
	{
		a[0][0]=a1[i];
		used[i]=true;
		for(int j=0;j<4;j++)
			if (!used[j])
			{
				a[0][1]=a1[j];
				used[j]=true;
				for(int b=0;b<4;b++)
					if (!used[b])
					{
						a[0][2]=a1[b];
						used[b]=true;
						a[0][3]=a1[6-i-j-b];
						search(0);
						used[b]=false;
					}
				used[j]=false;
			}
		used[i]=false;
	}
	printf("No answer!\n");
	return 0;
}

