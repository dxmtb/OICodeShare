/*
 * Problem: sgu275 To xor or not to xor 
 * Time: 2011.06.23
 * Author: dxmtb
 * State: Solved
 * Memo: 优先满足高位
*/
#include <iostream>
using namespace std;

const int MAXN=105;
typedef long long s64;

s64 a[MAXN];

int main()
{
	int N;
	cin>>N;
	for(int i=0;i<N;i++)
		cin>>a[i];
	s64 ans=0;
	for(int i=62;i>=0;i--)
		{
			int k=-1;
			for(int j=0;j<N;j++)
				if (a[j]&(1LL<<i))
				{
					k=j;
					break;
				}
			if (k!=-1)
			{
				if (!(ans&(1LL<<i)))
					ans^=a[k];
				for(int j=0;j<N;j++)
					if (j!=k && (a[j]&(1LL<<i)))
						a[j]^=a[k];
				a[k]=0;
			}
		}
	cout<<ans<<endl;
	return 0;
}
