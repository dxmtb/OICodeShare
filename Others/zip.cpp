/*
ID: dxmtb
PROG: 文件压缩
TIME: 2010.11.9
STATE: Solved
MEMO: 构造
*/
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
const int MAXN=10005;

int n,p;
char str[MAXN],str2[MAXN],path[MAXN];

bool used[MAXN];
int main()
{
	freopen("zip.in","r",stdin);
	freopen("zip.out","w",stdout);
	cin>>n;
	cin>>str;
	scanf("%d",&p);
	p--;
	memcpy(str2,str,sizeof(str));
	sort(str2,str2+n);
	cout<<str[p];
	int i=0,top=1;
	for(i=0;i<n;i++)
		if (str2[i]==str[p])
			break;
	while(true)
	{
		int j;
		for(j=n-1;j>=0;j--)
			if (!used[j]&&str2[j]==str[i])
			{
				used[j]=true;
				break;
			}
		path[top++]=str[i];
		i=j;
		if (i==p)
			break;
	}
	for(int i=n-1;i>=1;i--)
		cout<<path[i];
	cout<<endl;
	return 0;
}		
