/*
ID: dxmtb
PROG: HAOI2008 玩具取名
TIME: 2011.03.16
STATE: Solved
MEMO: dp
*/
#include <cstdio>
#include <cstring>
const int MAXN=250;

int d[MAXN][MAXN][4];
int s[4];
int way[4][20][2];

inline void change(char &ch)
{
	switch(ch)
	{
		case 'W':ch=0;break;
		case 'I':ch=1;break;
		case 'N':ch=2;break;
		case 'G':ch=3;break;
	}
}

int main()
{
	freopen("name.in","r",stdin);
	freopen("name.out","w",stdout);
	scanf("%d%d%d%d",s,s+1,s+2,s+3);
	for(int i=0;i<s[0];i++)
	{
		char ch[5];
		scanf(" %s",ch);
		change(ch[0]);
		change(ch[1]);
		way[0][i][0]=ch[0];
		way[0][i][1]=ch[1];
	}
	for(int i=0;i<s[1];i++)
	{
		char ch[5];
		scanf(" %s",ch);
		change(ch[0]);
		change(ch[1]);
		way[1][i][0]=ch[0];
		way[1][i][1]=ch[1];
	}
	for(int i=0;i<s[2];i++)
	{
		char ch[5];
		scanf(" %s",ch);
		change(ch[0]);
		change(ch[1]);
		way[2][i][0]=ch[0];
		way[2][i][1]=ch[1];
	}
	for(int i=0;i<s[3];i++)
	{
		char ch[5];
		scanf(" %s",ch);
		change(ch[0]);
		change(ch[1]);
		way[3][i][0]=ch[0];
		way[3][i][1]=ch[1];
	}	
	char str[250];
	scanf(" %s",str);
	int len=strlen(str);
	for(int i=0;i<len;i++)
	{
		change(str[i]);
		d[i][i][int(str[i])]=true;
	}
	for(int l=1;l<len;l++)
	{
		for(int i=0,j;(j=i+l)<len;i++)
			for(int p=0;p<4;p++)
				for(int q=0;q<s[p]&&d[i][j][p]==false;q++)
					for(int k=i;k<j;k++)
						if (d[i][k][way[p][q][0]] && d[k+1][j][way[p][q][1]])
						{
							d[i][j][p]=true;
							break;
						}		
	}
	bool flag=true;
	if (d[0][len-1][0])
		printf("W"),flag=false;
	if (d[0][len-1][1])
		printf("I"),flag=false;
	if (d[0][len-1][2])
		printf("N"),flag=false;	
	if (d[0][len-1][3])
		printf("G"),flag=false;	
	if (flag)
		printf("The name is wrong!");
	printf("\n");
	return 0;
}
