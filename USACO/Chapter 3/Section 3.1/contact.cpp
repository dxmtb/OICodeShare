/*
  ID: dxmtb1
  PROG: contact
  LANG: C++
*/
#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXA=12,MAXN=50;

struct Node
{
	int num,l,c;//数字，长度，次数
	Node(int a=0,int b=0,int d=0):num(a),l(b),c(d){}
};

inline bool comp(Node a,Node b)
{
	return (a.c>b.c)||(a.c==b.c&&a.l<b.l)||(a.c==b.c&&a.l==b.l&&a.num<b.num); 
}

void put(int num,int l)
{
	if(!l)return;
	if(num==0)
	{
		for(int i=0;i<l;i++)
			printf("0");
		return;
	}
	put(num/2,l-1);
	printf("%d",num&1);
}

int A,B,N;
string str;
int co[MAXN+1][(1<<MAXA)];

int main()
{
	freopen("contact.in","r",stdin);
	freopen("contact.out","w",stdout);
	cin>>A>>B>>N>>str;
	string temp;
	while (cin>>temp)
		str+=temp;
	int l=str.length();
	for(int i=0;i<l;i++)
	{
		int temp=0;
		for(int j=1;j<=B;j++)
			if (i+j-1<l)
			{
				temp=temp*2+str[i+j-1]-'0';
				co[j][temp]++;
			}
	}
	vector<Node> v;
	for(int i=0;i<(1<<MAXA);i++)
		for(int j=A;j<=B;j++)
			if(co[j][i])
				v.push_back(Node(i,j,co[j][i]));
	sort(v.begin(),v.end(),comp);
	l=1;printf("%d\n",v[0].c);
	put(v[0].num,v[0].l);
	for(int i=1,p=1;i<v.size();i++)
		if(v[i-1].c==v[i].c)
		{
			if(l%6==0)
				printf("\n");
			else printf(" ");
			l++;
			put(v[i].num,v[i].l);		
		}
		else
		{
			l=1;p++;
			if(p>N)
				break;
			printf("\n%d\n",v[i].c);
			put(v[i].num,v[i].l);
		}
	printf("\n");
	return 0;
}
