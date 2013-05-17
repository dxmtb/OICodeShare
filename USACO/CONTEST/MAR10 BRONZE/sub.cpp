/*
PROG: sub
LANG: C++
ID: dxmtb1
*/

#include <fstream>

using namespace std;

const int MAXN=200;

ifstream fin ("sub.in");
ofstream fout ("sub.out");

int main()
{
	int l1,l2,n1[MAXN],n2[MAXN];
	fin>>l1>>l2;
	for(int i=0;i<l1;i++)fin>>n1[i];
	for(int i=0;i<l2;i++)fin>>n2[i];
	int re=0;
	for(int i=0;i<l1;i++)
		for(int j=0;j<l2;j++)
			for(int k=0;i+k<l1&&j+k<l2&&n1[i+k]==n2[j+k];)
				if (++k>re) re=k;
	fout<<re<<endl;
	return 0;
}
