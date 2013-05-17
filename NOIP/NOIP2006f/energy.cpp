#include <fstream>
using namespace std;
const int maxn=100;
int i,j,n,k,re;
int d[2*maxn][2*maxn];
int max(int a,int b){
  return a>b?a:b;
}

ifstream fin ("energy.in");
ofstream fout ("energy.out");

int main(){
 int r[2*maxn],l[2*maxn];
 memset(d,0,sizeof(d));
 fin>>n;
 for(i=1;i<=n;i++){
  fin>>l[i];l[i+n]=l[i];
 }
 for(i=1;i<=2*n-1;i++)r[i]=l[i+1];
 r[2*n]=r[n];
 for(i=1;i<=2*n-1;i++)d[i][i+1]=l[i]*l[i+1]*r[i+1];
 for(j=2;j<=n-1;j++)
  for(i=1;i<=2*n-j;i++)
   for(k=i;k<=i+j-1;k++)
    d[i][i+j]=max(d[i][i+j],d[i][k]+d[k+1][i+j]+l[i]*l[k+1]*r[i+j]);
 re=0;
 for(i=1;i<=n+1;i++)
  if (d[i][i+n-1]>re) re=d[i][i+n-1];
 fout<<re;
}
