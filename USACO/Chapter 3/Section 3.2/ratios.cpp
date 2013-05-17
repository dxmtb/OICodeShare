/*
PROG: ratios
LANG: C++
ID: dxmtb1
*/
#include <cstdio>
using namespace std;

int goal[3];
int so[3][3];
int re[4];
int min=0x7fffffff;
int q;

void check(int a,int b,int c)
{
	int s1=a*so[0][0]+b*so[1][0]+c*so[2][0];
	int s2=a*so[0][1]+b*so[1][1]+c*so[2][1];
	int s3=a*so[0][2]+b*so[1][2]+c*so[2][2];
	if((s1==0)^(goal[0]==0))return;
	if((s2==0)^(goal[1]==0))return;
	if((s3==0)^(goal[2]==0))return;
	int t1,t2,t3;
	if(goal[0]!=0&&s1%goal[0])return;
	if(goal[1]!=0&&s2%goal[1])return;
	if(goal[2]!=0&&s3%goal[2])return;
	if(goal[0]!=0)t1=s1/goal[0];
	else t1=-1;
	if(goal[1]!=0)t2=s2/goal[1];
	else t2=-1;
	if(goal[2]!=0)t3=s3/goal[2];
	else t3=-1;
	if(t1!=-1&&t2!=-1&&t1!=t2)return;
	if(t2!=-1&&t3!=-1&&t2!=t3)return;
	if(t1!=-1&&t3!=-1&&t1!=t3)return;
	re[0]=a,re[1]=b,re[2]=c,re[3]=s1/goal[0],min=a+b+c;
}

int main()
{
	freopen("ratios.in","r",stdin);
	freopen("ratios.out","w",stdout);
	scanf("%d%d%d",goal,goal+1,goal+2);
	for(int i=0;i<3;i++)
		scanf("%d%d%d",so[i],so[i]+1,so[i]+2);
	for(int i=0;i<=100;i++)
		for(int j=0;j<=100;j++)
			for(int k=0;k<=100;k++)
				if(i+j+k>min)break;
				else check(i,j,k);
	if(min!=0x7fffffff)
		printf("%d %d %d %d\n",re[0],re[1],re[2],re[3]);
	else printf("NONE\n");
	return 0;
}
