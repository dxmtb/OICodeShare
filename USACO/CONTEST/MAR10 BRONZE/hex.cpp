/*
PROG: hex
LANG: C++
ID: dxmtb1
*/

#include <fstream>
#include <iomanip>

using namespace std;

const int MAXN=20;

ifstream fin ("hex.in");
ofstream fout ("hex.out");

int main()
{
	int n;
	fin>>hex>>n;
	fout<<oct<<n<<endl;
	return 0;
}
