#include <iostream>
using namespace std;

const int MAXN=100;

int n;

int main()
{
	cin>>n;
	long long s=0,ss=0;
	for(int i=1;i<=n;i++)
		if (i%7==0)
			s+=i*i;
		else 
		{
			int temp=i;
			while (temp!=0)
			{
				if (temp%10==7)
				{
					s+=i*i;
					break;
				}
				temp=temp/10;
			}
		}
	for(int i=1;i<=n;i++)
		ss+=i*i;
	cout<<ss-s<< endl;
	return 0;
}
