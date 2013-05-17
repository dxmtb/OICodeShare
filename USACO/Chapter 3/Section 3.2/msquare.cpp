/*
PROG: msquare
LANG: C++
ID: dxmtb1
*/
#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;

const int jc[8]={1,1,2,6,24,120,720,5040};
const int MAXN=40320;
bool hash[MAXN];
int q[MAXN],from[MAXN],dep[MAXN],qt=-1,qn=0;
int goal;
char way[MAXN];

void cal(int x,int w)
{
	if(x==goal)
	{
		printf("%d\n",dep[qn-1]);
		if(!dep[qn-1]){printf("\n");exit(0);}
		char re[40320]={1,'A'+w-1};
		for(int i=qn-1;i;i=from[i])
			re[++re[0]]=way[i];
		for(int i=re[0];i>=1;i--)
		  printf("%c",re[i]);
		printf("\n");
		exit(0);
	}
	int re=0;
	bool u[8];
	memset(u,false,sizeof(u));
	for(int i=0,t1=x,t2;i<8;i++)
	{
		int t3=0;
		u[t2=t1%10]=true;
		for(int j=t2-1;j;j--)
			if(!u[j])
				t3--;
		t1=t1/10;
		re+=(t2-1+t3)*jc[i];
	}
	if(hash[re])
		return;
	else
		hash[re]=true;
	q[++qt]=x;
	way[qt]='A'+w-1;
	from[qt]=qn-1;
	dep[qt]=dep[qn-1]+1;
}

int main()
{
	freopen("msquare.in","r",stdin);
	freopen("msquare.out","w",stdout);
	for(int i=0,x;i<8;i++)
	{
		scanf("%d",&x);
		goal=goal*10+x;
	}
	goal=goal/10000*10000+goal/1000%10+goal/100%10*10+goal/10%10*100+goal%10*1000;
	cal(12348765,0);
	while(qt>=qn)
	{
		int temp=q[qn++],newone;
//way1
		newone=(temp-temp/10000*10000)*10000+temp/10000;
		cal(newone,1);
//way2
		newone=temp%10*1000+temp/10000%10*10000000+temp%10000/10+temp/100000*10000;
		cal(newone,2);
//way3
		newone=temp/10000000%10*10000000+temp/100%10*1000000+temp/1000000%10*100000+temp/10000%10*10000+temp/1000%10*1000+temp/10%10*100+temp/100000%10*10+temp%10;
		cal(newone,3);
	}
	return 0;
}
