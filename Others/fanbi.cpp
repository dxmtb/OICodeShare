#include <cstdio>
#include <queue>
using namespace std;

const int MAXN=3000;

struct Node
{
	int left,step;
};

FILE *fin=fopen("fanbi.in","r");
FILE *fout=fopen("fanbi.out","w");

bool in[MAXN];
int n;

int main()
{
//////init
	fscanf(fin,"%d",&n);
	memset(in,false,sizeof(in));
	queue<Node> q;
/////
	int t=0;
	Node begin;
	begin.left=n;
	begin.step=0;
	q.push(begin);
	in[n]=true;
	while (!q.empty())
	{
		Node temp=q.front();
		q.pop();
		for(int i=max(0,5-n+temp.left);i<=temp.left&&i<=5;i++)
		{
			Node now;
			now.left=temp.left+5-2*i;
			if (in[now.left]) continue;
			in[now.left]=true;
			now.step=temp.step+1;
			if (now.left==0) {fprintf(fout,"%d",now.step);return 0;}
			q.push(now);t++;
		}
	}
	fprintf(fout,"No solution!","w");
	return 0;
}

