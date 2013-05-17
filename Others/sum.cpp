#include <iostream>
#include <fstream>
using namespace std;

ifstream fin ("sum.in");
ofstream fout ("sum.out");

int main()
{
	int k;
	fin>>k;
	double s=0,n=1;
	for(;!(s>k);n++)
	{
		s=s+1/n;
	}
	fout<<n-1<<endl;
	return 0;
}
