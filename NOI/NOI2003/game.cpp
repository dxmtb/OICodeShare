/*
ID: dxmtb
PROG: NOI2003 木棒游戏
TIME: 2011.03.01
STATE: Solved
MEMO: 枚举
*/
#include <cstdio>
#include <cstring>

const int MAXN=1005;
const int adj1[10][3]={{2,6,9},//self
	{0},{1,3},{1,2},{0},{1,3},{2,0,9},{0},{0},{2,0,6}};
const int adj2[10][4]={{0},//remove
	{0},{0},{0},{0},{0},{1,5},{1,1},{3,6,9,0},{2,3,5}};
const int adj3[10][3]={{1,8},//add
	{1,7},{0},{1,9},{0},{2,6,9},{2,5,8},{0},{0},{1,8}};
const int dec[9]={1,10,100,1000,10000,100000,1000000,10000000,100000000};

char str[MAXN];
int N;
int num[MAXN];
int belong[MAXN];
int sign[MAXN];
int ind[MAXN];
int tot[MAXN];
int len[MAXN];
int sum[MAXN];

int main()
{
	freopen("game.in","r",stdin);
	freopen("game.out","w",stdout);
	char ch=getchar();
	char *begin;
	if (ch=='+'||ch=='-')
	{
		begin=str;
		str[0]=ch;
		scanf("%s",str+1);
	}
	else
	{
		begin=str+1;
		str[0]='+';
		str[1]=ch;
		scanf("%s",str+2);
	}
	N=strlen(str);
	for(int i=0,t=0,tmp=1;;i++)
	{
		if (str[i]=='#')
		{
			N=i;
			str[i+1]=0;
			break;
		}
		if (str[i]=='=')
		{
			tmp=-1;
			belong[t=i]=-1;
			sign[t]=-1;
		}
		else if (str[i]=='+'||str[i]=='-')
		{
			if (i&&str[i-1]!='=') t=i;
			sign[t]=((str[i]=='+')?1:-1)*tmp;
			belong[i]=-1;
		}
		else
		{
			num[i]=str[i]-'0';
			tot[t]=tot[t]*10+num[i];
			ind[i]=i-t;
			belong[i]=t;
			len[t]++;
		}
	}	
	int total=0;
	for(int i=0;i<N;i++)
		if (belong[i]!=-1)
			ind[i]=len[belong[i]]-ind[i];
		else total+=tot[i]*sign[i];
	for(int i=0;i<N;i++)
		if (belong[i]!=-1)
			for(int j=1;j<=adj1[num[i]][0];j++)
				if (total+(adj1[num[i]][j]-num[i])
				    *dec[ind[i]]*sign[belong[i]]==0)
				{
					str[i]=adj1[num[i]][j]+'0';
					printf("%s\n",begin);
					return 0;
				}
	for(int i=0;i<N;i++)
	if (belong[i]!=-1)
	for(int j=1;j<=adj2[num[i]][0];j++)
		for(int a=0;a<N;a++)
		if (belong[a]!=-1 && i!=a)
		for(int b=1;b<=adj3[num[a]][0];b++)
		{
			int t1=(adj2[num[i]][j]-num[i])*dec[ind[i]]*
				sign[belong[i]];
			int t2=(adj3[num[a]][b]-num[a])*dec[ind[a]]*
				sign[belong[a]];
			if (total+t1+t2==0)
			{
				str[i]=adj2[num[i]][j]+'0';
				str[a]=adj3[num[a]][b]+'0';
				printf("%s\n",begin);
				return 0;
			}
		}
	printf("No\n");
	return 0;
}
