/*
ID: dxmtb
PROG: NOIP2007 字符串的展开
TIME: 2010.5.15
STATE: Solved
MEMO: 模拟
*/
#include <string>
#include <iostream>
using namespace std;

const char ch='-';
const int up='A'-'a';

string str;
int p1,p2,p3;

void init()
{
	cin>>p1>>p2>>p3>>str;
}

void solve()
{
	size_t p,j;
	for(j=0,p=str.find(ch,j);p!=str.npos;p=str.find(ch,j))
	{
		if (p==0||p==str.length()||str[p-1]>=str[p+1])
		{
			j=p+1;
			continue;
		}
		int f1=0,f2=0;//letter 1 number 2
		if (str[p-1]>='0'&&str[p-1]<='9')
			f1=2;
		else if (str[p-1]>='a'&&str[p-1]<='z')
			f1=1;
		if (str[p+1]>='0'&&str[p+1]<='9')
			f2=2;
		else if (str[p+1]>='a'&&str[p+1]<='z')
			f2=1;
		if (!f1||!f2||f1!=f2)
		{
			j=p+1;
			continue;
		}
		string temp;
		//step1
		if (p1!=3)
		for(char i=str[p-1]+1;i<=str[p+1]-1;i++)
		{
			if (f1==2)
				for(int k=0;k<p2;k++)
					temp+=i;
			else 
			{
				int add=up;
				if (p1==1)
					add=0;
				for(int k=0;k<p2;k++)
					temp+=i+add;
			}
		}
		else
		for(char i=str[p-1]+1;i<=str[p+1]-1;i++)
		{
			for(int k=0;k<p2;k++)
				temp+='*';
		}
		//step2
		if (p3==2)
		{
			string t2;
			for(int i=temp.length()-1;i>=0;i--)
				t2+=temp[i];
			temp=t2;
		}
		str.erase(p,1);
		str.insert(p,temp);
	}
	cout<<str<<endl;
}

int main() 
{
	freopen("expand.in","r",stdin);
	freopen("expand.out","w",stdout);
	init();
	solve();
	return 0;
}
