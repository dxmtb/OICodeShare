#include <cstdio>
#include <vector>
using namespace std;

const int MAXN=105;

int X[MAXN],Y[MAXN],U[MAXN],V[MAXN];
vector<int> can[MAXN];
bool used[MAXN];
int M,N,K;

inline int getdis(int x,int y)
{
	return x*x+y*y;
}

int main(int argc,char *argv[])
{
	FILE *fin=fopen(argv[1],"r");
	FILE *fans=fopen(argv[2],"r");
	FILE *fout=fopen(argv[3],"r");
	fscanf(fin,"%d%d%d",&M,&N,&K);
	for(int i=0;i<M;i++)
		fscanf(fin,"%d%d",X+i,Y+i);
	for(int i=0;i<N;i++)
		fscanf(fin,"%d%d",U+i,V+i);
	for(int i=0;i<N;i++)
		for(int j=0;j<M;j++)
			if (getdis(X[j]-U[i],Y[j]-V[i])<=K*K)
				can[i].push_back(j);
	int re;
	fscanf(fout,"%d",&re);
	for(int i=0,j=-1;i<re;i++)
	{
		int x;
		fscanf(fout,"%d",&x);
		x--;
		if (used[x])
		{
			printf("Bomb %d reused!\n",x);
			return 0;
		}
		used[x]=true;
		for(int k=0;k<(int)can[x].size();k++)
			if (can[x][k]>j)
			{
				if (can[x][k]==j+1)
					j++;
				else
					break;
			}
		if (i==re-1 && j!=M-1)
		{
			printf("You didn't finish the target!\n");
			return 0;
		}
	}
	int ans;
	fscanf(fans,"%d",&ans);
	int score;
	int t=re-ans;
	if (t<-32) score=18;
	else if (t<=-16) score=17;
	else if (t<=-7) score=15;
	else if (t<=-4) score=13;
	else if (t<=-2) score=12;
	else if (t==-1) score=11;
	else if (t==0) score=10;
	else if (t==1) score=9;
	else if (t<=3) score=8;
	else if (t<=6) score=7;
	else if (t<=15) score=5;
	else if (t<=32) score=3;
	else score=2;
	printf("Standart answer is %d. Your answer is %d. Score %d\n",ans,re,score);
	return 0;
}
