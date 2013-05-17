/*
ID: dxmtb
PROG: 搜索引擎提示框
TIME: 2010.7.6
STATE: Solved
MEMO: Trie
*/
#include <cstdio>
#include <cstring>
using namespace std;

struct Node
{
	char data;
	Node *next[26];
	bool flag;
	Node(char ch=0):data(ch){memset(next,0,sizeof(next));}
};

class Trie
{
	private:
		Node root;
		void ins(char str[21])
		{
			Node **pp=&(root.next[str[0]-'a']);
			if (!(*pp))(*pp)=new Node(str[0]);
			for(int p=1,len=strlen(str);p<len;p++)
			{
				pp=&((*pp)->next[str[p]-'a']);
				if (!(*pp))(*pp)=new Node(str[p]);
			}
			(*pp)->flag=true;
		}
		void find(Node *pp,char str[21],int &num)
		{
			if (!pp)return ;
			char temp[21];
			if (pp->flag)
			{
				if (num)printf(" ");
				printf("%s%c",str,pp->data);
				num++;
			}
			sprintf(temp,"%s%c",str,pp->data);
			for(int i=0;i<26&&num<8;i++)
				find(pp->next[i],temp,num);
		}
	public:
		void insert(char str[21]){ins(str);}
		void solve(char str[21])
		{
			int num=0;
			Node *pp=root.next[str[0]-'a'];
			if (!pp){printf("%s\n",str);return;}
			for(int p=1,len=strlen(str);p<len;p++)
			{
				pp=pp->next[str[p]-'a'];
				if (!pp){printf("%s\n",str);return;}
			}
			if (pp->flag)
			{
				printf("%s",str);
				num++;
			}
			for(int i=0;i<26&&num<8;i++)
				find(pp->next[i],str,num);
			printf("\n");
		}
}tree;

const int MAXN=10000;

int n;

int main()
{
	freopen("seaengtip.in","r",stdin);
	freopen("seaengtip.out","w",stdout);
	scanf("%d\n",&n);
	for(int i=0;i<n;i++)
	{
		char str[100]="";
		fgets(str,100,stdin);
		str[strlen(str)-1]=0;
		tree.insert(str);
	}
	scanf("%d\n",&n);
	for(int i=0;i<n;i++)
	{
		char str[100]="";
		fgets(str,100,stdin);
		str[strlen(str)-1]=0;
		tree.solve(str);
	}
}
