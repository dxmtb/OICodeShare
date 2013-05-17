/*
ID: dxmtb
PROG: NOIP2005 等价表达式
TIME: 2010.9.21
STATE: Solved
MEMO: 表达式计算
*/
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <stack>
using namespace std;

const char ope[6]={'+','-','*','^','(',')'};
const long long youx[6]={1,1,2,3,0,0};
const long long MO=1741013;

string str;
stack<long long> opt;
stack<long long> s1;

long long pow(long long a,long long b)
{
	if (!b)return 1;
	long long t=a%MO;
	for(long long i=1;i<b;i++)
	{
		t=(t*(a%MO));
		t%=MO;
	}
	return t;
}

void deal()
{
	long long a1=s1.top();s1.pop();
	long long a2=s1.top();s1.pop();
	long long op=opt.top();opt.pop();
	switch(op)
	{
		case 0:s1.push((a1+a2)%MO);break;
		case 1:s1.push((a2-a1)%MO);break;
		case 2:s1.push((a1*a2)%MO);break;
		case 3:s1.push((pow(a2,a1)%MO));break;
		default: cerr<<"wrong\n";
	}
}

long long calcu(string str,long long a)
{
	unsigned len=str.length();
	long long temp=0;
	bool flag=false;
	for(unsigned i=0;i<len;i++)
	{
		if (str[i]==' ')continue;
		if (str[i]>='0'&&str[i]<='9')
		{
			temp=temp*10+str[i]-'0';
			flag=true;
			continue;
		}
		else 
		{
			if (flag) 
			{
				s1.push(temp%MO);
				temp=0;
				flag=false;
			}
		}
		if (str[i]=='(')
		{
			opt.push(4);
			continue;
		}
		if (str[i]==')')
		{
			while(opt.top()!=4)
				deal();
			opt.pop();
			continue;
		}
		if (str[i]=='a')
		{
			s1.push(a%MO);
			continue;
		}
		switch (str[i])
		{
			case '+':
				while (!opt.empty()&&youx[0]<=youx[opt.top()])
					deal();
				opt.push(0);break;
			case '-':
				while (!opt.empty()&&youx[1]<=youx[opt.top()])
					deal();
				opt.push(1);break;
			case '*':
				while (!opt.empty()&&youx[2]<=youx[opt.top()])
					deal();
				opt.push(2);break;
			case '^':
				while (!opt.empty()&&youx[3]<=youx[opt.top()])
					deal();
				opt.push(3);break;
			default : cerr<<"wrong"<<endl;
		}
	}
	if (!opt.empty())cerr<<"wrong!!\n";
	return s1.top();
}

int main()
{
	freopen("equal.in","r",stdin);
	freopen("equal.out","w",stdout);
	srand(4741013);
	getline(cin,str);
	str='('+str+')';
	int n;
	scanf("%d\n",&n);
	for(int i=0;i<n;i++)
	{
		string s;
		getline(cin,s);
		s='('+s+')';
		int j;
		for(j=0;j<4;j++)
		{
			long long a=j;
			long long r1=calcu(str,a),r2=calcu(s,a);
			if ((r1)!=(r2))
				break;
		}
		if (j==4)
			printf("%c",'A'+i);
	}
	return 0;
}
			


