/*
ID: dxmtb
PROG: NOI01 聪明的打字员
TIME: 2010.3.27
STATE: Solved
MEMO: 搜！
*/
#include <cstdio>
#include <queue>
using namespace std;

const int maxint=0x7fff;

struct Node 
{
	int num[6],dep,index;
	bool visited[6];
};

struct link
{
	Node info;
	link *next;
};
void init();
void bfs();
int calcu(Node,Node);
bool check(Node);

FILE *fin=fopen("clever.in","r");
FILE *fout=fopen("clever.out","w");

Node begin,final;
link hash[10000000];
int mins=maxint,d[1000000];
int timer=0;

int main()
{
	init();
	queue<Node> q;
	q.push(begin);
	while(!q.empty())
	{
		int re=maxint;
		Node temp=q.front(),now;
		q.pop();
		if (temp.dep>=mins) continue;
		//right
		if (temp.index!=5)
		{
			now=temp;
			now.dep++;
			now.visited[++now.index]=true;
			if (temp.dep<mins&&check(now)) q.push(now),timer++;
			re=calcu(now,final);
			if (re+now.dep<mins)mins=re+now.dep;
		}
		//swap0
		if (temp.index!=0)
		{
			now=temp;
			int x;
			x=now.num[now.index];
			now.num[now.index]=now.num[0];
			now.num[0]=x;
			now.dep++;
			if (temp.dep<mins&&check(now)) q.push(now),timer++;
			re=calcu(now,final);
			if (re+now.dep<mins)mins=re+now.dep;
		}
		//swap1
		if (temp.index!=5)
		{
			now=temp;
			int x;
			x=now.num[now.index];
			now.num[now.index]=now.num[5];
			now.num[5]=x;
			now.visited[5]=true;
			now.dep++;
			if (temp.dep<mins&&check(now)) q.push(now),timer++;
			re=calcu(now,final);
			if (re+now.dep<mins)mins=re+now.dep;	
		}		
		//left
		if (temp.index!=0)
		{
			now=temp;
			now.dep++;
			now.visited[--now.index]=true;
			if (temp.dep<mins&&check(now)) q.push(now),timer++;
			re=calcu(now,final);
			if (re+now.dep<mins)mins=re+now.dep;
		}
	}
	fprintf(fout,"%d",mins);	
	return 0;
}

void init()
{
	for(int i=0;i<1000000;i++)
		for(int j=0;j<6;j++)
		hash[i].next=NULL;
	int a,b;
	fscanf(fin,"%d%d",&a,&b);
	for(int i=5;i>=0;i--)
		begin.num[i]=a%10,a/=10;
	begin.index=0;
	begin.dep=0;
	memset(begin.visited,false,sizeof(begin.visited));
	begin.visited[0]=true;
	for(int i=5;i>=0;i--)
		final.num[i]=b%10,b/=10;
	mins=calcu(begin,final);
}
int calcu(Node a,Node b)
{
	int res=0;
	for(int i=0;i<6;i++)
		if (a.visited[i])res+=abs(a.num[i]-b.num[i]);
		else if (a.num[i]!=b.num[i]) return maxint;
	return res;
}

bool check(Node a)
{
	int x=a.index*1000000+a.num[5]+a.num[4]*10+a.num[3]*100+a.num[2]*1000+a.num[1]*10000+a.num[0]*100000;
	link *p=&hash[x];
	while (p->next!=NULL)
		{
			p=p->next;
			bool flag=true;
			if (a.index!=p->info.index)continue;
			for(int j=0;j<6;j++)
			if (a.num[j]!=p->info.num[j]) {flag=false;break;}
			if (!flag) continue;
			for(int j=0;j<6;j++)
				if (a.visited[j]!=p->info.visited[j]) {flag=false;break;}
			if (!flag) continue;
			return false;
		}
	p=new link;
	p->next=hash[x].next;
	p->info=a;
	hash[x].next=p;	
	return true;
}
